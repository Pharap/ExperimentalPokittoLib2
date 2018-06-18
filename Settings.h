#pragma once

#include <cstdint>

namespace Pokitto
{
	struct Settings
	{	
		// True to include SD library
		static constexpr bool EnableSD = true;
		
		// How many seconds the loader waits for the C button to be pressed
		static constexpr uint32_t LoaderCountdown = 3;
		
		// True to ???
		static constexpr bool EnableFpsCounter = false;
		
		// True to refresh the display when waiting
		static constexpr bool EnableRefreshWithWaith = false;
		
		// True if console debug is available
		static constexpr bool EnableConsole = false;
		
		// 
		static constexpr bool EnableConsoleVisibleAtStartup = false;
		
		// 
		static constexpr uint32_t ConsoleInterval = 1000;
	
	#if defined(PROJECT_BOARD_REVISION)
		static constexpr uint32_t BoardRevision = static_cast<uint32_t>(PROJECT_BOARD_REVISION);
	#else
		static constexpr uint32_t BoardRevision = 2;
	#endif

	#if defined(PROJECT_ENABLE_LOGO)
		static constexpr bool EnableLogo = static_cast<bool>(PROJECT_ENABLE_LOGO);
	#else
		static constexpr bool EnableLogo = true;
	#endif

	#if defined(PROJECT_ENABLE_SOUND)
		static constexpr bool EnableSound = static_cast<bool>(PROJECT_ENABLE_SOUND);
	#else
		static constexpr bool EnableSound = true;
	#endif

	#if defined(PROJECT_ENABLE_BUFFERED_SOUND)
		static constexpr bool EnableBufferedSound = static_cast<bool>(PROJECT_ENABLE_BUFFERED_SOUND);
	#else
		static constexpr bool EnableBufferedSound = false;
	#endif

	#if defined(PROJECT_ENABLE_STREAMING_MUSIC)
		static constexpr bool EnableStreamingMusic = static_cast<bool>(PROJECT_ENABLE_STREAMING_MUSIC);
	#else
		static constexpr bool EnableStreamingMusic = false;
	#endif

	#if defined(PROJECT_ENABLE_SYNTH)
		static constexpr bool EnableSynth = static_cast<bool>(PROJECT_ENABLE_SYNTH);
	#else
		static constexpr bool EnableSynth = false;
	#endif

	#if defined(PROJECT_ENABLE_GB_SOUND)
		static constexpr bool EnableGBSound = static_cast<bool>(PROJECT_ENABLE_GB_SOUND);
	#else
		static constexpr bool EnableGBSound = false;
	#endif

	};
}