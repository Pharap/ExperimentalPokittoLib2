#pragma once

#include <cstdint>

namespace Pokitto
{
	class Battery
	{
	private:
		static uint8_t powerLevel;
		
		// ToDo: Figure out the purose of these
		static bool visible;
		static uint16_t voltage;
		// ToDo: Discover value of 'NUM_LVL'
		static uint16_t threshHolds[1];
		static int8_t nextUpdate;
	
	public:
		
		static uint8_t getPowerLevel(void) const
		{
			return this->powerLevel;
		}
	
		static void update(void);
	};
}