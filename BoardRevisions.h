#pragma once

namespace Pokitto
{
	template< unsigned int BoardRevisionNumber > struct BoardRevision;

	template<>
	struct BoardRevision<1>
	{
		static constexpr uint32_t CDPort = 0;
		static constexpr uint32_t CDPin = 2;
		static constexpr uint32_t WRPort = 1;
		static constexpr uint32_t WRPin = 23;
		static constexpr uint32_t RDPort = 1;
		static constexpr uint32_t RDPin = 24;
		static constexpr uint32_t RESPort = 1;
		static constexpr uint32_t RESPin = 28;
	};

	template<>
	struct BoardRevision<2>
	{
		static constexpr uint32_t CDPort = 0;
		static constexpr uint32_t CDPin = 2;
		static constexpr uint32_t WRPort = 1;
		static constexpr uint32_t WRPin = 12;
		static constexpr uint32_t RDPort = 1;
		static constexpr uint32_t RDPin = 24;
		static constexpr uint32_t RESPort = 1;
		static constexpr uint32_t RESPin = 0;
	};
}