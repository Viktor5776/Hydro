#pragma once
#include <functional>
#include <string>

namespace hydro::input
{
#include "SDLScancodes.h"

	using KeyCode = SDL_Scancode;

	enum class InputDeviceType {
		Keyboard,
		MouseButton
	};

	enum class InputEventType {
		Pressed,
		Released
	};

	enum class MouseButton {
		Left,
		Right,
		Middle,
		Side1,
		Side2
	};

	struct InputBinding {
		InputDeviceType device;
		union
		{
			KeyCode key;
			MouseButton mouseBtn;
		};

		InputBinding(KeyCode k) : device(InputDeviceType::Keyboard), key(k) {}
		InputBinding(MouseButton m) : device(InputDeviceType::MouseButton), mouseBtn(m) {}

		bool operator==(const InputBinding& other) const {
			if (device != other.device) return false;
			switch (device) {
			case InputDeviceType::Keyboard: return key == other.key;
			case InputDeviceType::MouseButton: return mouseBtn == other.mouseBtn;
			default: return false;
			}
		}
	};

	struct Vec2
	{
		float x;
		float y;
	};

	struct MouseState {
		Vec2 position{ 0.0f,0.0f };
		Vec2 delta{ 0.0f,0.0f };
		Vec2 scroll{ 0.0f,0.0f };
		bool isInWindow = false;
	};

	using InputCallback = std::function<void(const std::string& actionName, InputEventType eventType, MouseState mouseState)>;

	class IInput
	{
	public:
		virtual ~IInput() = default;
		
		virtual void BindAction(const std::string& actionName, const InputBinding& binding) = 0;
		virtual void RegisterActionCallback(const std::string& actionName, InputCallback callback) = 0;

		virtual bool IsActionPressed(const std::string& actionName) const = 0;
		virtual bool IsActionHeld(const std::string& actionName) const = 0;
		virtual bool IsActionReleased(const std::string& actionName) const = 0;

		virtual const MouseState& GetMouseState() const = 0;

		Vec2 GetMousePosition() const { return GetMouseState().position; };
		Vec2 GetMouseDelta() const { return GetMouseState().delta; };
		float GetScrollDelta() const { return GetMouseState().scroll.y; };
		bool IsMouseInWindow() const { return GetMouseState().isInWindow; }

		virtual bool LoadBindingsFromFile(const std::string& path) = 0;
		virtual bool SaveBindingsToFile(const std::string& path) const = 0;
	};
}