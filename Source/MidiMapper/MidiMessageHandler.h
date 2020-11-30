#ifndef __MIDIMESSAGEHANDLER_H__
#define __MIDIMESSAGEHANDLER_H__

#include "Constants.h"
#include "ATL/RingBufferFast.h"
#include "ATL/AVR/UsartRegisters.h"
#include "ATL/AVR/UsartReceive.h"
#include "ATL/AVR/UsartInputStream.h"
#include "MidiMap.h"
#include "MidiPatch.h"

using namespace ATL;
using namespace ATL::MCU;

/*
	This class is designed to be a base class to the [ATL]MidiReader class.
*/
template<typename StateT>
class MidiMessageHandler : public UsartInputStream<UsartReceive<UsartIds::UsartId0>, RingBufferFast<uint8_t, MidiReceiveBufferSize> >
{
    typedef UsartInputStream<UsartReceive<UsartIds::UsartId0>, RingBufferFast<uint8_t, MidiReceiveBufferSize> > BaseT;
public:
    inline int16_t Read()
    {
        if (!BaseT::getIsEmpty())
        {
            StateT::MidiStatus.Set(MidiIn_Index);
        }
        
        return BaseT::Read();
    }
    
protected:
    
	// MidiReader methods
	void OnMessage(MidiMessage* midiMsg)
	{
		if (midiMsg == nullptr) return;
		
        /*
		for (uint8_t i = 0; i < MaxMaps; i++)
		{
			// TODO: remove this call and integrate it with ExecuteMap
			// Now we're iterating the MapEntries twice.
			MessageMatchResult result = StateT::MemPatch[0].Maps[i].Match(midiMsg);

			switch (result.value)
			{
			case MessageMatchResult::Through:
				StateT::MidiOutSend(i, midiMsg);
				break;
			case MessageMatchResult::None:
			case MessageMatchResult::Passed:
				//ExecuteMap(i, midiMsg);
				break;
			default:
				break;
			}
		}
        */
	}
    


	void OnRealtime(Midi::MessageTypes msgType)
	{
		/*for (uint8_t i = 0; i < MaxMaps; i++)
		{
			TestResult result = StateT::MemPatch.Maps[i].Match(msgType);

			switch (result)
			{
			case resultThrough:
				StateT::MidiOutSend(i, msgType);
				break;
			case resultNone:
			case resultPassed:
				ExecuteMap(i, msgType);
				break;
			default:
				break;
			}
		}*/
	}

	void OnSysEx(MidiMessageHandler* unused)
	{ }

private:
    /*
	void ExecuteMap(uint8_t mapIndex, MidiMessage* inputMsg)
	{
		MidiMap map = StateT::MemPatch[0].Maps[mapIndex];
		MidiMessage outputMsg;

		for (uint8_t i = 0; i < MaxMapEntries; i++)
		{
			if (map.Entries[i].Mode == MidiMapEntry::Mode::None) break;

			inputMsg->CopyTo(&outputMsg);
			map.Entries[i].ExecuteMapEntry(inputMsg, &outputMsg);
			StateT::MidiOutSend(mapIndex, &outputMsg);
		}
	}
    */

	/*void ExecuteMap(uint8_t mapIndex, Midi::MessageTypes msgType)
	{
		MidiMap map = StateT::MemPatch.Maps[mapIndex];
		for (uint8_t i = 0; i < MaxMapEntries; i++)
		{
			if (map.Entries[i].Mode == MidiMapEntry::Mode::None) break;

			Midi::MessageTypes mappedType = map.Entries[i].ExecuteMapEntry(msgType);

			if (mappedType != Midi::InvalidType)
			{
				StateT::MidiOutSend(mapIndex, mappedType);
			}
		}
	}*/
};


#endif //__MIDIMESSAGEHANDLER_H__

