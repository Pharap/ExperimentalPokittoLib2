

enum class ScreenModeType
{
	Undefined,
	RasterMode,
	TileMode,
	SpriteMode,
};

enum class ColourMode
{
	Undefined,
	Paletted,
};

enum class DrawMode
{
	Undefined,
	
	// Colour data is drawn to a screen buffer
	Buffered,
	
	// Colour data is drawn directly
	Direct,
};