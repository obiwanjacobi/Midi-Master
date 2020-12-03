#ifndef PRESETMANAGER_H_
#define PRESETMANAGER_H_

#include "ATL/Singleton.h"
#include "MidiPatch.h"

using namespace ATL;

class PresetManager : public Singleton<PresetManager>
{
public:
    PresetManager(MidiPatch* memPatch)
        : _isDirty(false)
    {
		_firstPatch = memPatch;
        _currentPatch = memPatch;
    }

	inline bool LoadPreset(uint8_t index)
	{
		if (index > 1)
		{
			return false;
		}

		// TEMP!
		_currentPatch = _firstPatch + index;
		_presetIndex = index;
		return true;
	}

	inline PatchNameString* getPatchNameString() const
	{
		return &_currentPatch->Name;
	}

	inline uint8_t getCurrentPresetIndex() const
	{
		return _presetIndex;
	}

    inline const char* getCurrentPresetName() const
    {
        return _currentPatch->Name;
    }

	inline void MarkDirty()
	{
		_isDirty = true;
	}

    inline bool getIsDirty() const
    {
        return _isDirty;
    }

    inline MidiPatch* getCurrentPreset()
    {
        return _currentPatch;
    }

    void SelectOutput(uint8_t outIndex)
    {
        _mapIndex = outIndex;
    }

    inline OutputNameString* getCurrentOutputNameString() const
    {
        return &_currentPatch->Maps[_mapIndex].Name;
    }

    inline const char* getCurrentOutputName() const
    {
        return _currentPatch->Maps[_mapIndex].Name;
    }

    MidiMap* getCurrentMap()
    {
        return &_currentPatch->Maps[_mapIndex];
    }

    uint8_t getCurrentEntryIndex() const
    {
        return _entryIndex;
    }

    void SelectMapEntry(uint8_t index)
    {
        _entryIndex = index;
    }

    MidiMapEntry* getCurrentMapEntry()
    {
        return &getCurrentMap()->Entries[_entryIndex];
    }


private:
	MidiPatch* _firstPatch;
    MidiPatch* _currentPatch;

	uint8_t _presetIndex;
    uint8_t _mapIndex;
    uint8_t _entryIndex;

    bool _isDirty;
};


#endif /* PRESETMANAGER_H_ */