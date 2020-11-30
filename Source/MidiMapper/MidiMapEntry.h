#ifndef MIDIMAPENTRY_H_
#define MIDIMAPENTRY_H_

#include "DataTypes.h"
#include "MessageDetection.h"

class MidiMapEntry : public MessageDetection<MidiMapEntry>
{
public:
	BeginEnum(State)
	{
		// this map entry is not doing anything
		None,
		// this map entry is active
		Enabled
	}
	EndEnum(State)

	MidiMapEntry()
		: State(State::None)
	{ }

	uint8_t /*Mode*/ State;
	//FixedArray<MidiTransform, MaxTransforms> Transforms;

    /*
	void ExecuteMapEntry(MidiMessage* inputMsg, MidiMessage* outputMsg)
	{
		for (uint8_t i = 0; i < Transforms.getCapacity(); i++)
		{
			if (Transforms[i].Mode == MidiTransform::Mode::None) break;

			uint8_t value = Transforms[i].Transform(inputMsg);

			MessageManager::SetField(outputMsg, Transforms[i].TargetField, value);
		}
	}
    */

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
};

#endif //MIDIMAPENTRY_H_