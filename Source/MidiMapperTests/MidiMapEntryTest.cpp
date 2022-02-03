#include "avr.h"
#include "..\MidiMapper\MidiPatch.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


namespace MidiMapperTests
{
    [TestClass]
    public ref class MidiMapEntryTest
    {
    public:
        [TestMethod]
        void TestMessage_NotSet_ControlChange_Passed()
        {
            MidiMapEntry tested;
            tested.Mode = MidiMapEntry::Mode::Normal;
            tested.Category = Midi::MessageCategory::NotSet;
            tested.Channel.SetAny();
            tested.Identifier.SetAny();
            tested.Value.SetAny();
            tested.Transforms[(int16_t)0]->Mode = MidiTransform::Mode::None;

            MidiMessage msg;
            msg.MessageType = Midi::ControlChange;
            msg.Channel = 0;
            msg.Number = 66;
            msg.Value = 100;
            
            MessageTestResult result = tested.TestMessage(&msg);

            Assert::IsTrue(result == MessageTestResult::Passed);
        };

        [TestMethod]
        void TestMessage_ControlChange_ControlChange_Passed()
        {
            MidiMapEntry tested;
            tested.Mode = MidiMapEntry::Mode::Normal;
            tested.Category = Midi::MessageCategory::ControlChange;
            tested.Channel.SetAny();
            tested.Identifier.SetAny();
            tested.Value.SetAny();
            tested.Transforms[(int16_t)0]->Mode = MidiTransform::Mode::None;

            MidiMessage msg;
            msg.MessageType = Midi::ControlChange;
            msg.Channel = 0;
            msg.Number = 66;
            msg.Value = 100;

            MessageTestResult result = tested.TestMessage(&msg);

            Assert::IsTrue(result == MessageTestResult::Passed);
        };
    };
}
