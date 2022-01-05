#include "Program.h"
#include "Globals.h"
#include "DataTypes.h"
#include "PresetManager.h"
#include "MidiStatus.h"
#include "UI/PageManager.h"
#include "Debug.h"

#include "ATL/Debug.h"
#include "ATL/Time.h"
#include "ATL/Delays.h"
#include "ATL/FixedString.h"
#include "ATL/AVR/Time_Avr.h"
#include "ATL/AVR/TimerCounter.h"
#include "ATL/AVR/Interrupt.h"

#include <avr/pgmspace.h>

using namespace ATL;
using namespace ATL::MCU;

// singletons
Program program;
PresetManager PresetManagerInstance(Globals::MemPatch);
MidiStatus CurrentMidiStatus;
PageManager Pages;

static const char SplashLine1[] PROGMEM = "MIDI Master v0.1";
static const char SplashLine2[] PROGMEM = "(C) Canned Bytes 2021";

// char code 246 >
// char code 247 <

NavigationCommands LastNavCmd = NavigationCommands::None;

void Program::Run()
{
    uint32_t deltaTime = TaskScheduler::Update();

    // while() ensures that all midi bytes are processed as one message - as fast as possible
	//while(Globals::MidiInOutPort1.Receive.ReadByte());
//
    //if (Pages.IsCurrentScreen(&Pages.RealtimeScreen))
    //{
        //Pages.RealtimeScreen.DisplayActivity(&Lcd);
    //}

    KeyMatrix.ScanButton();
    auto isActive = KeyMatrix.getIsActive();

	if (isActive &&
		LastNavCmd == NavigationCommands::None)
	{
		LastNavCmd = TranslateKeyToCommand(KeyMatrix.getKeyCode());

		if (Pages.OnNavigationCommand(LastNavCmd))
		{
			Pages.Display(&Lcd);
		}
	}
	else if (!isActive)
	{
		LastNavCmd = NavigationCommands::None;
	}
}

void Program::OpenLcd()
{
	Lcd.Initialize(true);
	Lcd.setEnableDisplay(true);

	FixedString<LcdColumns> temp;
	temp.CopyFromProgMem(SplashLine1);
	Lcd.SetCursor(0, 4);
	Lcd.WriteLine(temp);

	Lcd.SetCursor(1, 1);
	temp.CopyFromProgMem(SplashLine2);
	Lcd.WriteLine(temp);

	Lcd.ReturnHome();
}

 void Program::Initialize()
{
	Globals::MemPatch[0].Clear();
	Globals::MemPatch[1].Clear();
    TimerCounter::Start();

	OpenLcd();
	Globals::OpenMidiPorts();

	Interrupt::EnableAll(true);

    // time to show the splash screen
    Delay<TimeResolution::Milliseconds>::Wait(2000);

    // TEST
    Globals::InitTest();

    Lcd.ClearDisplay();
    Lcd.ReturnHome();

    Pages.TrySetFirstPage();

    Pages.Display(&Lcd);
}

NavigationCommands Program::TranslateKeyToCommand(uint8_t keyCode)
{
    switch(keyCode)
    {
    case KeyLeft:
        return NavigationCommands::Left;
    case KeyRight:
        return NavigationCommands::Right;
    case KeyUp:
        return NavigationCommands::Up;
    case KeyDown:
        return NavigationCommands::Down;
    case KeyEnter:
        return NavigationCommands::Enter;
    case KeyExit:
        return NavigationCommands::Exit;
    default:
        return NavigationCommands::None;
    }
}

int main(void)
{
    program.Initialize();
	
    while (1)
    {
		program.Run();
    }
}


