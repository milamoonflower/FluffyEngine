#pragma once
#include "BaseInputDevice.h"
#include <SDL_scancode.h>
#include <unordered_map>
#include <memory>
#include <sstream>

namespace Fluffy
{
	struct KeyboardInput
	{
		SDL_Scancode key;
		InputState inputState;

		bool operator!=(const KeyboardInput& other) const
		{
			return	key != other.key ||
				inputState != other.inputState;
		}

		bool operator==(const KeyboardInput& other) const
		{
			return !(*this != other);
		}
	};
}

template <>
struct std::hash<Fluffy::KeyboardInput>
{
	auto operator()(const Fluffy::KeyboardInput& input) const -> size_t
	{
		std::stringstream hashStr;
		hashStr << unsigned int(input.key) << unsigned int(input.inputState);

		return std::hash<std::string>()(hashStr.str());
	}
};

namespace Fluffy
{
	class Keyboard final : public BaseInputDevice
	{
	public:
		Keyboard() = default;
		~Keyboard() = default;

		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;

		void Update() override;

		bool IsPressed(unsigned int key) override;
		bool IsReleased(unsigned int key) override;
		bool IsPrevious(unsigned int key) override;

		void HandleInput() override;

		void AddCommand(KeyboardInput input, std::unique_ptr<class Command> command);

	private:
		std::vector<Uint8> m_PressedKeys;
		std::vector<Uint8> m_ReleasedKeys;
		std::vector<Uint8> m_PreviousKeys;

		std::unordered_map<KeyboardInput, std::unique_ptr<class Command>> m_KeyBindings;
	};
}
