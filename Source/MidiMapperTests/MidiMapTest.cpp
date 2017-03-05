#include "stdafx.h"
#include "..\MidiMapper\MidiPatch.h"

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
            msg.MessageType = Midi::MessageTypes::ControlChange;
            msg.Channel = 0;
            msg.Number = 42;
            msg.Value = 100;
                
            MessageTestResult result = tested.TestMap(&msg);

            Assert::IsTrue(result == MessageTestResult::Passed);
        }

        [TestMethod]
        void TestMap_ControlChange_ControlChange_Passed()
        {
            MidiMap tested;
            InitMidiMap(tested);
            tested.Entries[0].Category = Midi::MessageCategory::ControlChange;

            MidiMessage msg;
            msg.MessageType = Midi::MessageTypes::ControlChange;
            msg.Channel = 0;
            msg.Number = 42;
            msg.Value = 100;

            MessageTestResult result = tested.TestMap(&msg);

            Assert::IsTrue(result == MessageTestResult::Passed);
        }

        [TestMethod]
        void TestMap_Note_ControlChange_Blocked()
        {
            MidiMap tested;
            InitMidiMap(tested);
            tested.Entries[0].Category = Midi::MessageCategory::Note;

            MidiMessage msg;
            msg.MessageType = Midi::MessageTypes::ControlChange;
            msg.Channel = 0;
            msg.Number = 42;
            msg.Value = 100;

            MessageTestResult result = tested.TestMap(&msg);

            Assert::IsTrue(result == MessageTestResult::Blocked);
        }

    private:
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
