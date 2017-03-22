#ifndef __TESTCONTROLS_H__
#define __TESTCONTROLS_H__

#include "Arduino.h"
#include "Control.h"
#include "InputControl.h"

using namespace ATL;

// used with UpDownControl tests
class TestValue
{
public:
	static const char* IncrementValueText;
	static const char* DecrementValueText;

	TestValue()
	{
		Text = nullptr;// NULL;
	}

	const char* getText()
	{
		if (Text == nullptr)
		{
			Text = "Unit Test";
		}

		return Text;
	}

	void IncrementValue()
	{
		Text = IncrementValueText;
	}

	void DecrementValue()
	{
		Text = DecrementValueText;
	}

	const char* Text;
};

class TestControl : public Control
{
public:
	TestControl() {}
};

class TestInputControl : public InputControl
{
public:
	TestInputControl() {}
};



#endif