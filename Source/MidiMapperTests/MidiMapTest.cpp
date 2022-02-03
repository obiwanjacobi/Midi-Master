#include "avr.h"
#include "..\MidiMapper\MidiPatch.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace MidiMapperTests2
{
    [TestClass]
    public ref class MidiMapTest
    {
        static int16_t Zero = 0;

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
            tested.Entries[Zero]->Category = Midi::MessageCategory::ControlChange;

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
            tested.Entries[Zero]->Category = Midi::MessageCategory::Note;

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
            midiMap.Entries[Zero]->Mode = MidiMapEntry::Mode::Normal;
            midiMap.Entries[Zero]->Category = Midi::MessageCategory::NotSet;
            midiMap.Entries[Zero]->Channel.SetAny();
            midiMap.Entries[Zero]->Identifier.SetAny();
            midiMap.Entries[Zero]->Value.SetAny();
            
            midiMap.Entries[Zero]->Transforms[Zero]->Mode = MidiTransform::Mode::None;
            midiMap.Entries[Zero]->Transforms[Zero]->SourceField = MessageField::None;
            midiMap.Entries[Zero]->Transforms[Zero]->TargetField = MessageField::None;
            midiMap.Entries[Zero]->Transforms[Zero]->Value.SetAny();
        }
    };
}
