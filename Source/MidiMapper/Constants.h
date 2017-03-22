#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#ifndef F_CPU
# warning "Declare F_CPU in the project configuration settings: F_CPU=20000000UL"
#define F_CPU 20000000UL
#endif

// string lengths (incl. terminating zero)
#define PatchNameMaxLength 15

// memory layout definitions
#define MaxPatches 32
#define MaxFilters 3
#define MaxMaps 2
#define MaxMapEntries 8
#define MaxTransforms 4


#define MidiTransmitBufferSize 32
#define MidiReceiveBufferSize 64

#define LcdColumns 24
#define LcdLines 2

#define MidiIn_Index     0
#define MidiOut1_Index   1
#define MidiOut2_Index   2
#define MidiOut3_Index   3
#define MidiOut4_Index   4


// Debug Component Ids
#define ProgramId 0x80
#define MidiMessageHandlerId 0x81


#endif /* CONSTANTS_H_ */