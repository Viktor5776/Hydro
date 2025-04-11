#pragma once
#include "IInput.h"
#include <array>
#include <unordered_map>
#include <SDL3\SDL.h>

namespace hydro::input
{

    class SDLInput : public IInput 
    {
    public:
        SDLInput();
        void UpdateEvent(SDL_Event& event);
        void Update();

        void BindAction(const std::string& actionName, const InputBinding& binding) override;
        void RegisterActionCallback(const std::string& actionName, InputCallback callback) override;

        bool IsActionPressed(const std::string& actionName) const override;
        bool IsActionHeld(const std::string& actionName) const override;
        bool IsActionReleased(const std::string& actionName) const override;

        const MouseState& GetMouseState() const override;

        bool LoadBindingsFromFile(const std::string& path) override;
        bool SaveBindingsToFile(const std::string& path) const override;
    private:
        void ProcessKeyboardEvent(const SDL_Event& event);
        void ProcessMouseButtonEvent(const SDL_Event& event);
    private:
        std::unordered_map<std::string, std::vector<InputBinding>> actionBindings_;
        std::unordered_map<std::string, std::vector<InputCallback>> actionCallbacks_;

        std::unordered_map<KeyCode, bool> keyStates_;
        std::unordered_map<KeyCode, bool> prevKeyStates_;  

        std::unordered_map<MouseButton, bool> mouseButtonStates_;
        std::unordered_map<MouseButton, bool> prevMouseButtonStates_;

        MouseState currentMouse_;
        MouseState prevMouse_;
    };

}