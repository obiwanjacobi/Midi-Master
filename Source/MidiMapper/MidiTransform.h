#ifndef __MIDITRANSFORM_H__
#define __MIDITRANSFORM_H__

#include "MessageManager.h"
#include "MessageField.h"

class MidiTransform
{
public:
	BeginEnum(Mode)
	{
		// this transform is doing nothing.
		None,
		// the incoming value is returned unchanged
		Literal,
		// a constant value is returned
		Constant,
		// a value is added
		Add,
		// a value is subtracted
		Subtract,
		// the value is mapped in a linear fashion.
		LinearMap,
		// the value is mapped using a log scale
		LogMap,
		// the value is mapped using a reversed log scale
		RevLogMap,
	}
	EndEnum(Mode)

	

	MidiTransform()
		: Mode(Mode::None), SourceField(MessageField::None), TargetField(MessageField::None)
	{ }

	Mode Mode;
	MessageField SourceField;
	MessageField TargetField;
	// value used in transformation
	ValueContainer<uint8_t> Value;

	uint8_t Transform(MidiMessage* midiMsg)
	{
		uint8_t value = Extract(midiMsg);

		value = TransformValue(value);

		return value;
	}

	/*Midi::MessageTypes Transform(Midi::MessageTypes msgType)
	{
		uint8_t value = TransformValue(msgType);

		return (Midi::MessageTypes)value;
	}*/

private:
	inline uint8_t Extract(MidiMessage* midiMsg)
	{
		return MessageManager::GetField(midiMsg, SourceField);
	}

	uint8_t TransformValue(uint8_t value)
	{
		switch(Mode.value)
		{
		case Mode::Constant:
			value = Value.getValue();
			break;
		case Mode::Add:
			value += Value.getValue();
			break;
		case Mode::Subtract:
			value -= Value.getValue();
			break;
		case Mode::LinearMap:
			break;
		case Mode::LogMap:
			break;
		case Mode::RevLogMap:
			break;
		default:
			break;
		}

		return value;
	}

};

#endif //__MIDITRANSFORM_H__