#pragma once

#include "..\MidiMapper\ATL\DisplayWriter.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define MaxLines 2
#define MaxCols 24

class TestDisplay : public ATL::DisplayWriter
{
public:
	TestDisplay(const char fillChar)
		: _fillChar(fillChar)
	{
		ClearDisplay();
	}

	void Display(const char* text) override
	{
		auto len = strlen(text);
		if (len + _posCol > MaxCols) Assert::Fail(L"Text goes past end of display.");
		if (_posLine >= MaxLines) Assert::Fail(L"Text goes past end of display.");

		memcpy(_lines[_posLine] + _posCol, text, len);
		_posCol += len;
	}

	void GoTo(uint8_t lineIndex, uint8_t columnIndex) override
	{
		if (lineIndex != ATL::DisplayWriter::CurrentPos)
			_posLine = lineIndex;
		if (columnIndex != ATL::DisplayWriter::CurrentPos)
			_posCol = columnIndex;
	}

	void EnableCursor(uint8_t lineIndex, uint8_t columnIndex, bool edit) override
	{ }

	void ClearDisplay()
	{
		memset(_lines, _fillChar, MaxLines * (MaxCols + 1));
		_lines[0][MaxCols] = 0;
		_lines[1][MaxCols] = 0;
	}

	void ReturnHome()
	{
		_posLine = 0;
		_posCol = 0;
	}

	void ConsoleWrite()
	{
		Logger::WriteMessage(_lines[0]);
		Logger::WriteMessage("\r\n");
		Logger::WriteMessage(_lines[1]);
		Logger::WriteMessage("\r\n");
	}

private:
	const char _fillChar;
	char _lines[MaxLines][MaxCols + 1];
	uint8_t _posLine;
	uint8_t _posCol;
};
