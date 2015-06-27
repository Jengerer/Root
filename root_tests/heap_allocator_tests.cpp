#include <gtest/gtest.h>
#include <root/heap_allocator.h>

// Test structure.
struct TestStructure
{
	static const int DefaultValue = 0xCDCD;
	TestStructure() : TestStructure(DefaultValue)
	{
	}

	TestStructure(int newValue) : value(newValue)
	{
	}

	int value;
};

TEST(HeapAllocatorTest, HandleSimpleAllocation)
{
	Root::HeapAllocator& allocator = Root::HeapAllocator::instance;
	int* number = allocator.Allocate<int>();
	EXPECT_NE(number, nullptr);
	allocator.Free(number);
}

TEST(HeapAllocatorTest, HandleArrayAllocation)
{
	static const int NumberCount = 10;
	Root::HeapAllocator& allocator = Root::HeapAllocator::instance;
	TestStructure* structures = allocator.AllocateArray<TestStructure>(NumberCount);
	ASSERT_NE(structures, nullptr);
	for (int i = 0; i < NumberCount; ++i) {
		EXPECT_EQ(structures[i].value, TestStructure::DefaultValue);
	}
}

TEST(HeapAllocatorTest, HandleClassParameterAllocation)
{
	static const int TestValue = 0xABAB;
	Root::HeapAllocator& allocator = Root::HeapAllocator::instance;
	TestStructure* structure = allocator.Allocate<TestStructure>(TestValue);
	ASSERT_NE(structure, nullptr);
	EXPECT_EQ(structure->value, TestValue);
	allocator.Free(structure);
}