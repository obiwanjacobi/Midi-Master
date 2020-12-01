#ifndef MAPDATACONTEXT_H_
#define MAPDATACONTEXT_H_

#include "MessageManager.h"

#include "ATL/MidiMessage.h"

using namespace ATL;

class MapDataContext
{
public:
    typedef enum
    {
        None,
        MessageType,
        MessageChannel,
        MessageIdentifier,
        MessageValue,
    } DataField;

	MidiMessage* InputMessage;
	MidiMessage* OutputMessage;

    inline int16_t Get(DataField source)
    {
		return MessageManager::GetField(InputMessage, MessageField((MessageField::type)source));
    }

    inline void Set(DataField target, int16_t value)
    {
		MessageManager::SetField(OutputMessage, MessageField((MessageField::type)target), value);
    }
};

#endif /* MAPDATACONTEXT_H_ */