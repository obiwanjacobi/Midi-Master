#ifndef MIDISTATUS_H_
#define MIDISTATUS_H_

#include "DataTypes.h"
#include "Globals.h"
#include "ATL/Singleton.h"
#include "ATL/BitArray.h"

using namespace ATL;


class MidiStatus : public Singleton<MidiStatus>
{

    
public:
    inline void UpdateStatus()
    {
        if (!Globals::MidiInOutPort1.Receive.getIsEmpty())
        {
            Globals::MidiStatus.Set(MidiIn_Index);
        }
    }
    
    inline bool getMidiIsActive()
    {
        return Globals::MidiStatus != 0;
    }   
        
    inline bool getMidiInIsActive()
    {
        bool value = Globals::MidiStatus.Get(MidiIn_Index);
        // clear on read
        Globals::MidiStatus.Reset(MidiIn_Index);
        
        return value;
    }
     
    inline bool getMidiOutIsActive(uint8_t outIndex)
    {
        if (outIndex < 4)
        {
            bool value = Globals::MidiStatus.Get(outIndex + 1);
            // clear on read
            Globals::MidiStatus.Reset(outIndex + 1);
            return value;
        }
        
        return false;
    }
};


#endif /* MIDISTATUS_H_ */