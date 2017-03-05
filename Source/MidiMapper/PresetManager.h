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
        _currentPatch = memPatch;
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
    MidiPatch* _currentPatch;
    bool _isDirty;
};



#endif /* PRESETMANAGER_H_ */