#ifndef __MESSAGEDETECTION_H__
#define __MESSAGEDETECTION_H__

#include <stdint.h>
#include "ATL/Midi.h"
#include "ATL/MidiMessage.h"
#include "ATL/ValueContainer.h"
#include "DataTypes.h"
#include "MessageMatchResult.h"

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

	MessageMatchResult MatchMessage(MidiMessage* midiMsg)
	{
		if (midiMsg == nullptr) return MessageMatchResult::None;

		if (Category == Midi::MessageCategory::NotSet)
		{
			return DispatchMessage(midiMsg, Midi::ToMessageCategory(midiMsg->MessageType));
		}

		return DispatchMessage(midiMsg, Category);
	}

	/*MessageTestResult MatchRealtime(Midi::MessageTypes msgType)
	{
		if (Midi::IsRealtimeMessage(msgType) &&
			Category == Midi::MessageCategory::Realtime)
		{
			return MessageTestResult::Passed;
		}

		return MessageTestResult::Blocked;
	}*/

protected:
	MessageMatchResult MatchNote(uint8_t channel, uint8_t noteNr, uint8_t velocity)
	{
		return DoFieldsMatch (channel, noteNr, velocity) 
                ? MessageMatchResult::Passed : MessageMatchResult::Blocked;
	}

	MessageMatchResult MatchAfterTouch(uint8_t channel, uint8_t noteNr, uint8_t pressure)
	{
		return DoFieldsMatch(channel, noteNr, pressure)
                ? MessageMatchResult::Passed : MessageMatchResult::Blocked;
	}

	MessageMatchResult MatchControlChange(uint8_t channel, uint8_t number, uint8_t value)
	{
		return DoFieldsMatch(channel, number, value)
                ? MessageMatchResult::Passed : MessageMatchResult::Blocked;
	}

	MessageMatchResult MatchProgramChange(uint8_t channel, uint8_t number)
	{
		return DoFieldsMatch(channel, number, 0)
                ? MessageMatchResult::Passed : MessageMatchResult::Blocked;
	}

	MessageMatchResult MatchPitchBend(uint8_t channel, int16_t bend)
	{
		return DoFieldsMatch(channel, 0, bend)
                ? MessageMatchResult::Passed : MessageMatchResult::Blocked;
	}

	MessageMatchResult MatchSysEx(MidiMessage* midiMsg)
	{
		return MessageMatchResult::Blocked;
	}

	MessageMatchResult MatchSystemCommon(MidiMessage* midiMsg)
	{
		return MessageMatchResult::Blocked;
	}
	
private:
	bool DoFieldsMatch(uint8_t channel, uint8_t identifier, int16_t value)
	{
		return Channel.IsInRange(channel) &&
			   Identifier.IsInRange(identifier) &&
			   Value.IsInRange(value);
	}

	MessageMatchResult DispatchMessage(MidiMessage* midiMsg, Midi::MessageCategory category)
	{
		MessageMatchResult result = MessageMatchResult::Blocked;

		switch(category.value)
		{
		case Midi::MessageCategory::Note:
			if (midiMsg->MessageType == Midi::NoteOn || midiMsg->MessageType == Midi::NoteOff) 
				result = static_cast<SuperT*>(this)->MatchNote(midiMsg->Channel, midiMsg->Note, midiMsg->Velocity);
			break;
		case Midi::MessageCategory::AfterTouch:
			if (midiMsg->MessageType == Midi::AfterTouchChannel || midiMsg->MessageType == Midi::AfterTouchPoly) 
				result = static_cast<SuperT*>(this)->MatchAfterTouch(midiMsg->Channel, midiMsg->Note, midiMsg->Pressure);
			break;
		case Midi::MessageCategory::ControlChange:
			if (midiMsg->MessageType == Midi::ControlChange)
				result = static_cast<SuperT*>(this)->MatchControlChange(midiMsg->Channel, midiMsg->Number, midiMsg->Value);
			break;
		case Midi::MessageCategory::ProgramChange:
			if (midiMsg->MessageType == Midi::ProgramChange)
				result = static_cast<SuperT*>(this)->MatchProgramChange(midiMsg->Channel, midiMsg->Number);
			break;
		case Midi::MessageCategory::PitchBend:
			if(midiMsg->MessageType == Midi::PitchBend)
				result = static_cast<SuperT*>(this)->MatchPitchBend(midiMsg->Channel, midiMsg->Bend);
			break;
		case Midi::MessageCategory::SystemExclusive:
			result = static_cast<SuperT*>(this)->MatchSysEx(midiMsg);
			break;
		case Midi::MessageCategory::SystemCommon:
			result = static_cast<SuperT*>(this)->MatchSystemCommon(midiMsg);
			break;
		/*case Midi::MessageCategory::Realtime:
			result = static_cast<SuperT*>(this)->MatchRealtime(midiMsg->MessageType);
			break;*/
		default:
			// Not Implemented
			result = MessageMatchResult::None;
			break;
		}

		return result;
	}
};

#endif //__MESSAGEDETECTION_H__