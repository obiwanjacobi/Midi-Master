#ifndef __MESSAGEDETECTION_H__
#define __MESSAGEDETECTION_H__

#include <stdint.h>
#include "ATL/Midi.h"
#include "ATL/MidiMessage.h"
#include "ATL/ValueContainer.h"
#include "DataTypes.h"
#include "MessageTestResult.h"

using namespace ATL;

/*
    SuperT is the class that will receive the specific test calls for each type of test 
    by casting the this pointer: TestResult static_cast<SuperT*>(this)->TestXxxx();.
*/
template<class SuperT>
class MessageDetection
{
public:
    MessageDetection()
        : Category(Midi::MessageCategory::NotSet)
    { }
        
    Midi::MessageCategory Category;
    ValueContainer<uint8_t> Channel;
    ValueContainer<uint8_t> Identifier;
    ValueContainer<int16_t> Value;

    MessageTestResult TestMessage(MidiMessage* midiMsg)
    {
        if (midiMsg == nullptr) return MessageTestResult::None;

        if (Category == Midi::MessageCategory::NotSet)
        {
            return DispatchTestMessage(midiMsg, Midi::ToMessageCategory(midiMsg->MessageType));
        }

        return DispatchTestMessage(midiMsg, Category);
    }

    /*MessageTestResult TestRealtime(Midi::MessageTypes msgType)
    {
        if (Midi::IsRealtimeMessage(msgType) &&
            Category == Midi::MessageCategory::Realtime)
        {
            return MessageTestResult::Passed;
        }

        return MessageTestResult::Blocked;
    }*/

protected:
    MessageTestResult TestNote(uint8_t channel, uint8_t noteNr, uint8_t velocity)
    {
        return (Channel.IsInRange(channel) &&
                Identifier.IsInRange(noteNr) &&
                Value.IsInRange(velocity)) ? MessageTestResult::Passed : MessageTestResult::Blocked;
    }

    MessageTestResult TestAfterTouch(uint8_t channel, uint8_t noteNr, uint8_t pressure)
    {
        return (Channel.IsInRange(channel) &&
                Identifier.IsInRange(noteNr) &&
                Value.IsInRange(pressure)) ? MessageTestResult::Passed : MessageTestResult::Blocked;
    }

    MessageTestResult TestControlChange(uint8_t channel, uint8_t number, uint8_t value)
    {
        return (Channel.IsInRange(channel) &&
                Identifier.IsInRange(number) &&
                Value.IsInRange(value)) ? MessageTestResult::Passed : MessageTestResult::Blocked;
    }

    MessageTestResult TestProgramChange(uint8_t channel, uint8_t number)
    {
        return (Channel.IsInRange(channel) &&
                Identifier.IsInRange(number)) ? MessageTestResult::Passed : MessageTestResult::Blocked;
    }

    MessageTestResult TestPitchBend(uint8_t channel, int16_t bend)
    {
        return (Channel.IsInRange(channel) &&
                Value.IsInRange(bend)) ? MessageTestResult::Passed : MessageTestResult::Blocked;
    }

    MessageTestResult TestSysEx(MidiMessage* midiMsg)
    {
        return MessageTestResult::Blocked;
    }

    MessageTestResult TestSystemCommon(MidiMessage* midiMsg)
    {
        return MessageTestResult::Blocked;
    }
    
private:
    MessageTestResult DispatchTestMessage(MidiMessage* midiMsg, Midi::MessageCategory category)
    {
        MessageTestResult result = MessageTestResult::Blocked;

        switch(category.value)
        {
        case Midi::MessageCategory::Note:
            if (midiMsg->MessageType == Midi::NoteOn || midiMsg->MessageType == Midi::NoteOff) 
                result = static_cast<SuperT*>(this)->TestNote(midiMsg->Channel, midiMsg->Note, midiMsg->Velocity);
            break;
        case Midi::MessageCategory::AfterTouch:
            if (midiMsg->MessageType == Midi::AfterTouchChannel || midiMsg->MessageType == Midi::AfterTouchPoly) 
                result = static_cast<SuperT*>(this)->TestAfterTouch(midiMsg->Channel, midiMsg->Note, midiMsg->Pressure);
            break;
        case Midi::MessageCategory::ControlChange:
            if (midiMsg->MessageType == Midi::ControlChange)
                result = static_cast<SuperT*>(this)->TestControlChange(midiMsg->Channel, midiMsg->Number, midiMsg->Value);
            break;
        case Midi::MessageCategory::ProgramChange:
            if (midiMsg->MessageType == Midi::ProgramChange)
                result = static_cast<SuperT*>(this)->TestProgramChange(midiMsg->Channel, midiMsg->Number);
            break;
        case Midi::MessageCategory::PitchBend:
            if(midiMsg->MessageType == Midi::PitchBend)
                result = static_cast<SuperT*>(this)->TestPitchBend(midiMsg->Channel, midiMsg->Bend);
            break;
        case Midi::MessageCategory::SystemExclusive:
            result = static_cast<SuperT*>(this)->TestSysEx(midiMsg);
            break;
        case Midi::MessageCategory::SystemCommon:
            result = static_cast<SuperT*>(this)->TestSystemCommon(midiMsg);
            break;
        /*case Midi::MessageCategory::Realtime:
            result = static_cast<SuperT*>(this)->TestRealtime(midiMsg->MessageType);
            break;*/
        default:
            // Not Implemented
            result = MessageTestResult::None;
            break;
        }

        return result;
    }
};

#endif //__MESSAGEDETECTION_H__