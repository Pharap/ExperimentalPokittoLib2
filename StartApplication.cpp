#include "StartApplication.h"

// Start the user application
// https://community.nxp.com/thread/417695
//

void start_application(unsigned long app_link_location);
{
	// Disable interrupt requests in preparation for altering the interrupt vectors
	__disable_irq();
	
	// Completely disable button interrupts
	LPC_PINT->IENR = 0;
	LPC_PINT->IENF = 0;
	
	// Disable SysTick
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk & ~(SysTick_CTRL_ENABLE_Msk);
	
	// Power-down USB PHY
	LPC_SYSCON->PDRUNCFG |= (1 << 10);
	
	// Power-down USB PLL
	LPC_SYSCON->PDRUNCFG |= (1 << 8);

	// Reset clock source to IRC
	
	// Update MCLK Clock Source
	LPC_SYSCON->MAINCLKUEN = 0x01;
	
	// Toggle Update Register
	LPC_SYSCON->MAINCLKUEN = 0x00;
	
	// Wait Until Updated
	while (LPC_SYSCON->MAINCLKUEN & 0x01);
	
	// Switch clock selection to IRC
	
	// Select Clock Source
	LPC_SYSCON->MAINCLKSEL = 0;
	
	// Update MCLK Clock Source
	LPC_SYSCON->MAINCLKUEN = 0x01;
	
	// Toggle Update Register
	LPC_SYSCON->MAINCLKUEN = 0x00;
	
	// Wait Until Updated
	while (LPC_SYSCON->MAINCLKUEN & 0x01);
	
	// Disable PLL clock output
	LPC_SYSCON->SYSPLLCLKUEN = 0;
	
	while (LPC_SYSCON->SYSPLLCLKUEN & 0x00);
	
	LPC_SYSCON->SYSPLLCTRL = 0;

	// Kill peripherals
	
	LPC_SYSCON->MAINCLKSEL = 0;
	
	// Disable all peripherals
	LPC_SYSCON->PRESETCTRL = 0;

	// Power-down PLL
	// Does this need to be volatile?
	volatile uint32_t tmp;
	tmp = (LPC_SYSCON->PDRUNCFG & 0x000025FFL);
	tmp |= ((1 << 7) & 0x000025FFL);
	
	// Power-down SYSPLL
	LPC_SYSCON->PDRUNCFG = (tmp | 0x0000C800L);

	//Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_IRC); //switch to IRC

	// Clear all gpio states
	LPC_GPIO_PORT->PIN[0] = 0;
	LPC_GPIO_PORT->PIN[1] = 0;
	LPC_GPIO_PORT->PIN[2] = 0;

	// Change vector table address
	SCB->VTOR = app_link_location;
	#if defined(__ARMCC_VERSION)
	uint32_t * app_loc = reinterpret_cast<uint32_t *>(app_link_location);
	__set_MSP (app_loc[0]);
		
	reinterpret_cast<void (*)(void)>(app_loc[1])();
	#else
	asm(" mov r0, %[address]" : : [address] "r" (app_link_location));
	// Get the stack pointer value from the program's reset vector
	asm(" ldr r1, [r0,#0]");
	// Copy the value to the stack pointer
	asm(" mov sp, r1");
	// Get the program counter value from the program's reset vector
	asm(" ldr r0, [r0,#4]");
	// Jump to the' start address
	asm(" blx r0");
	#endif
}