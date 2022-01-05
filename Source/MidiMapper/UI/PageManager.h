#ifndef PAGEMANAGER_H_
#define PAGEMANAGER_H_

#include "../ATL/Singleton.h"
#include "../ATL/PageController.h"
#include "RealtimePage.h"
#include "EditOutputMapPage.h"
#include "TestPage.h"

using namespace ATL;

#define NumberOfPages	5

class PageManager : public Singleton<PageManager>,
                    public PageController<LcdLines, NumberOfPages>
{
    typedef PageController<LcdLines, NumberOfPages> BaseT;

public:
    typedef Page<LcdLines> PageT;

    PageManager()
		: _currentPage(nullptr)
    {
        BaseT::Add(&RealtimeScreen);
        BaseT::Add(&EditOutputScreen);
        //BaseT::Add(&TestScreen);
    }

    // pages
    RealtimePage<PageManager> RealtimeScreen;
    EditOutputMapPage<PageManager> EditOutputScreen;
    //TestPage<PageManager> TestScreen;


    inline bool IsCurrentScreen(PageT* screen)
    {
        return BaseT::getCurrentPage() == screen;
    }

    void Display(LCD* lcd)
    {
        if (_currentPage != BaseT::getCurrentPage())
        {
            lcd->ClearDisplay();
            lcd->ReturnHome();
            _currentPage = BaseT::getCurrentPage();
        }

        BaseT::Display(lcd);
    }

    // navigate to the screen for editing the output map.
    inline bool EnterEditOutputMap(int outIndex)
    {
        PresetManager* presetMgr = PresetManager::getCurrent();
        presetMgr->SelectOutput(outIndex);

        EditOutputScreen.Update();
        BaseT::setCurrentControl(&EditOutputScreen);

        return true;
    }

    inline bool OnNavigationCommand(NavigationCommands navCmd) override
    {
        // bypass the next-page logic of PageController
        bool handled = BaseT::OnNavigationCommandCurrentPage(navCmd);

        if (!handled && navCmd == NavigationCommands::Enter)
        {
            PageT* page = BaseT::getCurrentPage();
            page->OnNavigationCommand(NavigationCommands::Down);
        }

        return handled;
    }

private:
    PageT* _currentPage;
};


#endif /* PAGEMANAGER_H_ */