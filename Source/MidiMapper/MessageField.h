#ifndef MESSAGEFIELD_H_
#define MESSAGEFIELD_H_

#include "ATL/EnumScope.h"

BeginEnum(MessageField)
{
    // not set
    None,
    // Message Type Midi Message field.
    MessageType,
    // Channel Midi Message field.
    Channel,
    // Identifier Midi Message field.
    Identifier,
    // Value Midi Message field.
    Value,
}
EndEnum(MessageField)


#endif /* MESSAGEFIELD_H_ */