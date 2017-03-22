#ifndef __MESSAGEMANAGER_H__
#define __MESSAGEMANAGER_H__

#include "ATL/MidiMessage.h"
#include "MessageField.h"

class MessageManager
{
public:
	MessageManager(MidiMessage* midiMsg)
		: _midiMsg(midiMsg)
	{ }
	
	inline bool SetField(MessageField field, uint8_t value)
	{
		return SetField(_midiMsg, field, value);
	}
	
	inline static bool SetField(MidiMessage* midiMsg, MessageField field, uint8_t value)
	{
		switch(field.value)
		{
		case MessageField::MessageType:
			midiMsg->MessageType = (Midi::MessageTypes)value;
			break;
		case MessageField::Channel:
			midiMsg->Channel = (uint8_t)value;
			break;
		case MessageField::Identifier:
			midiMsg->SetDataByte1((uint8_t)value);
			break;
		case MessageField::Value:
			midiMsg->SetDataByte2((uint8_t)value);
			break;
		default:
			return false;
		}
		
		return true;
	}
	
	inline uint8_t GetField(MessageField field) const
	{
		return GetField(_midiMsg, field);
	}
	
	inline static uint8_t GetField(MidiMessage* midiMsg, MessageField field)
	{
		switch(field.value)
		{
		case MessageField::MessageType:
			return midiMsg->MessageType;
		case MessageField::Channel:
			return midiMsg->Channel;
		case MessageField::Identifier:
			return midiMsg->GetDataByte1();
		case MessageField::Value:
			return midiMsg->GetDataByte2();
		default:
			break;
		}

		return 0;
	}

private:
	MidiMessage* _midiMsg;
};


#endif /* __MESSAGEMANAGER_H__ */