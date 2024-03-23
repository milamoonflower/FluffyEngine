#pragma once

enum class InputState : unsigned int
{
	Pressed,
	Released,
	Previous
};

class BaseInputDevice
{
public:
	virtual ~BaseInputDevice() = default;

	virtual void Update() = 0;

	virtual bool IsPressed(unsigned int) = 0;
	virtual bool IsReleased(unsigned int) = 0;
	virtual bool IsPrevious(unsigned int) = 0;

	virtual void HandleInput() = 0;
};
