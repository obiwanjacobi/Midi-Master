#include "stdafx.h"
#include "..\MidiMapper\ATL\RingBufferFast.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace ATL;

namespace MidiMapperTests2
{
    [TestClass]
    public ref class RingBufferFastTest
    {
    public: 
        [TestMethod]
        void getCount_NewInstance_IsZero()
        {
            RingBufferFast<uint8_t, 5> tested;

            Assert::IsTrue(tested.getCount() == 0);
        };

        [TestMethod]
        void getCount_Empty_IsZero()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Read();

            Assert::IsTrue(tested.getCount() == 0);
        };

        [TestMethod]
        void getCount_AfterWrapArround_IsCorrect()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);   // full
            tested.Read();
            tested.Read();
            tested.Read();
            tested.Write(42);   // wrap around

            Assert::IsTrue(tested.getCount() == 3);
        };

        [TestMethod]
        void getCount_OneWrite_IsOne()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);

            Assert::IsTrue(tested.getCount() == 1);
        };

        [TestMethod]
        void getCount_AlmostFull_IsOneLessCapacity()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);

            Assert::AreEqual((int)tested.getCount(), tested.getCapacity() - 1);
        };

        [TestMethod]
        void getCount_Full_IsCapacity()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);

            Assert::AreEqual(tested.getCount(), tested.getCapacity());
        };

        [TestMethod]
        void getCanWrite_Empty_True()
        {
            RingBufferFast<uint8_t, 5> tested;

            Assert::IsTrue(tested.getCanWrite());
        };

        [TestMethod]
        void getCanWrite_AlmostFull_True()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);

            Assert::IsTrue(tested.getCanWrite());
        };

        [TestMethod]
        void getCanWrite_Full_False()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);

            Assert::IsFalse(tested.getCanWrite());
        };

        [TestMethod]
        void Write_First_Success()
        {
            RingBufferFast<uint8_t, 5> tested;
            bool success = tested.Write(42);

            Assert::IsTrue(success);
        };

        [TestMethod]
        void Write_AlmostFull_Success()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            bool success = tested.Write(42);

            Assert::IsTrue(success);
        };

        [TestMethod]
        void Write_Full_Success()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            bool success = tested.Write(42);    // full

            Assert::IsTrue(success);
        };

        [TestMethod]
        void Write_Overrun_False()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);   // full
            bool success = tested.Write(42);

            Assert::IsFalse(success);
        };

        [TestMethod]
        void Write_WrapAround_True()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);
            tested.Write(42);   // full
            tested.Read();
            tested.Read();
            tested.Read();
            tested.Write(42);   // wrap around
            tested.Write(42);
            bool success = tested.Write(42); // full

            Assert::IsTrue(success);
        };


        [TestMethod]
        void Read_First_Success()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);

            Assert::AreEqual((int)tested.Read(), 42);
        };

        [TestMethod]
        void Read_Full_Success()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(43);
            tested.Write(44);
            tested.Write(45);
            tested.Write(46);

            Assert::AreEqual((int)tested.Read(), 42);
            Assert::AreEqual((int)tested.Read(), 43);
            Assert::AreEqual((int)tested.Read(), 44);
            Assert::AreEqual((int)tested.Read(), 45);
            Assert::AreEqual((int)tested.Read(), 46);
        };

        [TestMethod]
        void Read_WrapAround_Success()
        {
            RingBufferFast<uint8_t, 5> tested;
            tested.Write(42);
            tested.Write(43);
            tested.Write(44);
            tested.Write(45);
            tested.Write(46);   // full

            Assert::AreEqual((int)tested.Read(), 42);
            Assert::AreEqual((int)tested.Read(), 43);
            Assert::AreEqual((int)tested.Read(), 44);

            tested.Write(47);   // wrap around
            tested.Write(48);

            Assert::AreEqual((int)tested.Read(), 45);
            Assert::AreEqual((int)tested.Read(), 46);
            Assert::AreEqual((int)tested.Read(), 47);
            Assert::AreEqual((int)tested.Read(), 48);
        };
    };
}
