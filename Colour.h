#pragma once

#include <cstdint>

namespace Pokitto
{
	/*uint16_t Rgb888ToRgb565(uint8_t red, uint8_t green, uint8_t blue)
	{	
		// 3 = (8 - 5)
		uint16_t result = (red >> 3);
		
		result <<= 6;
		
		// 2 = (8 - 6)
		result |= (green >> 2);
		
		result <<= 5;
		
		// 3 = (8 - 5)
		result |= (blue >> 3);
		
		return result;
	}*/
	
	/*constexpr uint16_t ConstRgb888ToRgb565(uint8_t red, uint8_t green, uint8_t blue)
	{
		return		
		(static_cast<uint16_t>(red & 0xF8) << 8) |
		(static_cast<uint16_t>(green & 0xFC) << 3) |
		(static_cast<uint16_t>(blue & 0xF8) >> 3);
	}*/

	class ColourRgb565
	{
	public:
		static constexpr uint8_t RedMask = 0x1F;		
		static constexpr uint8_t GreenMask = 0x1F;
		static constexpr uint8_t BlueMask = 0x1F;
		
		static constexpr uint8_t RedShift = 11;		
		static constexpr uint8_t GreenShift = 5;
		static constexpr uint8_t BlueShift = 0;
		
	private:
		constexpr uint16_t internalFromRgb888(uint8_t red, uint8_t green, uint8_t blue)
		{
			return		
			(static_cast<uint16_t>(red & 0xF8) << 8) |
			(static_cast<uint16_t>(green & 0xFC) << 3) |
			(static_cast<uint16_t>(blue & 0xF8) >> 3);
		}
		
		constexpr uint16_t internalFromRgb565(uint8_t red, uint8_t green, uint8_t blue)
		{
			return		
			(static_cast<uint16_t>(red & RedMask) << RedShift) |
			(static_cast<uint16_t>(green & GreenMask) << GreenShift) |
			(static_cast<uint16_t>(blue & BlueMask) << BlueShift);
		}
			
	private:
		uint16_t value;
	
	public:
		constexpr ColourRgb565(void) = default;
	
		constexpr ColourRgb565(uint16_t rawValue)
			: value(value)
		{
		}

		constexpr uint8_t getRed(void) const
		{
			return static_cast<uint8_t>((this->value >> RedShift) & RedMask);
		}

		constexpr uint8_t getGreen(void) const
		{
			return static_cast<uint8_t>((this->value >> GreenShift) & GreenMask);
		}

		constexpr uint8_t getBlue(void) const
		{
			return static_cast<uint8_t>((this->value >> BlueShift) & BlueMask);
		}
		
		constexpr uint16_t getValue(void) const
		{
			return this->value;
		}
		
		constexpr explicit operator uint16_t(void) const
		{
			return this->value;
		}
		
		constexpr static ColourRgb565 fromRgb888(uint8_t red, uint8_t green, uint8_t blue)
		{
			return ColourRgb565(internalFromRgb888(red, green, blue));
		}
		
		constexpr static ColourRgb565 fromRgb565(uint8_t red, uint8_t green, uint8_t blue)
		{
			return ColourRgb565(internalFromRgb565(red, green, blue));
		}
	};

	inline ColourRgb565 interpolate(ColourRgb565 colour0, ColourRgb565 colour1, uint8_t factor)
	{
		const int16_t blue0 = colour0.getBlue();
		const int16_t blue1 = colour1.getBlue();
		const int16_t blueFinal = std::max(blue0 + ((blue1 - blue0) * factor) >> 8), 0);
		
		const int16_t green0 = colour0.getGreen();
		const int16_t green1 = colour1.getGreen();
		const int16_t greenFinal = std::max(green0 + ((green1 - green0) * factor) >> 8), 0);
		
		const int16_t red0 = colour0.getRed();
		const int16_t red1 = colour1.getRed();
		const int16_t redFinal = std::max(red0 + ((red1 - red0) * factor) >> 8), 0);
		
		const uint16_t value = (blueFinal << 0) | (greenFinal << 5) | (redFinal << 11);
		
		return ColourRgb565(value);
	}
	
	template< size_t size >
	void interpolateColourArray(ColourRgb565 (&destination)[size], const ColourRgb565 (&source0)[size], const ColourRgb565 (&source1)[size], uint8_t factor)
	{
		for(size_t index = 0; index < size; ++index)
			destination[index] = interpolate(source0[index], source1[index], factor);
	}
	
	template< size_t destinationSize, size_t size0, size_t size1 >
	void interpolateColourArray(ColourRgb565 (&destination)[destinationSize], const ColourRgb565 (&source0)[size0], const ColourRgb565 (&source1)[size1], uint8_t factor)
	{
		#if (__cplusplus > 201402L)
		// Cannot assume constexpr std::min unless C++14 is guaranteed
		constexpr size_t size = std::min(destinationSize, std::min(size0, size1));
		#else
		constexpr size_t size = (destinationSize < size0 && destinationSize < size1) ? destinationSize : (size0 < size1) ? size0 : size1;
		#endif
		
		for(size_t index = 0; index < size; ++index)
			destination[index] = interpolate(source0[index], source1[index], factor);
	}
}