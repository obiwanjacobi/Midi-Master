#ifndef MAPENTRYSELECTCONTROL_H_
#define MAPENTRYSELECTCONTROL_H_

#include "../ATL/UpDownControl.h"

template<class ValueT>
class MapEntrySelectControl : public UpDownControl<ValueT>
{
    typedef UpDownControl<ValueT> BaseT;

public:
    MapEntrySelectControl(ValueT* valueThis, const uint8_t pos)
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

#endif /* MAPENTRYSELECTCONTROL_H_ */