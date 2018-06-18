#pragma once

namespace Pokitto
{
	enum class LoaderUpdateResult
	{
		None,
		Success,
		UnexpectedError,
		ErrorReadingLoaderFile,
		FlashWriteError,
	};
	
	class Loader
	{
	private:
	
	public:
		static LoaderUpdateResult update(uint32_t version, uint32_t jumpAddress);
	};
	
	class LoaderGui
	{
	private:
	
	public:
		static bool update(uint32_t version, uint32_t jumpAddress);	
		static void jumpToLoader(void);
	};
}