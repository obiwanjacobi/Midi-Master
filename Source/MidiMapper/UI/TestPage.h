#ifndef TESTPAGE_H_
#define TESTPAGE_H_

#include "../Atl/LabelControl.h"
#include "../Atl/Line.h"
#include "../Atl/Page.h"

using namespace ATL;

template<typename PageManagerT>
class TestLine1 : public Line<2>
{
public:
    TestLine1()
        : Ctrl1("Test Ctrl 1", 0), Ctrl2("Test Ctrl 2", 12)
    {
        Add(&Ctrl1);
        Add(&Ctrl2);
    }

    LabelControl Ctrl1;
    LabelControl Ctrl2;
};

template<typename PageManagerT>
class TestLine2 : public Line<2>
{
    public:
    TestLine2()
        : Ctrl1("Test Ctrl 3", 0), Ctrl2("Test Ctrl 4", 12)
    {
        Add(&Ctrl1);
        Add(&Ctrl2);
    }

    LabelControl Ctrl1;
    LabelControl Ctrl2;
};

template<typename PageManagerT>
class TestPage : public Page<LcdLines>
{
public:
    TestPage()
    {
        Add(&Line1);
        Add(&Line2);
    }

    TestLine1<PageManagerT> Line1;
    TestLine2<PageManagerT> Line2;
};


#endif /* TESTPAGE_H_ */