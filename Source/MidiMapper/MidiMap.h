#ifndef MIDIMAP_H_
#define MIDIMAP_H_

#include "DataTypes.h"
#include "MapDataContext.h"
#include "ValueSequence.h"

typedef ValueSequence<MaxMapEntries> MidiMapEntrySequence;

class MidiMap
{
public:
    //FixedArray<MidiMapEntry, MaxMapEntries> Entries;
    MidiMapEntrySequence Entries;

    /*
    MessageMatchResult Match(MidiMessage* midiMsg)
    {
        MessageMatchResult retVal = MessageMatchResult::None;

        for(uint8_t i = 0; i < Entries.getCount(); i++)
        {
            // break on first entry that is off
            if (Entries[i].Mode == MidiMapEntry::Mode::None) break;

            MessageMatchResult result = Entries[i].MatchMessage(midiMsg);

            if (retVal == MessageMatchResult::None)
            {
                retVal = result;
            }

            // break on first hit
            if (result == MessageMatchResult::Passed)
            {
                retVal = result;
                break;
            }
        }

        return retVal;
    }
    */

    inline void Clear()
    {
        memset(this, 0, sizeof(MidiMap));
    }
};

#endif //MIDIMAP_H_