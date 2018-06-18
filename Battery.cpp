#include "Battery.h"
#include "Pins.h"

using mbed::AnalogIn;

AnalogIn BatteryInput = AnalogIn(Battery2Pin);

void Battery::update(void)
{
	// ToDo: Clarify the purpose of the * 0xFF
	powerLevel = BatteryInput.read() * 0xFF;
}