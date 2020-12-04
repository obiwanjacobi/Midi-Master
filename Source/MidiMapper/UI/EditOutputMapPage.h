#ifndef EDITOUTPUTMAPPAGE_H_
#define EDITOUTPUTMAPPAGE_H_

#include "../ATL/PageController.h"
#include "NameTextControl.h"
#include "MapEntrySelectControl.h"
#include "../StringExtensions.h"

using namespace ATL;

#define OutputMapSubPages 3

typedef NameTextControl<OutputNameMaxLength> OutputNameTextControl;

template<typename PageManagerT>
class EditOutputMapLine1 : public Line<2>
{
    typedef Line<2> BaseT;

public:
    EditOutputMapLine1()
        : OutputNameText(0), MapEntrySelect(this, 6)
    {
        Add(&OutputNameText);
        Add(&MapEntrySelect);
    }

    OutputNameTextControl OutputNameText;
    MapEntrySelectControl<EditOutputMapLine1<PageManagerT>> MapEntrySelect;

    // MapEntrySelectControl callbacks
    inline const char* getText()
    {
        uint8_t val = PresetManager::getCurrent()->getCurrentEntryIndex() + 1;

        return ToString::Integer<2>(val);
    }

    inline void IncrementValue()
    {
        MoveToMapEntry(1);
    }

    inline void DecrementValue()
    {
        MoveToMapEntry(-1);
    }

private:
    inline void MoveToMapEntry(int8_t delta)
    {
        PresetManager* presetMgr = PresetManager::getCurrent();

        uint8_t index = presetMgr->getCurrentEntryIndex() + delta;
        if (index >= 0 && index < MaxMapEntries)
        {
            presetMgr->SelectMapEntry(index);

            //MidiMapEntry* entry = presetMgr->getCurrentMapEntry();
            // TODO: init lines
        }
    }
};

template<typename PageManagerT>
class EditOutputMapLine2 : public Line<2>
{
    typedef Line<2> BaseT;

public:
    EditOutputMapLine2()
    {
    }
};

template<typename PageManagerT>
class EditOutputMapPage : public Page<LcdLines>
{
public:
    EditOutputMapPage()
    {
        Add(&Line1);
    }

    EditOutputMapLine1<PageManagerT> Line1;

    inline void Update()
    {
        Line1.OutputNameText.setString(PresetManager::getCurrent()->getCurrentOutputNameString());
    }
};



#endif /* EDITOUTPUTMAPPAGE_H_ */