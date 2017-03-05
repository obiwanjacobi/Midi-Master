#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "DataTypes.h"
#include "MidiPatch.h"
#include "ATL/BitArray.h"

using namespace ATL;

class Globals
{
public:
#define MidiIn_Index     0
#define MidiOut1_Index   1
#define MidiOut2_Index   2
#define MidiOut3_Index   3
#define MidiOut4_Index   4

    static MidiPatch MemPatch;
    static MidiInOutPort1T<Globals> MidiInOutPort1;
    static MidiOutPort2T MidiOutPort2;
    static BitArray<uint8_t> MidiStatus;
    
    static void OpenMidiPorts();
    
    inline static void MidiOutSend(uint8_t outIndex, MidiMessage* midiMsg)
    {
        MidiStatus.Set(outIndex + 1);
        
        switch(outIndex)
        {
        case 0:
            MidiInOutPort1.Transmit.Write(midiMsg);
            break;
        case 1:
            MidiOutPort2.Transmit.Write(midiMsg);
            break;
        case 2:
            //MidiOut3.Write(midiMsg);
            break;
        case 3:
            //MidiOut4.Write(midiMsg);
            break;
        }
    }

    inline static void MidiOutSend(uint8_t outIndex, Midi::MessageTypes msgType)
    {
        MidiStatus.Set(outIndex + 1);
        
        switch(outIndex)
        {
        case 0:
            MidiInOutPort1.Transmit.Write(msgType);
            break;
        case 1:
            MidiOutPort2.Transmit.Write(msgType);
            break;
        case 2:
            //MidiOut3.Write(msgType);
            break;
        case 3:
            //MidiOut4.Write(msgType);
            break;
        }
    }
    
    
    static void InitTest()
    {
        //
        // TEST
        //
        
        MemPatch.Name = "NamePreset";
        MemPatch.Maps[0].Entries[0].Mode = MidiMapEntry::Mode::Normal;
        MemPatch.Maps[0].Entries[0].Category = Midi::MessageCategory::ControlChange;
        MemPatch.Maps[0].Entries[0].Channel.SetAny();
        MemPatch.Maps[0].Entries[0].Identifier.SetAny();
        MemPatch.Maps[0].Entries[0].Value.SetRange(0, 63);

        MemPatch.Maps[1].Entries[0].Mode = MidiMapEntry::Mode::Normal;
        MemPatch.Maps[1].Entries[0].Category = Midi::MessageCategory::ControlChange;
        MemPatch.Maps[1].Entries[0].Channel.SetAny();
        MemPatch.Maps[1].Entries[0].Identifier.SetAny();
        MemPatch.Maps[1].Entries[0].Value.SetRange(64, 127);
        
    }
    
private:
	Globals();

};

#endif //__GLOBALS_H__
