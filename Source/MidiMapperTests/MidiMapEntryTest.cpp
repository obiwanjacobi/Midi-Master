#include "stdafx.h"
#include "MidiPatch.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


namespace MidiMapperTests
{
    [TestClass]
    public ref class MidiMapEntryTest
    {
    public:
        [TestMethod]
        void MatchMessage_NotSet_ControlChange_Passed()
        {
            MidiMapEntry tested;
            tested.Mode = MidiMapEntry::Mode::Normal;
            tested.Category = Midi::MessageCategory::NotSet;
            tested.Channel.SetAny();
            tested.Identifier.SetAny();
            tested.Value.SetAny();
            tested.Transforms[0].Mode = MidiTransform::Mode::None;

            MidiMessage msg;
            CreateMessage(&msg);
            
            MessageMatchResult result = tested.MatchMessage(&msg);

            Assert::IsTrue(result == MessageMatchResult::Passed);
        };

        [TestMethod]
        void MatchMessage_ControlChange_ControlChange_Passed()
        {
            MidiMapEntry tested;
            tested.Mode = MidiMapEntry::Mode::Normal;
            tested.Category = Midi::MessageCategory::ControlChange;
            tested.Channel.SetAny();
            tested.Identifier.SetAny();
            tested.Value.SetAny();
            tested.Transforms[0].Mode = MidiTransform::Mode::None;

            MidiMessage msg;
            CreateMessage(&msg);

            MessageMatchResult result = tested.MatchMessage(&msg);

            Assert::IsTrue(result == MessageMatchResult::Passed);
        };

    private:
        void CreateMessage(MidiMessage* message)
        {
            message->MessageType = Midi::MessageTypes::ControlChange;
            message->Channel = 0;
            message->Number = 66;
            message->Value = 100;
        }
    };
}
