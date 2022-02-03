// stdafx.cpp : source file that includes just the standard includes
// ArduinoTemplateLibrary.Tests.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#include "TextFormatInfo.h"

// from TextFormatInfo.cpp
namespace ATL {

	char TextFormatInfo::NewLine[] = { '\r', '\n', '\0' };
	uint8_t TextFormatInfo::DecimalDigits = (uint8_t)2;
	char TextFormatInfo::NegativeSign = { '-' };
	char TextFormatInfo::DecimalSeparator = { '.' };
	uint8_t TextFormatInfo::DefaultBase = (uint8_t)TextFormatInfo::baseDecimal;

} // AT:L

uint8_t Registers::_memSpace[MAX_MEMSPACE];