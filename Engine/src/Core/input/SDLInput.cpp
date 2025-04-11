#include "SDLInput.h"
#include "../utl/Assert.h"
#include <nlohmann\json.hpp>
#include <fstream>

namespace hydro::input
{
	inline const char* GetKeyName(KeyCode code) {
		return SDL_GetScancodeName((::SDL_Scancode)code);
	}

	inline KeyCode GetKeyCodeFromName(const std::string& name) {
		return (KeyCode)SDL_GetScancodeFromName(name.c_str());
	}

    inline std::string MouseButtonToString(MouseButton btn) {
        switch (btn) {
            case MouseButton::Left: return "Left";
            case MouseButton::Right: return "Right";
            case MouseButton::Middle: return "Middle";
            case MouseButton::Side1: return "Side1";
            case MouseButton::Side2: return "Side2";
        }
        return "Unknown";
    }

    inline MouseButton MouseButtonFromString(const std::string& str) {
        if (str == "Left") return MouseButton::Left;
        if (str == "Right") return MouseButton::Right;
        if (str == "Middle") return MouseButton::Middle;
        if (str == "Side1") return MouseButton::Side1;
        if (str == "Side2") return MouseButton::Side2;
        return (MouseButton)-1;
    }

    using json = nlohmann::json;

    SDLInput::SDLInput() {

        // Initialize keyboard states
        for (int i = 0; i < SDL_SCANCODE_COUNT; ++i) {
            keyStates_[static_cast<KeyCode>(i)] = false;
            prevKeyStates_[static_cast<KeyCode>(i)] = false;  // Added
        }

        // Initialize mouse buttons
        for (int i = 0; i < 5; ++i) {
            mouseButtonStates_[static_cast<MouseButton>(i)] = false;
            prevMouseButtonStates_[static_cast<MouseButton>(i)] = false;
        }
    }

    void SDLInput::Update() {
        prevMouse_ = currentMouse_;

        currentMouse_.delta = { 0.0f, 0.0f };
        currentMouse_.scroll = { 0.0f, 0.0f };
    }

    void SDLInput::UpdateEvent(SDL_Event& event) {
        switch (event.type) {
        case SDL_EVENT_MOUSE_MOTION:
            currentMouse_.position = {
                static_cast<float>(event.motion.x),
                static_cast<float>(event.motion.y)
            };
            currentMouse_.delta = {
                static_cast<float>(event.motion.xrel),
                static_cast<float>(event.motion.yrel)
            };
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            currentMouse_.scroll = {
                static_cast<float>(event.wheel.x),
                static_cast<float>(event.wheel.y)
            };
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            ProcessMouseButtonEvent(event);
            break;

        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            ProcessKeyboardEvent(event);
            break;

        case SDL_EVENT_WINDOW_MOUSE_ENTER:
            currentMouse_.isInWindow = true;
            break;
        case SDL_EVENT_WINDOW_MOUSE_LEAVE:
            currentMouse_.isInWindow = false;
            break;
        }
    }

    void SDLInput::BindAction(const std::string& actionName, const InputBinding& binding) {
        actionBindings_[actionName].push_back(binding);
    }

    void SDLInput::RegisterActionCallback(const std::string& actionName, InputCallback callback) {
        actionCallbacks_[actionName].push_back(callback);
    }

    bool SDLInput::IsActionPressed(const std::string& actionName) const {
        const auto it = actionBindings_.find(actionName);
        if (it == actionBindings_.end()) return false;

        for (const auto& binding : it->second) {
            try {
                bool current, previous;

                if (binding.device == InputDeviceType::Keyboard) {
                    current = keyStates_.at(binding.key);
                    previous = prevKeyStates_.at(binding.key);
                }
                else if (binding.device == InputDeviceType::MouseButton) {
                    current = mouseButtonStates_.at(binding.mouseBtn);
                    previous = prevMouseButtonStates_.at(binding.mouseBtn);
                }
                else {
                    continue;
                }

                if (current && !previous) return true;
            }
            catch (...) {
                continue; 
            }
        }
        return false;
    }

    bool SDLInput::IsActionHeld(const std::string& actionName) const {
        const auto it = actionBindings_.find(actionName);
        if (it == actionBindings_.end()) return false;

        for (const auto& binding : it->second) {
            try {
                bool current = (binding.device == InputDeviceType::Keyboard)
                    ? keyStates_.at(binding.key)
                    : mouseButtonStates_.at(binding.mouseBtn);

                if (current) return true;
            }
            catch (...) {
                continue;
            }
        }
        return false;
    }

    bool SDLInput::IsActionReleased(const std::string& actionName) const {
        const auto it = actionBindings_.find(actionName);
        if (it == actionBindings_.end()) return false;

        for (const auto& binding : it->second) {
            try {
                bool current, previous;

                if (binding.device == InputDeviceType::Keyboard) {
                    current = keyStates_.at(binding.key);
                    previous = prevKeyStates_.at(binding.key);
                }
                else {
                    current = mouseButtonStates_.at(binding.mouseBtn);
                    previous = prevMouseButtonStates_.at(binding.mouseBtn);
                }

                if (!current && previous) return true;
            }
            catch (...) {
                continue;
            }
        }
        return false;
    }

    const MouseState& SDLInput::GetMouseState() const {
        return currentMouse_;
    }

    bool SDLInput::LoadBindingsFromFile(const std::string& path) {
        std::ifstream in(path);
        hass(in.is_open()).msg(L"Failed to open input bindings file: {}" + utl::ToWide(path.c_str()));

        json j;
        in >> j;

        auto& bindingsJson = j["bindings"];
        hass(bindingsJson.is_object()).msg(L"Invalid format: 'bidings' must be object.");

        for (auto& [action, bindingArray] : bindingsJson.items()) {
            if (!bindingArray.is_array()) continue;

            for (const auto& bindingJson : bindingArray) {
                if (!bindingJson.contains("type") || !bindingJson.contains("code")) continue;

                std::string type = bindingJson["type"];
                std::string code = bindingJson["code"];

                if (type == "Keyboard") {
                    KeyCode c = GetKeyCodeFromName(code);
                    
                    if (c != SDL_SCANCODE_UNKNOWN) {
                        BindAction(action, InputBinding{ c });
                    }
                    else {
                        hass(false).msg(L"Unknown key code: {}" + utl::ToWide(code.c_str()));
                    }
                }
                else if (type == "Mouse") {
                    MouseButton btn = MouseButtonFromString(code);

                    if (btn != (MouseButton)-1) {
                        BindAction(action, InputBinding{ btn });
                    }
                    else {
                        hass(false).msg(L"Unknown mouse button: {}" + utl::ToWide(code.c_str()));
                    }
                }
                else {
                    hass(false).msg(L"Unknown binding type: {}" + utl::ToWide(type.c_str()));
                }
            }
        }

        return true;
    }

    bool SDLInput::SaveBindingsToFile(const std::string& path) const {
        json j;

        for (const auto& [action, bindings] : actionBindings_) {
            for (const auto& binding : bindings) {
                switch (binding.device) {
                case InputDeviceType::Keyboard: {
                    std::string name = GetKeyName(binding.key);
                    j["bindings"][action].push_back({
                        { "type", "Keyboard" },
                        { "code", name }
                        });
                    break;
                }
                case InputDeviceType::MouseButton: {
                    std::string name = MouseButtonToString(binding.mouseBtn);
                    j["bindings"][action].push_back({
                        { "type", "Mouse" },
                        { "code", name }
                        });
                    break;
                }
                default:
                    // Skip unknown input device types
                    break;
                }
            }
        }

        std::ofstream out(path);
        hass(out.is_open()).msg(L"Failed to open file for writing: {}" + utl::ToWide(path.c_str()));

        out << j.dump(4);
        return true;
    }

    void SDLInput::ProcessKeyboardEvent(const SDL_Event& event) {
        KeyCode key = static_cast<KeyCode>(event.key.scancode);
        bool pressed = (event.type == SDL_EVENT_KEY_DOWN);

        keyStates_[key] = pressed;

        // Fire callbacks for bound actions
        for (auto& [action, bindings] : actionBindings_) {
            for (auto& binding : bindings) {
                if (binding.device == InputDeviceType::Keyboard && binding.key == key) {
                    InputEventType eventType = pressed ? InputEventType::Pressed : InputEventType::Released;
                    for (auto& callback : actionCallbacks_[action]) {
                        callback(action, eventType, currentMouse_);
                    }
                }
            }
        }
    }

    void SDLInput::ProcessMouseButtonEvent(const SDL_Event & event) {
        MouseButton button = static_cast<MouseButton>(event.button.button-1);
        bool pressed = (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN);

        mouseButtonStates_[button] = pressed;

        // Fire callbacks for bound actions
        for (auto& [action, bindings] : actionBindings_) {
            for (auto& binding : bindings) {
                if (binding.device == InputDeviceType::MouseButton && binding.mouseBtn == button) {
                    InputEventType eventType = pressed ? InputEventType::Pressed : InputEventType::Released;
                    for (auto& callback : actionCallbacks_[action]) {
                        callback(action, eventType, currentMouse_);
                    }
                }
            }
        }
    }

}