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
        return ReadAndClear(MidiIn_Index);
    }
     
    inline bool getMidiOutIsActive(uint8_t outIndex)
    {
        if (outIndex < MaxMaps)
        {
            return ReadAndClear(outIndex + 1);
        }
        
        return false;
    }

private:
	inline bool ReadAndClear(uint8_t index)
	{
		 bool value = Globals::MidiStatus.Get(index);
		 // clear on read
		 Globals::MidiStatus.Reset(index);

		 return value;
	}

};


#endif /* MIDISTATUS_H_ */