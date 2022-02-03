#include "avr.h"

#include "..\ATL\BitArray.cpp"
#include "..\ATL\TextFormatInfo.cpp"
#include "..\Globals.cpp"

void avrSei() {}
void avrCli() {}

void ToggleDebugPin() {}

uint8_t Registers::_memSpace[MAX_MEMSPACE];