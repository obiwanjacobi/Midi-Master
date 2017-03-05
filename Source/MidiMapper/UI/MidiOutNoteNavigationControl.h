#ifndef MIDIOUTNOTENAVIGATIONCONTROL_H_
#define MIDIOUTNOTENAVIGATIONCONTROL_H_

#include "../ATL/InputControl.h"
#include "../DataTypes.h"
#include "../MidiStatus.h"

using namespace ATL;

static const char* ActivityChar = "!";


template<typename PageManagerT>
class MidiOutNoteNavigationControl : public InputControl
{
public:
    MidiOutNoteNavigationControl(uint8_t outIndex, uint8_t pos = 0)
        : InputControl(pos), _outIndex(outIndex)
    { }
        
    inline virtual void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal)
    {
        if (mode == ControlDisplayMode::Cursor) return;
        
        if (MidiStatus::getCurrent()->getMidiOutIsActive(_outIndex))
        {
            output->Display(ActivityChar);
        }
        else
        {
            StringWriter<1> str;
            str.Write(_outIndex + 1);
            output->Display(str);
        }        
    }
    
    inline virtual bool OnNavigationCommand(NavigationCommands navCmd)
    {
        if (navCmd == NavigationCommands::Enter)
        {
            return PageManagerT::getCurrent()->EnterEditOutputMap(_outIndex);
        }
        return false;
    }
private:
    uint8_t _outIndex;
};


#endif /* MIDIOUTNOTENAVIGATIONCONTROL_H_ */