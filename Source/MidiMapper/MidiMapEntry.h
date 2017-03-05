#ifndef __MIDIMAPENTRY_H__
#define __MIDIMAPENTRY_H__

#include "ATL/FixedArray.h"
#include "DataTypes.h"
#include "MessageDetection.h"
#include "MessageManager.h"
#include "MidiTransform.h"

class MidiMapEntry : public MessageDetection<MidiMapEntry>
{
public:
	BeginEnum(Mode)
	{
		// this map entry is not doing anything
		None,
		// this map entry is active
		Normal
	}
	EndEnum(Mode)

	MidiMapEntry()
		: Mode(Mode::None)
	{ }

	Mode Mode;
	FixedArray<MidiTransform, MaxTransforms> Transforms;

	void ExecuteMapEntry(MidiMessage* inputMsg, MidiMessage* outputMsg)
	{
		for (uint8_t i = 0; i < Transforms.getCapacity(); i++)
		{
			if (Transforms[i].Mode == MidiTransform::Mode::None) break;

			uint8_t value = Transforms[i].Transform(inputMsg);

			Insert(outputMsg, Transforms[i].TargetField, value);
		}
	}

	/*Midi::MessageTypes ExecuteMapEntry(Midi::MessageTypes msgType)
	{
		for (uint8_t i = 0; i < MaxTransforms; i++)
		{
			if (Transforms[i].Mode == MidiTransform::Mode::None) break;

			return Transforms[i].Transform(msgType);
		}

		return Midi::InvalidType;
	}*/

	inline void Clear()
	{
		memset(this, 0, sizeof(MidiMapEntry));
	}
	
private:
	inline void Insert(MidiMessage* midiMsg, MessageField targetField, uint8_t value)
	{
		MessageManager::SetField(midiMsg, targetField, value);
	}
};

#endif //__MIDIMAPENTRY_H__