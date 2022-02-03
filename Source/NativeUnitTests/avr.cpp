#include "pch.h"
#include "avr.h"

#include "..\MidiMapper\ATL\BitArray.cpp"
#include "..\MidiMapper\ATL\TextFormatInfo.cpp"
#include "..\MidiMapper\Globals.cpp"

void avrSei() {}
void avrCli() {}

void ToggleDebugPin() {}

uint8_t Registers::_memSpace[MAX_MEMSPACE];