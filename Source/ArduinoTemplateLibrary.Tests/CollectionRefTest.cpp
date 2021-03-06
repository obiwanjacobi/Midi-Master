#include "stdafx.h"
#include "FixedArray.h"
#include "CollectionRef.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class CollectionRefTest
	{
		typedef FixedArray<int, 2> ValueArray;

		static const int MagicNumber = 42;

	public: 
		[TestMethod]
		void Count_InitializedCollection_Zero()
		{
			ValueArray array;
			CollectionRef<ValueArray> tested(array);

			Assert::AreEqual((int)0, (int)tested.getCount());
		}

		[TestMethod]
		void Count_OneItem_One()
		{
			ValueArray array;
			CollectionRef<ValueArray> tested(array);

			tested.Add(0);

			Assert::AreEqual((int)1, (int)tested.getCount());
		}

		[TestMethod]
		void IsValidIndex_InvalidIndex_False()
		{
			ValueArray array;
			CollectionRef<ValueArray> tested(array);

			Assert::IsFalse(tested.IsValidIndex(0));
		}

		[TestMethod]
		void IsValidIndex_ValidIndex_True()
		{
			ValueArray array;
			CollectionRef<ValueArray> tested(array);
			
			tested.Add(0);

			Assert::IsTrue(tested.IsValidIndex(0));
		}

		[TestMethod]
		void GetAt_InvalidIndex_DefaultOfT()
		{
			ValueArray array;
			CollectionRef<ValueArray> tested(array);

			Assert::AreEqual(Default<int>::DefaultOfT, tested.GetAt(0));
		}

		[TestMethod]
		void GetAt_ValidIndex_Value()
		{
			ValueArray array;
			CollectionRef<ValueArray> tested(array);

			tested.Add(MagicNumber);

			Assert::AreEqual(MagicNumber, tested.GetAt(0));
		}

		[TestMethod]
		void Add_TooManyTimes_DoesNotCrash()
		{
			ValueArray array;
			CollectionRef<ValueArray> tested(array);

			for (int i = 0; i < 10; i++)
			{
				tested.Add(MagicNumber);
			}

			Assert::AreEqual(array.getCapacity(), tested.getCount());
		}
	};
}
