#ifndef MAPDATACONTEXT_H_
#define MAPDATACONTEXT_H_

#include "MessageManager.h"

#include "ATL/MidiMessage.h"

using namespace ATL;

class MapDataContext
{
public:
    enum DataField
    {
        None,
        MessageType,
        MessageChannel,
        MessageIdentifier,
        MessageValue,
    };

	MidiMessage* InputMessage;
	MidiMessage* OutputMessage;

    inline int16_t Get(DataField source)
    {
        int16_t value = 0;

        switch (source)
        {
        case MessageType:
            value = MessageManager::GetField(InputMessage, MessageField::MessageType);
            break;
        case MessageChannel:
            value = MessageManager::GetField(InputMessage, MessageField::Channel);
            break;
        case MessageIdentifier:
            value = MessageManager::GetField(InputMessage, MessageField::Identifier);
            break;
        case MessageValue:
            value = MessageManager::GetField(InputMessage, MessageField::Value);
            break;
        default:
            break;
        }

        return value;
    }

    inline void Set(DataField target, int16_t value)
    {
        switch (target)
        {
        case MessageType:
            MessageManager::SetField(OutputMessage, MessageField::MessageType, value);
            break;
        case MessageChannel:
            MessageManager::SetField(OutputMessage, MessageField::Channel, value);
            break;
        case MessageIdentifier:
            MessageManager::SetField(OutputMessage, MessageField::Identifier, value);
            break;
        case MessageValue:
            MessageManager::SetField(OutputMessage, MessageField::Value, value);
            break;
        default:
            break;
        }
    }

};

#endif /* MAPDATACONTEXT_H_ */