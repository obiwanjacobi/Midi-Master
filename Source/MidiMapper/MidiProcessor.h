#ifndef MIDIPROCESSOR_H_
#define MIDIPROCESSOR_H_

#include "MidiMap.h"
#include "MidiMapEntry.h"
#include "MidiTransform.h"

/*
    Globals
    + MidiPatch (memory)
    + DataSlots 

    MidiPatch
    + MidiMaps
    + MidiMapEntries
    + MidiTransforms
    + MidiMessages

    MidiMap
    + SequenceEntries
     MidiMapEntry
    + State (can be inferred from SeqTransf?)
    + SequenceTransforms

    MidiTransform
    + (Sequence)Messages

    MidiDataContext
    + Input / Output Messages
    + DataSlots (refs)

    MidiProcessor
    + Execute(MidiPatch, MidiDataContext)
    + Execute(MidiMap, MidiDataContext)
    + Execute(MidiMapEntry, MidiDataContext)
    + Execute(MidiTransform, MidiDataContext)
    
    MidiDataContext(DataSlots)
    MIDI-In => MidiMessage => 
        MidiDataContext.Add(MidiMessage)
        MidiProcessor.Execute(MidiPatch, MidiDataContext)
    Loop
*/


class MidiProcessor
{
public:
    void Execute(MidiPatch patch, MapDataContext context)
    {

    }

    void Execute(MidiMap map, MapDataContext context)
    {

    }

    void Execute(MidiMapEntry entry, MapDataContext context)
    {

    }

    void Execute(MidiTransform transform, MapDataContext context)
    {

    }
};

#endif /* MIDIPROCESSOR_H_ */