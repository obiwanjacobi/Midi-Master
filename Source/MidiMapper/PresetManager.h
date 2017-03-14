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

		_currentPatch = _firstPatch + index;
		_index = index;
		return true;
	}

	inline uint8_t getCurrentPresetIndex() const
	{
		return _index;
	}

    inline const char* getCurrentPresetName() const
    {
        return _currentPatch->Name;
    }
    
    inline bool getIsDirty() const
    {
        return _isDirty;
    }
    
private:
	MidiPatch* _firstPatch;
    MidiPatch* _currentPatch;

	uint8_t _index;
    bool _isDirty;
};



#endif /* PRESETMANAGER_H_ */