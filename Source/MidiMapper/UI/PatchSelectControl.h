#ifndef __PATCHSELECTCONTROL_H__
#define __PATCHSELECTCONTROL_H__

#include "../ATL/UpDownControl.h"

template<class ValueT>
class PatchSelectControl : public UpDownControl<ValueT>
{
	typedef UpDownControl<ValueT> BaseT;

public:
	PatchSelectControl(ValueT* valueThis, const uint8_t pos)
		: BaseT(valueThis, pos)
	{ }

	inline void Display(DisplayWriter* output, ControlDisplayMode mode) override
	{
		if (mode == ControlDisplayMode::Cursor && BaseT::getIsActive())
		{
			output->GoTo(DisplayWriter::CurrentPos, BaseT::getPosition() + 1);
		}

		BaseT::Display(output, mode);
	}

};

#endif /* __PATCHSELECTCONTROL_H__ */