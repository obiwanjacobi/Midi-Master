#include "stdafx.h"

#include "ATL/Array.h"
#include "ValueSequence.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


namespace MidiMapperTests
{
    [TestClass]
    public ref class ValueSequenceTest
    {
        typedef ValueSequence<7> TestSequence;
        typedef ATL::Array<uint8_t, 7> TestArray;

    public: 
        [TestMethod]
        void Add_SingleIndex_CountIsOne()
        {
            TestSequence uut;
            uut.Add(42);

            Assert::AreEqual(1, (int)uut.getCount());
        }

        [TestMethod]
        void Add_SingleIndex_GetValue()
        {
            TestSequence uut;
            uut.Add(42);

            Assert::AreEqual(42, (int)uut.GetValueAt(0));
        }

        [TestMethod]
        void Add_SingleIndex_GetEncoding()
        {
            TestSequence uut;
            uut.Add(42);

            Assert::AreEqual((int)TestSequence::Value, (int)uut.GetEncodingAt(0));
        }

        [TestMethod]
        [Ignore]
        void Assign_SingleIndex_CorrectEncoding()
        {
            TestArray arr;
            arr.SetAt(0, 42);

            TestSequence uut;
            uut.Assign(arr);

            Assert::AreEqual((int)TestSequence::Value, (int)uut.GetEncodingAt(0));
        }

        [TestMethod]
        [Ignore]
        void Assign_MultipleIndexes_CorrectEncoding()
        {
            TestArray arr;
            arr.SetAt(0, 24);
            arr.SetAt(1, 42);

            TestSequence uut;
            uut.Assign(arr);

            Assert::AreEqual((int)TestSequence::Value, (int)uut.GetEncodingAt(0));
            Assert::AreEqual((int)TestSequence::Value, (int)uut.GetEncodingAt(1));
        }

        [TestMethod]
        [Ignore]
        void Assign_RangeOfOne_CorrectEncoding()
        {
            TestArray arr;
            arr.SetAt(0, 42);

            TestSequence uut;
            uut.Assign(arr);

            Assert::AreEqual((int)TestSequence::Value, (int)uut.GetEncodingAt(0));
        }
    };


    [TestClass]
    public ref class IndexIteratorTest
    {
        typedef ValueSequence<7> TestSequence;
        typedef SequenceIterator<TestSequence> TestIterator;

    public:
        [TestMethod]
        void MoveNext_SingleIndex_CanMove()
        {
            TestSequence col;
            col.Add(42);

            TestIterator uut(col);
            Assert::IsTrue(uut.MoveNext());
        }

        [TestMethod]
        void MoveNext_SingleIndex_ProduceValue()
        {
            TestSequence col;
            col.Add(42);

            TestIterator uut(col);
            uut.MoveNext();

            Assert::AreEqual(42, (int)uut.getCurrent());
        }

        [TestMethod]
        void MoveNext_SingleIndex_CannotMovePastEnd()
        {
            TestSequence col;
            col.Add(42);

            TestIterator uut(col);
            Assert::IsTrue(uut.MoveNext());
            Assert::IsFalse(uut.MoveNext());
        }

        [TestMethod]
        void MoveNext_TwoIndexes_ProduceValues()
        {
            TestSequence col;
            col.Add(42);
            col.Add(43);

            TestIterator uut(col);
            uut.MoveNext();
            Assert::AreEqual(42, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(43, (int)uut.getCurrent());
        }

        [TestMethod]
        void MoveNext_RangeOfOne_CannotMovePastEnd()
        {
            TestSequence col;
            col.AddRange(42, 43);

            TestIterator uut(col);
            Assert::IsTrue(uut.MoveNext());
            Assert::IsTrue(uut.MoveNext());
            Assert::IsFalse(uut.MoveNext());
        }

        [TestMethod]
        void MoveNext_RangeOfOne_ProduceValues()
        {
            TestSequence col;
            col.AddRange(42, 43);

            TestIterator uut(col);
            uut.MoveNext();
            Assert::AreEqual(42, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(43, (int)uut.getCurrent());
        }

        [TestMethod]
        void MoveNext_RangeOfMultiple_ProduceValues()
        {
            TestSequence col;
            col.AddRange(42, 45);

            TestIterator uut(col);
            uut.MoveNext();
            Assert::AreEqual(42, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(43, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(44, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(45, (int)uut.getCurrent());
        }

        [TestMethod]
        void MoveNext_MixedIndexesAndRangeOfOne_CannotMovePastEnd()
        {
            TestSequence col;
            col.Add(41);
            col.AddRange(42, 43);
            col.Add(44);

            TestIterator uut(col);
            Assert::IsTrue(uut.MoveNext());
            Assert::IsTrue(uut.MoveNext());
            Assert::IsTrue(uut.MoveNext());
            Assert::IsTrue(uut.MoveNext());
            Assert::IsFalse(uut.MoveNext());
        }

        [TestMethod]
        void MoveNext_MixedIndexesAndRangeOfMultiple_ProduceValues()
        {
            TestSequence col;
            col.Add(40);
            col.Add(41);
            col.AddRange(42, 45);
            col.Add(46);

            TestIterator uut(col);

            uut.MoveNext();
            Assert::AreEqual(40, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(41, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(42, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(43, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(44, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(45, (int)uut.getCurrent());

            uut.MoveNext();
            Assert::AreEqual(46, (int)uut.getCurrent());
        }
    };
}
