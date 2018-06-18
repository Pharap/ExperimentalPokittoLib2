
#include <type_traits>

template< uint8_t BitsPerRedValue, uint8_t BitsPerGreenValue, uint8_t BitsPerBlueValue >
class PackedColour
{
public:
	static constexpr uint8_t BitsPerRed = BitsPerRedValue;
	static constexpr uint8_t BitsPerGreen = BitsPerGreenValue;
	static constexpr uint8_t BitsPerBlue = BitsPerBlueValue;
	static constexpr uint32_t TotalBits = BitsPerRed + BitsPerGreen + BitsPerBlue;
	
	//static constexpr uint

	using PackedType =
		typename std::conditional<(TotalBits <= sizeof(uint8_t)), uint8_t,
		typename std::conditional<(TotalBits <= sizeof(uint16_t)), uint16_t,
		typename std::conditional<(TotalBits <= sizeof(uint32_t)), uint32_t,
		typename std::conditional<(TotalBits <= sizeof(uint64_t)), uint64_t,
		typename std::conditional<(TotalBits <= sizeof(uintmax_t)), uintmax_t,
			void > > > > >;
			
	static_assert(!std::is_void<PackedType>::value, "No type large enough to handle specified colour type");
	
private:
	PackedType value;

public:



};