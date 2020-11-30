#include "stdafx.h"
#include "MidiPatch.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace MidiMapperTests2
{
    [TestClass]
    public ref class MidiMapTest
    {
    public: 
        [TestMethod]
        void TestMap_NotSet_ControlChange_Passed()
        {
            MidiMap tested;
            InitMidiMap(tested);

            MidiMessage msg;
            CreateMessage(&msg);
                
            MessageMatchResult result = tested.Match(&msg);

            Assert::IsTrue(result == MessageMatchResult::Passed);
        }

        [TestMethod]
        void TestMap_ControlChange_ControlChange_Passed()
        {
            MidiMap tested;
            InitMidiMap(tested);
            tested.Entries[0].Category = Midi::MessageCategory::ControlChange;

            MidiMessage msg;
            CreateMessage(&msg);

            MessageMatchResult result = tested.Match(&msg);

            Assert::IsTrue(result == MessageMatchResult::Passed);
        }

        [TestMethod]
        void TestMap_Note_ControlChange_Blocked()
        {
            MidiMap tested;
            InitMidiMap(tested);
            tested.Entries[0].Category = Midi::MessageCategory::Note;

            MidiMessage msg;
            CreateMessage(&msg);

            MessageMatchResult result = tested.Match(&msg);

            Assert::IsTrue(result == MessageMatchResult::Blocked);
        }

    private:
        void CreateMessage(MidiMessage* message)
        {
            message->MessageType = Midi::MessageTypes::ControlChange;
            message->Channel = 0;
            message->Number = 42;
            message->Value = 100;
        }

        void InitMidiMap(MidiMap& midiMap)
        {
            midiMap.Entries[0].Mode = MidiMapEntry::Mode::Normal;
            midiMap.Entries[0].Category = Midi::MessageCategory::NotSet;
            midiMap.Entries[0].Channel.SetAny();
            midiMap.Entries[0].Identifier.SetAny();
            midiMap.Entries[0].Value.SetAny();
            
            midiMap.Entries[0].Transforms[0].Mode = MidiTransform::Mode::None;
            midiMap.Entries[0].Transforms[0].SourceField = MessageField::None;
            midiMap.Entries[0].Transforms[0].TargetField = MessageField::None;
            midiMap.Entries[0].Transforms[0].Value.SetAny();
        }
    };
}
