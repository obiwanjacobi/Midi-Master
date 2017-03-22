#include "stdafx.h"
#include "Arduino.h"
#include "Control.h"
#include "PanelControlContainer.h"
#include "TestControls.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
    class TestPanel : public PanelControlContainer<2>
    {};

    [TestClass]
    public ref class PanelControlContainerTest
    {
    public:
        [TestMethod]
        void Panel_GetAt_FirstControl_IsIndexZero()
        {
            TestPanel tested;
            TestInputControl tic;

            tested.Add(&tic);

            Assert::IsTrue(&tic == tested.GetAt(0));
        }

        [TestMethod]
        void Panel_IndexOf_FirstControl_IsIndexZero()
        {
            TestPanel tested;
            TestInputControl tic;

            tested.Add(&tic);

            Assert::AreEqual((int16_t)0, tested.IndexOf(&tic));
        }
    };
}
