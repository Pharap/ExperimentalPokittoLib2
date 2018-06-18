#pragma once

#include "Settings.h"
#include "Buttons.h"

#include <cstdint>

namespace Pokitto
{
	enum class ValueType : uint8_t
	{
		None,
		UInt8,
		Int8,
		UInt16,
		Int16,
		UInt32,
		Int32,
		Float,
		String,
	};
	
	enum class MessageSource : uint8_t
	{
		Null,
		Sd,
		Lcd,
		Sound,
		Timer,
		ButtonA,
		ButtonB,
		ButtonC,
		ButtonUp,
		ButtonDown,
		ButtonLeft,
		ButtonRight,
		Battery,
		Application,
		User,
		Collision,
	}

	enum class MessageType : uint8_t
	{
		Null,
		Ok,
		Warning,
		InitOk,
		InitFail,
		NotEnoughMemory,
		GraphicsModeChange,
		GraphicsModeInvalid,
		Up,
		Down,
		Print,
		Break,
		YesNo,
		Yes,
		No,
		Object,
		Object2,
				
		Fatal = 255,
	};

	class ConsoleMessage
	{
	public:
		MessageType messageType;
		MessageSource messageSource;
		ValueType valueType;
		uint32_t value;

	public:
		ConsoleMessage(void) = default;
		ConsoleMessage(MessageType messageType, MessageSource messageSource, ValueType valueType uint32_t value)
			: messageType(messageType), messageSource(messageSource), valueType(valueType), value(value)
		{		
		}
	};

	enum class ConsoleModes
	{
		Overlay = (1 << 0),
		Pause = (1 << 1),
		Step = (1 << 2),
		Visible = (1 << 3),
	};
	
	inline constexpr ConsoleModes operator |(ConsoleModes left, ConsoleModes right)
	{
		return static_cast<ConsoleModes>(static_cast<uint32_t>(left) | static_cast<uint32_t>(right));
	}
	
	inline ConsoleModes & operator |=(ConsoleModes & left, ConsoleModes right)
	{
		left = left | right;
		return left;
	}
	
	inline constexpr ConsoleModes operator &(ConsoleModes left, ConsoleModes right)
	{
		return static_cast<ConsoleModes>(static_cast<uint32_t>(left) & static_cast<uint32_t>(right));
	}
	
	inline ConsoleModes & operator &=(ConsoleModes & left, ConsoleModes right)
	{
		left = left & right;
		return left;
	}
	
	inline constexpr ConsoleModes operator ^(ConsoleModes left, ConsoleModes right)
	{
		return static_cast<ConsoleModes>(static_cast<uint32_t>(left) ^ static_cast<uint32_t>(right));
	}
	
	inline ConsoleModes & operator ^=(ConsoleModes & left, ConsoleModes right)
	{
		left = left ^ right;
		return left;
	}
	
	//
	// Console implements a circular buffer of messsages
	//
	class Console
	{
	public:
		static constexpr auto BufferSize = Pokitto::Settings::ConsoleBufferSize;
		static constexpr uint16_t Timeout = 20;
	
	private:
		static ConsoleMessage messageBuffer[BufferSize];
		static uint8_t lastIndex = 0;
		static uint8_t firstIndex = 0;
		static uint8_t pointerIndex = 0;
	
		static uint16_t counter = 0;
		static uint16_t colour = 0xFFFF;
		static ConsoleModes mode;
		// Visible is only ever written to?
		static bool visible;
	
	public:
		//Console(void);
		
		static void toggle(void);
		static void addMessage(MessageSource messageSource, MessageType messageType);
		static void addMessage(MessageType messageType, const char * stringPointer);
		static void addMessage(MessageType messageType, ValueType valueType, uint32_t value);
		static void addMessage(MessageSource messageSource, MessageType messageType, ValueType valueType, uint32_t value);
		
		static void selectFirst(void);
		static void selectLast(void);
		static void previous(void);
		static void next(void);
		
		static void removeLast();
		
		static ConsoleMessage getMessage(void);
		static void printMessage(void);
		
		// purge not implemented?
		//static void purge(void);
	};
}