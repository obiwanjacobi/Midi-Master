#ifndef MIDIPATCH_H_
#define MIDIPATCH_H_

#include "ATL/FixedArray.h"
#include "ATL/FixedString.h"
#include "DataTypes.h"
#include "MidiMapEntry.h"
#include "MidiTransform.h"
//#include "MidiStorage.h"

typedef FixedString<PatchNameMaxLength> PatchNameString;
typedef FixedArray<MidiMap, MaxMaps> MidiMapArray;
typedef FixedArray<MidiMapEntry, MaxMapEntries> MidiMapEntryArray;
typedef FixedArray<MidiTransform, MaxTransforms> MidiTransformArray;

class MidiPatch
{
public:
	PatchNameString Name;
    MidiMapArray Maps;
    MidiMapEntryArray Entries;
    MidiTransformArray Transforms;

	inline void Clear()
	{
		memset(this, 0, sizeof(MidiPatch));
	}
};

#endif //MIDIPATCH_H_