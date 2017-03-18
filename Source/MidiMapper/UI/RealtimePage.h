#ifndef REALTIMEPAGE_H_
#define REALTIMEPAGE_H_

#include "../ATL/Debug.h"
#include "../ATL/IdentifiableObject.h"
#include "../ATL/Task.h"
#include "../ATL/Line.h"
#include "../ATL/Page.h"
#include "../ATL/LabelControl.h"
#include "../ATL/UpDownControl.h"
#include "../PresetManager.h"
#include "MidiOutNoteNavigationControl.h"
#include "MidiInNoteControl.h"
#include "PatchSelectControl.h"
#include "NameTextControl.h"

using namespace ATL;

typedef NameTextControl<PatchNameMaxLength> PatchNameTextControl;

template<typename PageManagerT>
class RealtimeLine1 : public Line<7>
{
    typedef Line<7> BaseT;

public:
    RealtimeLine1()
        : PatchNumber(this, 0), PatchNameText(3), InNoteLabel(21)
    {
        Add(&PatchNumber);
		Add(&PatchNameText);
        Add(&InNoteLabel);
    }
    
    PatchSelectControl<RealtimeLine1<PageManagerT> > PatchNumber;
	PatchNameTextControl PatchNameText;
    MidiInNoteControl InNoteLabel;

	// PatchSelectControl callbacks
	inline const char* getText()
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

		PatchNameText.RefreshString();
	}

	inline void DecrementValue()
	{
		PresetManager* presetMgr = PresetManager::getCurrent();
		presetMgr->LoadPreset(presetMgr->getCurrentPresetIndex() - 1);

		PatchNameText.RefreshString();
	}

private:
	StringWriter<2> _str;
};

template<typename PageManagerT>
class RealtimeLine2 : public Line<5>
{
    typedef Line<5> BaseT;
    
public:
    RealtimeLine2()
        : Out1NoteLabel(0), Out2NoteLabel(6), Out3NoteLabel(12), Out4NoteLabel(18)
    {
		Add(&Out1NoteLabel);
		Add(&Out2NoteLabel);
        Add(&Out3NoteLabel);
        Add(&Out4NoteLabel);
    }

	MidiOutNoteNavigationControl<PageManagerT, 0> Out1NoteLabel;
	MidiOutNoteNavigationControl<PageManagerT, 1> Out2NoteLabel;
    MidiOutNoteNavigationControl<PageManagerT, 2> Out3NoteLabel;
    MidiOutNoteNavigationControl<PageManagerT, 3> Out4NoteLabel;
};

template<typename PageManagerT>
class RealtimePage : public IdentifiableObject<Page<LcdLines> >
{
    typedef IdentifiableObject<Page<LcdLines> > BaseT;
    
public:
    RealtimePage()
    {
        Add(&Line1);
        Add(&Line2);
    }
    
    RealtimeLine1<PageManagerT> Line1;
    RealtimeLine2<PageManagerT> Line2;
    
    void PartialDisplay(DisplayWriter* output)
    {
		// TODO:
    }
    
    Task_BeginWithParams(DisplayActivity, DisplayWriter* output)
    {
		PartialDisplay(output);

        if (MidiStatus::getCurrent()->getMidiIsActive())
        {
            Task_YieldUntil(TaskScheduler::Wait(getId(), 30));
        }
    }
    Task_End
    
private:
    uint8_t _task;
};



#endif /* REALTIMEPAGE_H_ */