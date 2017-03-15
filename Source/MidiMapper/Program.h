#ifndef __PROGRAM_H__
#define __PROGRAM_H__


#include "DataTypes.h"
#include "MidiPatch.h"
#include "KeyBoardMatrix.h"

#include "ATL/IdentifiableObject.h"
#include "ATL/PushButton.h"
#include "ATL/Singleton.h"
#include "ATL/NavigationController.h"

using namespace ATL;

class Program : public Singleton<Program>
{
public:
	void Initialize();
	void Run();

	LCD Lcd;
    PushButton<IdentifiableObject<KeyboardMatrix>, TaskScheduler, 30, 350> KeyMatrix;
	
private:
	void OpenLcd();
    
    #define KeyLeft 8
    #define KeyRight 128
    #define KeyUp 4
    #define KeyDown 64
    #define KeyEnter 32
    #define KeyExit 2
    NavigationCommands TranslateKeyToCommand(uint8_t keyCode);
};


#endif //__PROGRAM_H__
