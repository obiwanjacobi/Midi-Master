#include "stdafx.h"
#include "TestInputStream.h"
#include "Midi.h"
#include "MidiMessage.h"
#include "MidiReader.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	// helper class that implements Midi event handlers.
	public class MidiReaderBase : public TestInputStream
	{
	public:
		MidiReaderBase()
		{
			RealtimeStatus = Midi::InvalidType;
		}

		void OnMessage(MidiMessage* midiMsg)
		{
			midiMsg->CopyTo(&MidiMsg);
		}

		MidiMessage MidiMsg;

		void OnRealtime(Midi::MessageTypes midiStatus)
		{
			RealtimeStatus = midiStatus;
		}

		Midi::MessageTypes RealtimeStatus;

		void OnSysEx(void* obj)
		{
			Assert::Fail("SysEx is not implemented yet!");
		}
	};

	[TestClass]
	public ref class MidiReaderTest
	{
	public: 
		[TestMethod]
		void InitBufferWithNoteOn_Read_FiresChannelMessageEvent()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0x40, 0x70 };
			midiReader.InitInputStream(buffer, 3);

			while(midiReader.ReadByte());

			AssertMidiMessage(&midiReader.MidiMsg,
				Midi::NoteOn, 1, 0x40, 0x70);
		}

		[TestMethod]
		void InitBufferWithChannelAndRealtime_Read_FiresChannelMessageAndRealtimeEvent()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0x40, 0xFF, 0x70 };
			midiReader.InitInputStream(buffer, 4);

			while(midiReader.ReadByte());

			AssertMidiMessage(&midiReader.MidiMsg,
				Midi::NoteOn, 1, 0x40, 0x70);

			// realtime interleaved midi message
			Assert::AreEqual((int)Midi::SystemReset, (int)midiReader.RealtimeStatus);
		}

		[TestMethod]
		void InitBufferWithChannelAndRealtime_Read_FiresChannelMessageAndRealtimeEvent_AtDifferentSpot()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0xFF, 0x40, 0x70 };
			midiReader.InitInputStream(buffer, 4);

			while(midiReader.ReadByte());

			AssertMidiMessage(&midiReader.MidiMsg,
				Midi::NoteOn, 1, 0x40, 0x70);

			// realtime interleaved midi message
			Assert::AreEqual((int)Midi::SystemReset, (int)midiReader.RealtimeStatus);
		}

		[TestMethod]
		void InitBufferWithMultipleChannelMessages_Read_FiresChannelMessageEvents()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0x40, 0x70, 0x81, 0x44, 0x68  };
			midiReader.InitInputStream(buffer, 6);

			for(int i = 0; i < 3; i++)
				Assert::IsTrue(midiReader.ReadByte());

			AssertMidiMessage(&midiReader.MidiMsg,
				Midi::NoteOn, 1, 0x40, 0x70);

			for(int i = 0; i < 3; i++)
				Assert::IsTrue(midiReader.ReadByte());

			AssertMidiMessage(&midiReader.MidiMsg,
				Midi::NoteOff, 1, 0x44, 0x68);
		}

		[TestMethod]
		void InitBufferWithRunningStatusChannelMessages_Read_FiresChannelMessageEvents()
		{
			MidiReader<MidiReaderBase> midiReader;

			unsigned char buffer[] = { 0x91, 0x40, 0x70, 0x44, 0x68  };
			midiReader.InitInputStream(buffer, 5);

			for(int i = 0; i < 3; i++)
				Assert::IsTrue(midiReader.ReadByte());

			AssertMidiMessage(&midiReader.MidiMsg,
				Midi::NoteOn, 1, 0x40, 0x70);

			for(int i = 0; i < 2; i++)
				Assert::IsTrue(midiReader.ReadByte());

			AssertMidiMessage(&midiReader.MidiMsg,
				Midi::NoteOn, 1, 0x44, 0x68);
		}

		static void AssertMidiMessage(MidiMessage* midiMsg,
			Midi::MessageTypes msgType, uint8_t channel, uint8_t note, uint8_t velocity)
		{
			Assert::IsTrue(midiMsg != nullptr);
			Assert::AreEqual((uint8_t)msgType, (uint8_t)midiMsg->MessageType);
			Assert::AreEqual(channel, midiMsg->Channel);
			Assert::AreEqual(note, midiMsg->Note);
			Assert::AreEqual(velocity, midiMsg->Velocity);
		}
	};
}
