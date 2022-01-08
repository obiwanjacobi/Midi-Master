#include "Debug.h"
#include "Program.h"
#include "ATL/Debug.h"
#include "ATL/AVR/Delay_avr.h"
#include "ATL/AVR/DigitalOutputPin.h"
#include "ATL/AVR/Port.h"

uint8_t DebugCol = 0;

void ATL::AtlDebugWrite(const char* message)
{
    auto program = Program::getCurrent();
    uint8_t c = program->Lcd.getCursorCol();
    uint8_t r = program->Lcd.getCursorRow();

    program->Lcd.SetCursor(1, DebugCol);
    program->Lcd.Write(message);

    DebugCol = program->Lcd.getCursorCol();
    if (DebugCol > 24)
    DebugCol = 0;

    // restore position
    program->Lcd.SetCursor(r, c);
}

//bool ATL::AtlDebugLevel(uint8_t componentId, DebugLevel level)
//{
////return Bit<7>::IsTrue(componentId);
//return true;
//}

ATL::MCU::DigitalOutputPin<Ports::PortD, Pins::Pin7> debugPin;

void ToggleDebugPin()
{
    debugPin.Write(true);
    Delay<TimeResolution::Milliseconds>::Wait(200);
    debugPin.Write(false);
    Delay<TimeResolution::Milliseconds>::Wait(200);
}
