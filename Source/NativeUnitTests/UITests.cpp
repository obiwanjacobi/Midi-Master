#include "pch.h"
#include "CppUnitTest.h"
#include "../MidiMapper/UI/PageManager.h"
#include "../MidiMapper/PresetManager.h"
#include "TestDisplay.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NativeUnitTests
{
	TEST_CLASS(UITests)
	{
	public:
		
		TEST_METHOD(RealtimePage)
		{
			MidiPatch midiPatch;
			midiPatch.Name = "Tst Midi Patch";
			midiPatch.Maps[0]->Name = "U-220";
			midiPatch.Maps[1]->Name = "R-8";
			midiPatch.Maps[2]->Name = "D-110";
			midiPatch.Maps[3]->Name = "VG-99";

			TestDisplay lcd('.');
			PresetManager presetMgr(&midiPatch);
			PageManager pageMgr;

			Assert::IsTrue(pageMgr.TrySetFirstPage());
			pageMgr.Display(&lcd, ControlDisplayMode::Normal);
			lcd.ConsoleWrite();
		}
	};
}
