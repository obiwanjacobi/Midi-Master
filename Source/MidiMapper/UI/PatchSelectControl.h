#ifndef __PATCHSELECTCONTROL_H__
#define __PATCHSELECTCONTROL_H__

#include "../ATL/Debug.h"
#include "../ATL/UpDownControl.h"


class PatchSelectControl : public UpDownControl<PatchSelectControl>
{
	typedef UpDownControl<PatchSelectControl> BaseT;

public:
	PatchSelectControl(const uint8_t pos)
		: UpDownControl(this, pos)
	{ }

	inline void Display(DisplayWriter* output, ControlDisplayMode mode) override
	{
		if (mode == ControlDisplayMode::Cursor && getIsActive())
		{
			output->GoTo(DisplayWriter::DontCare, getPosition() + 1);
		}

		BaseT::Display(output, mode);
	}

	inline const char* ToString()
	{
		uint8_t val = PresetManager::getCurrent()->getCurrentPresetIndex() + 1;

		_str.Clear();
		_str.Write(val, 2);
		return (const char*)_str;
	}

	inline void IncrementValue()
	{
		PresetManager* presetMgr = PresetManager::getCurrent();
		presetMgr->LoadPreset(presetMgr->getCurrentPresetIndex() + 1);
	}

	inline void DecrementValue()
	{
		PresetManager* presetMgr = PresetManager::getCurrent();
		presetMgr->LoadPreset(presetMgr->getCurrentPresetIndex() - 1);
	}

private:
	StringWriter<2> _str;
};

#endif /* __PATCHSELECTCONTROL_H__ */