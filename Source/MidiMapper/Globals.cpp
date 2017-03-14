#include "Globals.h"
#include "ATL/AVR/UsartConfig.h"
#include <avr/Interrupt.h>

using namespace ATL;
using namespace ATL::MCU;

MidiPatch Globals::MemPatch[];
MidiInOutPort1T<Globals> Globals::MidiInOutPort1;
MidiOutPort2T Globals::MidiOutPort2;
BitArray<uint8_t> Globals::MidiStatus;

void Globals::OpenMidiPorts()
{
    UsartConfig config;
    config.InitAsync(MIDI_BAUDRATE);
    
    MidiInOutPort1.OpenAsync(config);
    MidiInOutPort1.Receive.setEnable();
    MidiInOutPort1.Transmit.setEnable();
    
    MidiOutPort2.OpenAsync(config);
    MidiOutPort2.Transmit.setEnable();
    
    MidiInOutPort1.Receive.setEnableIsCompleteInterrupt();
}

ISR(USART0_RX_vect)
{
    Globals::MidiInOutPort1.Receive.OnIsCompleteInterrupt();
}

ISR(USART0_UDRE_vect)
{
    Globals::MidiInOutPort1.Transmit.OnAcceptDataInterrupt();
}

ISR(USART1_UDRE_vect)
{
    Globals::MidiOutPort2.Transmit.OnAcceptDataInterrupt();
}
