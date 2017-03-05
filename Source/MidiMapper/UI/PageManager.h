#ifndef PAGEMANAGER_H_
#define PAGEMANAGER_H_

#include "../ATL/Singleton.h"
#include "../ATL/PageController.h"
#include "RealtimePage.h"

using namespace ATL;

class PageManager : public Singleton<PageManager>, 
                    public PageController<LcdLines, 2>
{
    typedef PageController<LcdLines, 2> BaseT;

public:
    typedef Page<LcdLines> PageT;
    
    PageManager()
    :   _nextPage(NULL)
    {
        BaseT::Add(&RealtimeScreen);
    }
    
    // pages
    RealtimePage<PageManager> RealtimeScreen;
    
    inline bool IsCurrentScreen(PageT* screen)
    {
        return BaseT::getCurrentPage() == screen;
    }
    
    // navigate to the screen for editing the output map.
    inline bool EnterEditOutputMap(int outIndex)
    {
        // queue navigation and execute on display.
        
        
        _nextPage = &RealtimeScreen;    // test
        
        return false;
    }
    
    inline virtual bool OnNavigationCommand(NavigationCommands navCmd)
    {
        bool handled = BaseT::OnNavigationCommand(navCmd);
        
        
        
        return handled;
    }
    
private:
    PageT* _nextPage;
};


#endif /* PAGEMANAGER_H_ */