#pragma once

#include <cstdint>

namespace Pokitto
{
	enum class Button
	{
		Left = 0,
		Up = 1,
		Right = 2,
		Down = 3,
		A = 4,
		B = 5,
		C = 6,
	};
	
	constexpr uint32_t ButtonCount = 7;
	
	enum class ButtonMode
	{
		Polling = 0x00,
		Interrupt = 0x01,
	};
	
	enum class ButtonState
	{
		Released = 0x00,
		Pressed = 0x01,
		JustReleased = 0x02,
		JustPressed = 0x03,
	};
	
	class Buttons
	{	
	public:
		//Buttons(void) = delete;
		
		static void initialise(ButtonMode mode);
	
		static void update(void);
		
		static bool isPressed(Button button);
	};
}