#include "myArray_class.h"
#include "gtest/gtest.h"



TEST(MyArrayTest, DefaultConstructor)
{
    myArray<int> arr;
    EXPECT_EQ(arr.length(), 0);
    EXPECT_GE(arr.memory(), 10);
}

TEST(MyArrayTest, SingleElementConstructor)
{
    int value = 42;
    myArray<int> arr(value);
    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.at(0), value);
}

TEST(MyArrayTest, ArrayConstructor)
{
    int values[] = {1, 2, 3, 4};
    myArray<int> arr(values, 4);
    EXPECT_EQ(arr.length(), 4);
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(3), 4);
}

TEST(MyArrayTest, CopyConstructor)
{
    int values[] = {1, 2, 3};
    myArray<int> arr1(values, 3);
    myArray<int> arr2(arr1, 3);
    EXPECT_EQ(arr2.length(), 3);
    EXPECT_EQ(arr2.at(0), 1);
    EXPECT_EQ(arr2.at(2), 3);
}

TEST(MyArrayTest, PopFromNonEmptyArray)
{
    int values[] = {10, 20, 30};
    myArray<int> arr(values, 3);
    auto popped = arr.pop(1);
    EXPECT_EQ(popped, 20);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.at(0), 10);
    EXPECT_EQ(arr.at(1), 30);
}

TEST(MyArrayTest, PopFromEmptyArray)
{
    myArray<int> arr;
    EXPECT_THROW(arr.pop(), std::out_of_range);
}

TEST(MyArrayTest, IndexFunctionSuccess)
{
    int values[] = {5, 10, 15};
    myArray<int> arr(values, 3);
    EXPECT_EQ(arr.index(10), 1);
}

TEST(MyArrayTest, IndexFunctionFailure)
{
    int values[] = {5, 10, 15};
    myArray<int> arr(values, 3);
    EXPECT_THROW(arr.index(20), std::out_of_range);
}

TEST(MyArrayTest, InFunctionTrue)
{
    int values[] = {1, 2, 3};
    myArray<int> arr(values, 3);
    EXPECT_TRUE(arr.in(2));
}

TEST(MyArrayTest, InFunctionFalse)
{
    int values[] = {1, 2, 3};
    myArray<int> arr(values, 3);
    EXPECT_FALSE(arr.in(4));
}


TEST(MyArrayTest, AppendSingleElement)
{
    myArray<int> arr;
    arr.append(100);
    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.at(0), 100);
}

TEST(MyArrayTest, AppendMultipleElements)
{
    myArray<int> arr;
    arr.append(10);
    arr.append(20);
    arr.append(30);
    EXPECT_EQ(arr.length(), 3);
    EXPECT_EQ(arr.at(2), 30);
}

TEST(MyArrayTest, ReverseArray)
{
    int values[] = {1, 2, 3};
    myArray<int> arr(values, 3);
    arr.reverse();
    EXPECT_EQ(arr.at(0), 3);
    EXPECT_EQ(arr.at(2), 1);
}

TEST(MyArrayTest, ClearArray)
{
    int values[] = {10, 20, 30};
    myArray<int> arr(values, 3);
    arr.clear();
    EXPECT_EQ(arr.length(), 0);
}

TEST(MyArrayTest, ClearArrayWithShrink)
{
    int values[] = {10, 20, 30};
    myArray<int> arr(values, 3);
    arr.clear(true);
    EXPECT_EQ(arr.length(), 0);
    EXPECT_LT(arr.memory(), 3 * sizeof(Node<int>));
}

TEST(MyArrayTest, SortNumbers)
{
    int values[] = {5, 3, 8, 1};
    myArray<int> arr(values, 4);
    arr.sort(true);
    EXPECT_EQ(arr.at(0), 8);
    EXPECT_EQ(arr.at(3), 1);
}

TEST(MyArrayTest, StrFunction)
{
    int values[] = {1, 2, 3};
    myArray<int> arr(values, 3);
    std::string result = arr.str();
    EXPECT_EQ(result, "1, 2, 3");
}

TEST(MyArrayTest, CopyFunction)
{
    int values[] = {7, 8, 9};
    myArray<int> arr1(values, 3);
    myArray<int> arr2 = arr1.copy();
    EXPECT_EQ(arr2.length(), 3);
    EXPECT_EQ(arr2.at(1), 8);
}

TEST(MyArrayTest, AccessOutOfBoundsThrowsException)
{
    int values[] = {1, 2, 3};
    myArray<int> arr(values, 3);
    EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST(MyArrayTest, SortWord)
{
    char values[] = "Banana";
    myArray<char> arr(values, 6);
    arr.sort(true);
    EXPECT_EQ(arr.at(0), 'n');
    EXPECT_EQ(arr.at(4), 'a');
    EXPECT_EQ(arr.at(5), 'B');
}


TEST(MyArrayTest, InitializationTests)
{

    myArray<int> testArray;
    EXPECT_EQ(testArray.length(), 0);
    EXPECT_EQ(testArray.memory(), 10);
    EXPECT_TRUE(!testArray);

    int value = 42;
    myArray<int> singleElementArray(value);
    EXPECT_EQ(singleElementArray.length(), 1);
    EXPECT_EQ(singleElementArray.front(), 42);
    EXPECT_EQ(singleElementArray.back(), 42);

    int values[] = {1, 2, 3, 4, 5};
    myArray<int> arrayFromValues(values, 5);
    EXPECT_EQ(arrayFromValues.length(), 5);
    EXPECT_EQ(arrayFromValues.at(0), 1);
    EXPECT_EQ(arrayFromValues.at(4), 5);

    myArray<int> originalArray(values, 3);
    myArray<int> copiedArray(originalArray, originalArray.length());
    EXPECT_EQ(copiedArray.length(), 3);
    EXPECT_EQ(copiedArray.at(0), 1);
    EXPECT_EQ(copiedArray.at(1), 2);
    EXPECT_EQ(copiedArray.at(2), 3);
    copiedArray[0] = 10;
    EXPECT_EQ(originalArray.at(0), 1);
}

TEST(MyArrayTest, ElementAccessTests)
{
    int values[] = {10, 20, 30, 40, 50};
    myArray<int> testArray(values, 5);

    EXPECT_EQ(testArray.at(0), 10);
    EXPECT_EQ(testArray.at(4), 50);

    EXPECT_EQ(testArray.at(-1), 50);
    EXPECT_EQ(testArray.at(-5), 10);

    EXPECT_THROW(testArray[5], std::out_of_range);
    EXPECT_THROW(testArray.at(-6), std::out_of_range);
}

TEST(MyArrayTest, AppendAndPopTests)
{
    myArray<int> testArray;

    testArray.append(1);
    testArray.append(2);
    testArray.append(3);
    EXPECT_EQ(testArray.length(), 3);
    EXPECT_EQ(testArray.at(0), 1);
    EXPECT_EQ(testArray.at(2), 3);

    EXPECT_EQ(testArray.pop(), 3);
    EXPECT_EQ(testArray.length(), 2);

    int values[] = {1, 2, 3, 4};
    myArray<int> populatedArray(values, 4);
    EXPECT_EQ(populatedArray.pop(1), 2);
    EXPECT_EQ(populatedArray.length(), 3);
    EXPECT_EQ(populatedArray.at(1), 3);

    myArray<int> emptyArray;
    EXPECT_THROW(emptyArray.pop(), std::out_of_range);
}

TEST(MyArrayTest, SearchAndMembershipTests)
{
    int values[] = {1, 2, 3, 2, 4};
    myArray<int> testArray(values, 5);

    EXPECT_EQ(testArray.index(2), 1);
    EXPECT_EQ(testArray.index(2, 2), 3);

    EXPECT_THROW(testArray.index(10), std::out_of_range);

    EXPECT_TRUE(testArray.in(2));
    EXPECT_FALSE(testArray.in(10));

    EXPECT_EQ(testArray.count(2), 2);
    EXPECT_EQ(testArray.count(5), 0);
}

TEST(MyArrayTest, SortingAndReversalTests)
{
    int values[] = {4, 2, 5, 1, 3};
    myArray<int> testArray(values, 5);

    testArray.sort();
    EXPECT_EQ(testArray.at(0), 1);
    EXPECT_EQ(testArray.at(4), 5);

    testArray.sort(true);
    EXPECT_EQ(testArray.at(0), 5);
    EXPECT_EQ(testArray.at(4), 1);

    testArray.reverse();
    EXPECT_EQ(testArray.at(0), 1);
    EXPECT_EQ(testArray.at(4), 5);
}

TEST(MyArrayTest, SlicingTests)
{
    int values[] = {1, 2, 3, 4, 5};
    myArray<int> testArray(values, 5);

    myArray<int> sliced = testArray[1, 3];
    EXPECT_EQ(sliced.length(), 3);
    EXPECT_EQ(sliced.at(0), 2);
    EXPECT_EQ(sliced.at(2), 4);

    myArray<int> slicedReverse = testArray[1, 4, -1];
    EXPECT_EQ(slicedReverse.length(), 4);
    EXPECT_EQ(slicedReverse.at(0), 5);
    EXPECT_EQ(slicedReverse.at(3), 2);

    EXPECT_THROW(slicedReverse[5], std::out_of_range);
}

TEST(MyArrayTest, SubarrayTests)
{
    int values1[] = {1, 2, 3, 4, 5};
    int values2[] = {2, 3};
    myArray<int> array1(values1, 5);
    myArray<int> array2(values2, 2);

    EXPECT_TRUE(array1.isSubarray(array2));

    int values3[] = {6, 7};
    myArray<int> array3(values3, 2);
    EXPECT_FALSE(array1.isSubarray(array3));
}

TEST(MyArrayTest, AdvancedOperationTests)
{
    int values[] = {10, 20, 30, 40};
    myArray<int> testArray(values, 4);

    testArray.insert(25, 2);
    EXPECT_EQ(testArray.at(2), 25);
    EXPECT_EQ(testArray.length(), 5);

    testArray.remove(30);
    EXPECT_EQ(testArray.length(), 4);
    EXPECT_FALSE(testArray.in(30));
}

TEST(MyArrayTest, MemoryManagementTests)
{
    myArray<int> testArray;

    testArray.append(1);
    testArray.clear();
    EXPECT_EQ(testArray.length(), 0);
    EXPECT_EQ(testArray.memory(), 10);

    for(int i = 0; i < 11; ++i)
        testArray.append(1);
    testArray.clear(false);
    EXPECT_EQ(testArray.length(), 0);
    EXPECT_GT(testArray.memory(), 10);
}

auto square = [](int in){return in * in; };
auto isEven = [](int in){return (in % 2) == 0; };

TEST(MyArrayTest, Vectorise_EmptyArray)
{
    myArray<int> testArray;
    testArray.vectorise(square);
    EXPECT_EQ(testArray.length(), 0);
}

TEST(MyArrayTest, Vectorise_SingleElement)
{
    myArray<int> testArray;
    testArray.append(5);
    testArray.vectorise(square);
    EXPECT_EQ(testArray[0], 25);
}

TEST(MyArrayTest, Vectorise_MultipleElements)
{
    myArray<int> testArray;
    testArray.append(1);
    testArray.append(2);
    testArray.append(3);
    testArray.append(4);

    testArray.vectorise(square);

    EXPECT_EQ(testArray[0], 1);
    EXPECT_EQ(testArray[1], 4);
    EXPECT_EQ(testArray[2], 9);
    EXPECT_EQ(testArray[3], 16);
}

TEST(MyArrayTest, Vectorise_NegativeElements)
{
    myArray<int> testArray;
    testArray.append(-2);
    testArray.append(-3);

    testArray.vectorise(square);

    EXPECT_EQ(testArray[0], 4);
    EXPECT_EQ(testArray[1], 9);
}

TEST(MyArrayTest, CountIf_EmptyArray)
{
    myArray<int> testArray;
    EXPECT_EQ(testArray.countIf(isEven), 0);
}

TEST(MyArrayTest, CountIf_AllMatch)
{
    myArray<int> testArray;
    testArray.append(2);
    testArray.append(4);
    testArray.append(6);

    EXPECT_EQ(testArray.countIf(isEven), 3);
}

TEST(MyArrayTest, CountIf_NoneMatch)
{
    myArray<int> testArray;
    testArray.append(1);
    testArray.append(3);
    testArray.append(5);

    EXPECT_EQ(testArray.countIf(isEven), 0);
}

TEST(MyArrayTest, CountIf_SomeMatch)
{
    myArray<int> testArray;
    testArray.append(1);
    testArray.append(2);
    testArray.append(3);
    testArray.append(4);

    EXPECT_EQ(testArray.countIf(isEven), 2);
}

TEST(MyArrayTest, CountIf_CustomPredicate)
{
    myArray<int> testArray;
    testArray.append(10);
    testArray.append(20);
    testArray.append(30);

    auto greaterThan15 = [](int x) { return x > 15; };

    EXPECT_EQ(testArray.countIf(greaterThan15), 2);
}


TEST(MyArrayTest, Plus)
{
    myArray<int> testArray;
    testArray.append(2);
    testArray.append(4);
    testArray.append(7);

    int nums[] = {67, 24, 246, 60};
    myArray<int> testArray2(nums, 4);
    myArray<int> result = (testArray + testArray2);
    EXPECT_EQ(result.countIf(isEven), 5);
}