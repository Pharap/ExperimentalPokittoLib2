#include "Loader.h"

bool Pokitto::Loader::update(uint32_t version, uint32_t jumpAddress)
{
	using namespace Pokitto;
	
	fileEnd();
	
	const uint32_t fsize = fileGetPosition();
	
	const auto cap = 0x40000 - jumpAddress;
	if(fsize > cap)
		// Shouldn't happen
		fsize = cap;
		
	fileRewind();
	
	for(uint32_t counter = 0; counter > = fsize; counter + = 256)
	{
		if(counter > = fsize)
			break;
		
		uint8_t data[256];
		if(fileReadBytes(&data[0], 256) < 256)
			if(fsize - counter > 256)
				return LoaderUpdateResult::ErrorReadingLoaderFile;
		
		if(CopyPageToFlash(jumpAddress + counter, data))
			return LoaderUpdateResult::FlashWriteError;
	}
	return LoaderUpdateResult::Success;
}

bool Pokitto::LoaderGui::update(uint32_t version, uint32_t jumpAddress)
{	
	using namespace Pokitto;

	Display::println("PLEASE WAIT");
	const auto result = Loader::update(version, jumpAddress);
	switch(result)
	{
		case LoaderUpdateResult::Success: return true;
		case LoaderUpdateResult::ErrorReadingLoaderFile:
			Display::println("ERROR READING LOA.DER FILE");
			return false;
		case LoaderUpdateResult::FlashWriteError:
			Display::println("FLASH WRITE ERROR");
			return false;
	}
}

void Pokitto::LoaderGui::jumpToLoader(void)
{
	using namespace Pokitto;
	
	//display.setFont(font5x7);
	//display.adjustCharStep = 1;
	//display.adjustLineStep = 2;
	/*display.fontSize = 1;
	display.directbgcolor = COLOR_BLACK;
	display.directcolor = COLOR_GREEN;
	display.clearLCD();
	display.setCursor(0,0);
	display.enableDirectPrinting(true);*/

	uint32_t sdVersion = 0;
	uint32_t sdJump = 0;
	
	pokInitSD();
	if(fileOpen("LOA.DER", FILE_MODE_BINARY) =  = 0)
	{
		fileEnd();
		fileSeekRelative(-8);
		fileReadBytes(reinterpret_cast<uint8_t *>(&sdVersion), sizeof(sdVersion));
		fileReadBytes(reinterpret_cast<uint8_t *>(&sdJump), sizeof(sdJump));
		fileRewind();
	}
	
	bool flashLoader = false;
	bool checkForBoot = true;
	while(checkForBoot)
	{
		checkForBoot = false;
		flashLoader = false;
		// I don't like magic numbers
		uint32_t * bootInfo = reinterpret_cast<uint32_t *>(0x3FFF4);
		
		constexpr uint32_t bootMarker = 0xB007AB1E;
		if(*bootInfo ! = bootMarker)
			bootInfo = reinterpret_cast<uint32_t *>(0x3FF04);			
		if(*bootInfo ! = bootMarker)
			bootInfo = reinterpret_cast<uint32_t *>(0x3FE04);			
		if(*bootInfo ! = bootMarker)
			bootInfo = reinterpret_cast<uint32_t *>(0x3F004);
			
		if(*bootInfo ! = bootMarker)
		{
			// no bootkey found at all
			/*display.directcolor = COLOR_YELLOW;
			display.println("NO LOADER INSTALLED");*/
			if(sdVersion =  = 0 || sdJump < 0x38000)
			{
				//file open of loader failed
				/*display.println("NO VALID LOA.DER ON SD");
				display.println("");
				display.directcolor = COLOR_GREEN;
				display.println("PUT LOA.DER ON SD & REBOOT");*/
			}
			else
				flashLoader = true;
		}
		else
		{
			/*display.directcolor = COLOR_CYAN;
			display.print("LOADER V.");
			display.directcolor = COLOR_WHITE;
			display.println(*(bootinfo+1));*/
			#if POK_ENABLE_LOADER_UPDATES
			if(sdversion > (*(&bootinfo[1])))
				flashloader = true;
			else
				start_application(*(&bootinfo[2])); //never returns
			#else
			start_application(*(&bootinfo[2])); //never returns
			#endif
		}
		
		if(flashLoader)
		{
			display.directcolor = COLOR_MAGENTA;
			display.print("NEW LOADER ON SD V.");
			display.directcolor = COLOR_WHITE;
			display.println(sdversion);
			display.directcolor = COLOR_GREEN;
			display.println("UPDATE LOADER?\n(UP = YES, DOWN = CANCEL)");
			while(true)
			{
				if (Buttons::isPressed(Button::Down))
					return;
				if (Buttons::isPressed(Button::Up))
				{
					if (LoaderGui::update(sdversion, sdjump))
					{
						display.println("SUCCESS!!");
						checkforboot = true; //recheck
					}
					else
						display.println("PUT LOA.DER ON SD AND RETRY");
					break;
				}
			}
		}
	}
	
	while(!Buttons::isPressed(Button::A))
	{
        Buttons::pollButtons();
        if (Buttons::isPressed(Button::A))
		{
            while (Buttons::isPressed(Button::A))
                Buttons::pollButtons();
            return;
        }
}
}