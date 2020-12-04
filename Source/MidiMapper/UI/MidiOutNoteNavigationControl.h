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

        if (MidiStatus::getCurrent()->getMidiOutIsActive(OutputIndex))
        {
            FixedString<OutputNameMaxLength> buf(map->Name);
            buf[OutputNameMaxLength - 1] = 0;    // chop off last char
            output->Display(buf);
            output->Display(ActivityChar);
        }
        else
            output->Display(map->Name);
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