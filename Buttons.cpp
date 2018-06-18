#include "Buttons.h"
#include "Pins.h"

using mbed::InterruptIn;

InterruptIn ButtonAInterrupt(Pokitto::Pins::ButtonAPin);
InterruptIn ButtonBInterrupt(Pokitto::Pins::ButtonBPin);
InterruptIn ButtonCInterrupt(Pokitto::Pins::ButtonCPin);
InterruptIn ButtonUpInterrupt(Pokitto::Pins::ButtonUpPin);
InterruptIn ButtonDownInterrupt(Pokitto::Pins::ButtonDownPin);
InterruptIn ButtonLeftInterrupt(Pokitto::Pins::ButtonLeftPin);
InterruptIn ButtonRightInterrupt(Pokitto::Pins::ButtonRightPin);

using std::size_t;
using Pokitto::Button;

class ButtonStates
{
public:
	static constexpr size_t ButtonCount = static_cast<size_t>(Pokitto::ButtonCount);

private:
	bool buttonStates[ButtonCount];

public:
	bool isPressed(Button button)
	{
		return buttonStates[static_cast<size_t>(button)];
	}
	
	void press(Button button)
	{
		buttonStates[static_cast<size_t>(button)] = true;
	}
	
	void release(Button button)
	{
		buttonStates[static_cast<size_t>(button)] = false;
	}
	
	void setState(Button button, bool state)
	{
		buttonStates[static_cast<size_t>(button)] = state;
	}
};

ButtonStates buttonStates;

#define FORWARD_ACTIONS(button) \
void On##button##Pressed(void) \
{ \
	buttonStates.press(Button::##button); \
} \
 \
void On##button##Released(void) \
{ \
	buttonStates.release(Button::##button); \
}

void OnAPressed(void)
{
	buttonStates.press(Button::A);
}

void OnAReleased(void)
{
	buttonStates.release(Button::A);
}

void OnBPressed(void)
{
	buttonStates.press(Button::B);
}

void OnBReleased(void)
{
	buttonStates.release(Button::B);
}

void OnCPressed(void)
{
	buttonStates.press(Button::C);
}

void OnCReleased(void)
{
	buttonStates.release(Button::C);
}

void OnUpPressed(void)
{
	buttonStates.press(Button::Up);
}

void OnUpReleased(void)
{
	buttonStates.release(Button::Up);
}

void OnDownPressed(void)
{
	buttonStates.press(Button::Down);
}

void OnDownReleased(void)
{
	buttonStates.release(Button::Down);
}

void OnRightPressed(void)
{
	if(buttonStates.isPressed(Button::C))
		Pokitto::Sound::volumeUp();
	else
		buttonStates.press(Button::Right);
}

void OnRightReleased(void)
{
	buttonStates.release(Button::Right);
}

void OnLeftPressed(void)
{
	if(buttonStates.isPressed(Button::C))
		Pokitto::Sound::volumeDown();
	else
		buttonStates.press(Button::Left);
}

void OnRightReleased(void)
{
	buttonStates.release(Button::Left);
}

#define DEFINE_INTERRUPT_HANDLER(number, button) \
void PinInterruptHandler##number(void) \
{ \
	buttonStates.setState(Button::##button, (Button##button##Interrupt.read() != 0)); \
	ClearPinInt(reinterpret_cast<LPC_PIN_INT_T *>(LPC_PININT, PININTCH(number)); \
}

void PinInterruptHandler0(void)
{
	buttonStates.setState(Button::A, (ButtonAInterrupt.read() != 0));
	ClearPinInt(reinterpret_cast<LPC_PIN_INT_T *>(LPC_PININT, PININTCH(0)));
}

void PinInterruptHandler1(void)
{
	buttonStates.setState(Button::B, (ButtonBInterrupt.read() != 0));
	ClearPinInt(reinterpret_cast<LPC_PIN_INT_T *>(LPC_PININT, PININTCH(1)));
}

void PinInterruptHandler2(void)
{
	buttonStates.setState(Button::C, (ButtonCInterrupt.read() != 0));
	ClearPinInt(reinterpret_cast<LPC_PIN_INT_T *>(LPC_PININT, PININTCH(2)));
}

void PinInterruptHandler3(void)
{
	buttonStates.setState(Button::Up, (ButtonUpInterrupt.read() != 0));
	ClearPinInt(reinterpret_cast<LPC_PIN_INT_T *>(LPC_PININT, PININTCH(3)));
}

void PinInterruptHandler4(void)
{
	buttonStates.setState(Button::Down, (ButtonDownInterrupt.read() != 0));
	ClearPinInt(reinterpret_cast<LPC_PIN_INT_T *>(LPC_PININT, PININTCH(4)));
}

void PinInterruptHandler5(void)
{
	buttonStates.setState(Button::C, (ButtonCInterrupt.read() != 0));
	buttonStates.setState(Button::Left, (ButtonLeftInterrupt.read() != 0));
	
	if(buttonStates.isPressed(Button::C) && buttonStates.isPressed(Button::Left))
	{
		if(!volumeControlClicked)
			Pokitto::Sound::volumeDown();
		buttonStates.release(Button::Left);
		volumeControlClicked = true;
	}
	else
		volumeControlClicked = false;
		
	ClearPinInt(reinterpret_cast<LPC_PIN_INT_T *>(LPC_PININT, PININTCH(5)));
}

void PinInterruptHandler6(void)
{
	buttonStates.setState(Button::C, (ButtonCInterrupt.read() != 0));
	buttonStates.setState(Button::Right, (ButtonRightInterrupt.read() != 0));
	
	if(buttonStates.isPressed(Button::C) && buttonStates.isPressed(Button::Right))
	{
		if(!volumeControlClicked)
			Pokitto::Sound::volumeDown();
		buttonStates.release(Button::Right);
		volumeControlClicked = true;
	}
	else
		volumeControlClicked = false;
		
	ClearPinInt(reinterpret_cast<LPC_PIN_INT_T *>(LPC_PININT, PININTCH(6)));
}

#define SET_VECTOR(number) NVIC_SetVector(static_cast<IRQn_Type>(PIN_INT##number##_IRQn), static_cast<uint32_t>(&PinInterruptHandler##number));

void Pokitto::Buttons::initialise(void)
{
	ButtonAInterrupt.rise(OnAPressed);
	ButtonAInterrupt.fall(OnAReleased);
	
	ButtonBInterrupt.rise(OnBPressed);
	ButtonBInterrupt.fall(OnBReleased);
	
	ButtonCInterrupt.rise(OnCPressed);
	ButtonCInterrupt.fall(OnCReleased);
	
	ButtonUpInterrupt.rise(OnUpPressed);
	ButtonUpInterrupt.fall(OnUpReleased);
	
	ButtonDownInterrupt.rise(OnDownPressed);
	ButtonDownInterrupt.fall(OnDownReleased);
	
	ButtonRightInterrupt.rise(OnRightPressed);
	ButtonRightInterrupt.fall(OnRightReleased);
	
	ButtonLeftInterrupt.rise(OnLeftPressed);
	ButtonLeftInterrupt.fall(OnLeftReleased);
	
	NVIC_SetVector(static_cast<IRQn_Type>(PIN_INT0_IRQn), static_cast<uint32_t>(&PinInterruptHandler0));
	NVIC_SetVector(static_cast<IRQn_Type>(PIN_INT1_IRQn), static_cast<uint32_t>(&PinInterruptHandler1));
	NVIC_SetVector(static_cast<IRQn_Type>(PIN_INT2_IRQn), static_cast<uint32_t>(&PinInterruptHandler2));
	NVIC_SetVector(static_cast<IRQn_Type>(PIN_INT3_IRQn), static_cast<uint32_t>(&PinInterruptHandler3));
	NVIC_SetVector(static_cast<IRQn_Type>(PIN_INT4_IRQn), static_cast<uint32_t>(&PinInterruptHandler4));
	NVIC_SetVector(static_cast<IRQn_Type>(PIN_INT5_IRQn), static_cast<uint32_t>(&PinInterruptHandler5));
	NVIC_SetVector(static_cast<IRQn_Type>(PIN_INT6_IRQn), static_cast<uint32_t>(&PinInterruptHandler6));
}
