#ifndef __NAMETEXTCONTROL_H__
#define __NAMETEXTCONTROL_H__

#include "../PresetManager.h"
#include "../ATL/Iterator.h"
#include "../ATL/Singleton.h"
#include "../ATL/EditControl.h"

using namespace ATL;

template<const char StartChar, const char EndChar>
class AlphaNumCharProvider
{
public:
	typedef char ItemT;

	inline bool IsValidIndex(int16_t index) const
	{
		return index >= StartChar && index <= EndChar;
	}

	inline int16_t IndexOf(char item) const
	{
		return (int16_t)item;
	}

	inline char GetAt(uint16_t index) const
	{
		return (char)index;
	}
};

typedef Iterator<AlphaNumCharProvider<0x20, 0x7F> > AplhaNumCharIterator;
AplhaNumCharIterator TextIterator;

template<const uint8_t Size>
class NameTextControl : public EditControl<FixedString<Size>, AplhaNumCharIterator, NameTextControl<Size> >
{
	typedef EditControl<FixedString<Size>, AplhaNumCharIterator, NameTextControl<Size> > BaseT;

public:
	NameTextControl(const uint8_t pos)
		: BaseT(nullptr, &TextIterator, this, pos)
	{ }

	/** Called by the EditControl to increment the 'value' - char at edit position.
     */
    inline void IncrementValue()
    {
        BaseT::IncrementValue();
		PresetManager::getCurrent()->MarkDirty();
    }

    /** Called by the EditControl to decrement the 'value' - char at edit position.
     */
    inline void DecrementValue()
    {
		BaseT::DecrementValue();
		PresetManager::getCurrent()->MarkDirty();
    }
};

#endif /* __NAMETEXTCONTROL_H__ */