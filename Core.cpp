#include "Core.h"





#include <ctime>

// PokittoHW.cpp
uint32_t Pokitto::Core::getRandomSeed(void)
{
	// ToDo: Consider improving with a hash function
	std::time_t currentTime = time(nullptr);
	Pokitto::Battery::update();
	return static_cast<uint32_t>(Pokitto::Battery::getPowerLevel()) + static_cast<uint32_t>(currentTime);
}

// PokittoHW.cpp
void Pokitto::Core::initialiseGpio(void)
{
	// ToDo: Find out what this stuff actually does

	// Control Lines
	LPC_GPIO_PORT->DIR[LCD_CD_PORT] |= (1 << LCD_CD_PIN);
	LPC_GPIO_PORT->DIR[LCD_WR_PORT] |= (1 << LCD_WR_PIN);
	LPC_GPIO_PORT->DIR[LCD_RD_PORT] |= (1 << LCD_RD_PIN);
	LPC_GPIO_PORT->DIR[LCD_RES_PORT] |= (1 << LCD_RES_PIN);
	
	// Data Lines
	// P2_3...P2_18 as output
	LPC_GPIO_PORT->DIR[2] |= (0xFFFF << 3);
	
	// Turn off pull-ups
	pin_mode(P2_3, PullNone);
	pin_mode(P2_4, PullNone);
	pin_mode(P2_5, PullNone);
	pin_mode(P2_6, PullNone);
	pin_mode(P2_7, PullNone);
	pin_mode(P2_8, PullNone);
	pin_mode(P2_9, PullNone);
	pin_mode(P2_10, PullNone);
	pin_mode(P2_11, PullNone);
	pin_mode(P2_12, PullNone);
	pin_mode(P2_13, PullNone);
	pin_mode(P2_14, PullNone);
	pin_mode(P2_15, PullNone);
	pin_mode(P2_16, PullNone);
	pin_mode(P2_17, PullNone);
	pin_mode(P2_18, PullNone);
}