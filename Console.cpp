#pragma once

/*Pokitto::Console(void)
{
	Console::last = 0;
	Console::first = 0;
	Console::pointer = 0;
	Console::counter = 0;
	Console::colour = 0xFFFF;
	Console::mode = ConsoleMode::Overlay | ConsoleMode::Visible;
	Console::mode = ConsoleMode::Overlay;
}*/

void Console::toggle(void)
{
	if(Console::counter > 0)
	{
		Console::mode ^= ConsoleMode::Visible;
		Console::counter = Console::Timeout;
	}
}

static void Console::addMessage(MessageSource messageSource, MessageType messageType)
{
	Console::addMessage(messageSource, messageType, ValueType::None, 0);
}

static void Console::addMessage(MessageType messageType, const char * stringPointer)
{
	Console::addMessage(MessageSource::User, messageType, ValueType::String, reinterpret_cast<uint32_t>(stringPointer));
}

static void Console::addMessage(MessageType messageType, ValueType valueType, uint32_t value)
{
	Console::addMessage(MessageSource::User, messageType, valueType, value);
}

static void Console::addMessage(MessageSource messageSource, MessageType messageType, ValueType valueType, uint32_t value)
{
	Console::messageBuffer[Console::lastIndex] = ConsoleMessage(messageSource, messageType, valueType, value);
	
	++Console::lastIndex;	
	if(Console::lastIndex == Console::BufferSize)
		Console::lastIndex = 0;
		
	Console::firstIndex = Console::lastIndex + 1;
	if(Console::FirstIndex == Console::BufferSize)
		Console::firstIndex = 0;
}

static void Console::selectLast(void)
{
	Console::pointerIndex = Console::lastIndex;
}

static void Console::previous(void)
{
	if(Console::pointerIndex == 0)
		Console::pointerIndex = Console::BufferSize - 1;
	else
		--Console::pointerIndex;
}

static void Console::next(void)
{
	if(Console::pointerIndex == Console::BufferSize - 1)
		Console::pointerIndex = 0;
	else
		++Console::pointerIndex;
}

static void Console::removeLast(void)
{
	Console::selectLast();
	Console::previous();
	
	Console::messageBuffer[Console::pointerIndex] = ConsoleMessage(MessageSource::Null, MessageType::Null, ValueType::None, 0);
	
	Console::lastIndex = Console::pointerIndex;
}

static ConsoleMessage Console::getMessage(void)
{
	return Console::messageBuffer[Console::pointerIndex];
}

/*void Console::First() {
    consmsg c;
    uint16_t outofbounds=0;
    conspointer = consfirst;
    c=GetMessage();
    while (!c.msgsource) {
        Next();
        c=GetMessage();
        outofbounds++;
        if (outofbounds==CONSOLEBUFSIZE) {
            conspointer = consfirst;
            break;
        }
    }
}*/

/*void Console::PrintMessage() {
    consmsg c = msgbuf[conspointer];
    switch (c.msgsource) {
    case MSOURCE_APP:
        _display->print("App:");break;
    case MSOURCE_BATT:
        _display->print("Batt:");break;
    case MSOURCE_BTNA:
        _display->print("A:");break;
    case MSOURCE_BTNB:
        _display->print("B:");break;
    case MSOURCE_BTNC:
        _display->print("C:");break;
    case MSOURCE_BTNU:
        _display->print("Up:");break;
    case MSOURCE_BTND:
        _display->print("Down:");break;
    case MSOURCE_BTNL:
        _display->print("Left:");break;
    case MSOURCE_BTNR:
        _display->print("Right:");break;
    case MSOURCE_LCD:
        _display->print("LCD:");break;
    case MSOURCE_SD:
        _display->print("SD:");break;
    case MSOURCE_SOUND:
        _display->print("Sound:");break;
    case MSOURCE_TIMER:
        _display->print("Timer:");break;
    case MSOURCE_USER:
        _display->print("User:");break;
    case MSOURCE_COLLISION:
        _display->print("Hit:");break;
    default:
        return;
        break;
    }

    switch (c.msgtype) {
    case MSG_OK:
        _display->print("OK ");break;
    case MSG_INIT_OK:
        _display->print("INIT OK ");break;
    case MSG_INIT_FAIL:
        _display->print("INIT FAIL ");break;
    case MSG_WARNING:
        _display->print("WARNING ");break;
    case MSG_FATAL:
        _display->print("FATAL ");break;
    case MSG_GFX_MODE_CHANGE:
        _display->print("MODE ");break;
    case MSG_GFX_MODE_INVALID:
        _display->print("INVALID!");break;
    case MSG_NOT_ENOUGH_MEM:
       _display->print("NOT ENOUGH MEM ");break;
    case MSG_UP:
        _display->print("KEYUP");break;
    case MSG_DOWN:
        _display->print("KEYDOWN");break;
    case MSG_BREAK:
        _display->print("BREAK ");break;
    case MSG_YESNO:
        _display->print("YES(A)/NO(B)");break;
    case MSG_YES:
        _display->print("YES");break;
    case MSG_NO:
        _display->print("NO");break;
    case MSG_OBJECT:
        _display->print("OBJ1: ");break;
    case MSG_OBJECT2:
        _display->print("OBJ2: ");break;
    default:
        _display->print(" ");
    }

    switch (c.valtype) {
    case V_NONE:
        _display->println();break;
    case V_UINT8:
        _display->println((uint16_t)c.val);break;
    case V_INT8:
        _display->println((int16_t)c.val);break;
    case V_UINT16:
        _display->println((uint16_t)c.val);break;
    case V_INT16:
        _display->println((int16_t)c.val);break;
    case V_UINT32:
        _display->println((uint32_t)c.val);break;
    case V_INT32:
        _display->println((int32_t)c.val);break;
    case V_FLOAT:
        _display->println((float)c.val);break;
    case V_STRING:
        _display->println((char*)c.val);break;
    default:
        _display->println();
    }

    if (c.msgtype == MSG_BREAK || c.msgtype == MSG_YESNO) {
        #ifndef POK_SIM
        __disable_irq();    // Disable Interrupts
        #else
        pauseAudio(1);
        visible = false; // avoid loop in loop inside refreshDisplay
        simulator.wait_ms(300);
        #endif
        int rval=0;
        while(!rval) {
                _buttons->pollButtons();
                #ifdef POK_SIM
                    simulator.refreshDisplay();
                #endif // POK_SIM
                if (_buttons->aBtn()) rval = 1;
                if (_buttons->bBtn()) rval = -1;
                }
        /* now remove this message to prevent it from rerunning */
        if (c.msgtype == MSG_YESNO) {
            int8_t* v;
            v = (int8_t*) c.val; //c.val is a pointer to the memory location that receives answer
            *v = rval; // return value through pointer
            msgbuf[conspointer].msgsource = MSOURCE_USER;
            if (rval==1) msgbuf[conspointer].msgtype = MSG_YES;
            else msgbuf[conspointer].msgtype = MSG_NO;
        } else msgbuf[conspointer].msgsource = MSOURCE_NULL;

        #ifndef POK_SIM
        __enable_irq();     // Enable Interrupts
        #else
        pauseAudio(0);
        visible = true;
        #endif
    }
}*/

/*void Console::Draw() {
    unsigned char* oldfont;
    int16_t oldx,oldy;
    uint16_t oldcolor;
    uint8_t oldsize;
    bool oldenable;
    oldfont = (unsigned char*) _display->font;
    oldx = _display->cursorX;
    oldy = _display->cursorY;
    oldcolor = _display->directcolor;
    oldsize = _display->fontSize;
    if (!(mode & CONS_OVERLAY)) _display->clearLCD();
    _display->setFont(font5x7);
    _display->fontSize=1;
    _display->setCursor(0,0);
    _display->directcolor=color;
    First();
    while(conspointer!=conslast) {
        PrintMessage();
        Next();
        if (GetMessage().msgsource==MSOURCE_NULL) break;
    }
    _display->font = oldfont;
    _display->fontSize = oldsize;
    _display->cursorX = oldx;
    _display->cursorY = oldy;
    _display->directcolor = oldcolor;
}*/