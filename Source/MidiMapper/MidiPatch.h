#ifndef __MIDIPATCH_H__
#define __MIDIPATCH_H__

#include "ATL/FixedArray.h"
#include "ATL/FixedString.h"
#include "DataTypes.h"
#include "MidiMap.h"

class MidiPatch
{
public:
	FixedString<MaxPatchNameLength> Name;
	FixedArray<MidiMap, MaxMaps> Maps;

	inline void Clear()
	{
		memset(this, 0, sizeof(MidiPatch));
	}
};

#endif //__MIDIPATCH_H__