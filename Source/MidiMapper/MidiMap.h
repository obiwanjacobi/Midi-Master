#ifndef __MIDIMAP_H__
#define __MIDIMAP_H__

#include "ATL/FixedArray.h"
#include "DataTypes.h"
#include "MidiMapEntry.h"

typedef FixedString<OutputNameMaxLength> OutputNameString;

class MidiMap
{
public:
    OutputNameString Name;
    FixedArray<MidiMapEntry, MaxMapEntries> Entries;

    MessageTestResult TestMap(MidiMessage* midiMsg)
    {
        MessageTestResult retVal = MessageTestResult::None;

        for(int16_t i = 0; i < Entries.getCount(); i++)
        {
            // break on first entry that is off
            if (Entries[i]->Mode == MidiMapEntry::Mode::None) break;

            MessageTestResult result = Entries[i]->TestMessage(midiMsg);

            if (retVal == MessageTestResult::None)
            {
                retVal = result;
            }

            // break on first hit
            if (result == MessageTestResult::Passed)
            {
                retVal = result;
                break;
            }
        }

        return retVal;
    }

    inline void Clear()
    {
        memset(this, 0, sizeof(MidiMap));
    }
};

#endif //__MIDIMAP_H__