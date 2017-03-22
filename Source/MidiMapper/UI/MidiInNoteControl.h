#ifndef MIDIINNOTECONTROL_H_
#define MIDIINNOTECONTROL_H_

#include "../ATL/InputControl.h"
#include "../MidiStatus.h"

using namespace ATL;

class MidiInNoteControl : public Control
{
public:
    MidiInNoteControl(uint8_t pos = 0)
        : Control(pos)
    { }
    
    inline void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal) override
    {
        if (mode == ControlDisplayMode::Cursor) return;
        
        if (MidiStatus::getCurrent()->getMidiInIsActive())
        {
            output->Display("!");
        }
        else
        {
            output->Display(" ");
        }
    }
};



#endif /* MIDIINNOTECONTROL_H_ */