#include "avr.h"
#include "DisplayWriter.h"
#include "UI/PageManager.h"
#include "PresetManager.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


namespace LCDUITest
{
	[TestClass]
	public ref class LcdUITest
	{
	public: 
		[TestMethod]
		void TestMethod1()
		{
			MidiPatch midiPatch;
			midiPatch.Name = "Test Midi Patch";
			midiPatch.Maps[0]->Name = "U-220";
			midiPatch.Maps[1]->Name = "R-8";
			midiPatch.Maps[2]->Name = "D-110";
			midiPatch.Maps[3]->Name = "VG-99";

			TestDisplay lcd('.');
			PresetManager presetMgr(&midiPatch);
			PageManager pageMgr;
			pageMgr.Display(&lcd, ControlDisplayMode::Normal);
			lcd.ConsoleWrite();
		}
	};
}
