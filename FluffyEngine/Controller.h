#pragma once
#include "BaseInputDevice.h"
#include <unordered_map>
#include <memory>
#include <sstream>
#include <type_traits>
#include <string>
#include <Xinput.h>

namespace Fluffy
{
	enum class Button : unsigned int
	{
		NONE = 0,

		GAMEPAD_A = XINPUT_GAMEPAD_A,
		GAMEPAD_B = XINPUT_GAMEPAD_B,
		GAMEPAD_X = XINPUT_GAMEPAD_X,
		GAMEPAD_Y = XINPUT_GAMEPAD_Y,

		GAMEPAD_DPAD_UP = XINPUT_GAMEPAD_DPAD_UP,
		GAMEPAD_DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		GAMEPAD_DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		GAMEPAD_DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
	};

	struct ControllerInput
	{
		Button button;
		InputState inputState;

		bool operator!=(const ControllerInput& other) const;
		bool operator==(const ControllerInput& other) const;
	};
}

template <>
struct std::hash<Fluffy::ControllerInput>
{
	auto operator()(const Fluffy::ControllerInput& input) const -> size_t
	{
		std::stringstream hashStr;
		hashStr << unsigned int(input.button) << unsigned int(input.inputState);

		return std::hash<std::string>()(hashStr.str());
	}
};

namespace Fluffy
{
	class Controller final : public BaseInputDevice
	{
	public:
		Controller() = default;
		~Controller() = default;

		Controller(const Controller& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller(Controller&& other) noexcept = delete;
		Controller& operator=(Controller&& other) noexcept = delete;

		void Update() override;

		bool IsPressed(unsigned int button) override;
		bool IsReleased(unsigned int button) override;
		bool IsHeld(unsigned int button) override;

		void HandleInput() override;

		void AddCommand(ControllerInput input, std::unique_ptr<class Command> command);

	private:
		int m_ControllerIndex{};

		XINPUT_STATE m_InputState{};

		unsigned int m_PressedButtons{};
		unsigned int m_ReleasedButtons{};
		unsigned int m_PreviousButtons{};

		std::unordered_map<ControllerInput, std::unique_ptr<class Command>> m_ButtonBindings{};
	};
}
