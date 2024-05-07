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
		NONE = 0x0000,

		XINPUT_CONTROLLER_A = 0x1000,
		XINPUT_CONTROLLER_B = 0x2000,
		XINPUT_CONTROLLER_X = 0x4000,
		XINPUT_CONTROLLER_Y = 0x8000,

		XINPUT_GAMEPAD_DRAD_UP = 0x0001,
		XINPUT_GAMEPAD_DRAD_DOWN = 0x0002,
		XINPUT_GAMEPAD_DRAD_LEFT = 0x0004,
		XINPUT_GAMEPAD_DRAD_RIGHT = 0x0008
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
		bool IsPrevious(unsigned int button) override;

		void HandleInput() override;

		void AddCommand(ControllerInput input, std::unique_ptr<class Command> command);

	private:
		int m_ControllerIndex;

		XINPUT_STATE m_InputState{};

		unsigned int m_PressedButtons;
		unsigned int m_ReleasedButtons;
		unsigned int m_PreviousButtons;

		std::unordered_map<ControllerInput, std::unique_ptr<class Command>> m_ButtonBindings;
	};
}
