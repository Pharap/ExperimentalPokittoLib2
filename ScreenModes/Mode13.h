#pragma once

namespace Pokitto
{
	namespace Mode14
	{
		struct Settings
		{
			static constexpr uint8_t Width = 110;
			static constexpr uint8_t Height = 88;
			static constexpr size_t ScreenBufferSize = (static_cast<size_t>(Width) * static_cast<size_t>(Height)) / 2;
		};
	}
}