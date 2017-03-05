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

using namespace ATL;

static const char* OutText = "Out";

template<typename PageManagerT>
class RealtimeLine1 : public Line<7>
{
    typedef Line<7> BaseT;
    typedef MidiOutNoteNavigationControl<PageManagerT> MidiOutNoteControl;
    
public:
    RealtimeLine1()
        : PresetLabel("Preset"), 
        PresetNumber(this, 7), InNoteLabel(9),
        Out1Label(OutText, 12), Out1NoteLabel(0, 16),
        Out2Label(OutText, 19), Out2NoteLabel(1, 23)
    {
        Add(&PresetLabel);
        Add(&PresetNumber);
        Add(&InNoteLabel);
        Add(&Out1Label);
        Add(&Out1NoteLabel);
        Add(&Out2Label);
        Add(&Out2NoteLabel);
    }
    
    LabelControl PresetLabel;
    UpDownControl<RealtimeLine1> PresetNumber;
    MidiInNoteControl InNoteLabel;
    LabelControl Out1Label;
    MidiOutNoteControl Out1NoteLabel;
    LabelControl Out2Label;
    MidiOutNoteControl Out2NoteLabel;
    
    inline const char* ToString()
    {
        return "01";
    }
    
    inline void IncrementValue()
    {
        
    }
    
    inline void DecrementValue()
    {
        
    }
};

template<typename PageManagerT>
class RealtimeLine2 : public Line<5>
{
    typedef Line<5> BaseT;
    typedef MidiOutNoteNavigationControl<PageManagerT> MidiOutNoteControl;
    
public:
    RealtimeLine2()
        : BaseT(1), 
        Out3Label(OutText, 12), Out3NoteLabel(2, 16),
        Out4Label(OutText, 19), Out4NoteLabel(3, 23)
    {
        Add(&PresetNameLabel);
        Add(&Out3Label);
        Add(&Out3NoteLabel);
        Add(&Out4Label);
        Add(&Out4NoteLabel);
    }

    LabelControl PresetNameLabel;
    LabelControl Out3Label;
    MidiOutNoteControl Out3NoteLabel;
    LabelControl Out4Label;
    MidiOutNoteControl Out4NoteLabel;
    
    inline virtual void Display(DisplayWriter* output, ControlDisplayMode mode)
    {
        Refresh();
        BaseT::Display(output, mode);
    }
    
private:
    inline void Refresh()
    {
        PresetNameLabel.setText(PresetManager::getCurrent()->getCurrentPresetName());
    }
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
        output->GoTo(0, Line1.InNoteLabel.getPosition());
        Line1.InNoteLabel.Display(output);
        
        output->GoTo(0, Line1.Out1NoteLabel.getPosition());
        Line1.Out1NoteLabel.Display(output);
        output->GoTo(0, Line1.Out2NoteLabel.getPosition());
        Line1.Out2NoteLabel.Display(output);
        
        output->GoTo(1, Line2.Out3NoteLabel.getPosition());
        Line2.Out3NoteLabel.Display(output);
        output->GoTo(1, Line2.Out4NoteLabel.getPosition());
        Line2.Out4NoteLabel.Display(output);
    }
    
    Task_BeginWithParams(DisplayActivity, DisplayWriter* output)
    {
        if (MidiStatus::getCurrent()->getMidiIsActive())
        {
            PartialDisplay(output);
            Task_YieldUntil(TaskScheduler::Wait(getId(), 30));
        }
        else
        {
            PartialDisplay(output);
        }
    }
    Task_End
    
private:
    uint8_t _task;
};



#endif /* REALTIMEPAGE_H_ */