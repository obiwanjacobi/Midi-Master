#ifndef MIDIOUTNOTENAVIGATIONCONTROL_H_
#define MIDIOUTNOTENAVIGATIONCONTROL_H_

#include "../ATL/InputControl.h"
#include "../DataTypes.h"
#include "../MidiStatus.h"

using namespace ATL;

static const char* ActivityChar = "\0x07";

template<typename PageManagerT, const uint8_t OutputIndex>
class MidiOutNoteNavigationControl : public InputControl
{
public:
    MidiOutNoteNavigationControl(uint8_t pos = 0)
        : InputControl(pos)
    { }

    inline virtual void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal)
    {
        if (mode == ControlDisplayMode::Cursor) return;

        PresetManager* presetMgr = PresetManager::getCurrent();
        MidiMap* map = &presetMgr->getCurrentPreset()->Maps[OutputIndex];
		output->Display(map->Name);

        if (MidiStatus::getCurrent()->getMidiOutIsActive(OutputIndex))
        {
            output->Display(ActivityChar);
        }
        //else
        //{
            //StringWriter<1> str;
            //str.Write(OutputIndex + 1);
            //output->Display(str);
        //}
    }

    inline virtual bool OnNavigationCommand(NavigationCommands navCmd)
    {
        if (navCmd == NavigationCommands::Enter)
        {
            return PageManagerT::getCurrent()->EnterEditOutputMap(OutputIndex);
        }
        return false;
    }
};


#endif /* MIDIOUTNOTENAVIGATIONCONTROL_H_ */