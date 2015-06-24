#include <gtest/gtest.h>
#include <root/memory.h>

// Test parameters.
static const int BufferSize = 10;

TEST(MemoryTest, ZeroInteger)
{
	Root::U32 integer = 0xFFFFFFFF;
	Root::Memory::Zero(&integer);
	EXPECT_EQ(integer, 0);
}

TEST(MemoryTest, ZeroString)
{
	char string[] = "This is a test string.";
	Root::Memory::Zero(string, sizeof(string));
	for (Root::U32 i = 0; i < sizeof(string); ++i)
	{
		EXPECT_EQ(string[i], 0);
	}
}

TEST(MemoryTest, CopyInteger)
{
	Root::U32 integer = 0;
	Root::U32 other = 0xFFFFFFFF;
	Root::Memory::Copy(&other, &integer, sizeof(integer));
	EXPECT_EQ(integer, 0xFFFFFFFF);
	EXPECT_EQ(other, 0xFFFFFFFF);
}

TEST(MemoryTest, NonNativeSizeCopy)
{
	char data[BufferSize];
	char copy[BufferSize];
	for (Root::U32 i = 0; i < sizeof(data); ++i) {
		data[i] = i;
	}
	Root::Memory::Copy(&data, copy, sizeof(data));
	for (Root::U32 i = 0; i < sizeof(data); ++i) {
		EXPECT_EQ(copy[i], i);
		EXPECT_EQ(data[i], i);
	}
}

TEST(MemoryTest, ArraySizeTest)
{
	Root::U32 buffer[BufferSize];
	Root::Size length = Root::Memory::ArraySize(buffer);
	EXPECT_EQ(length, BufferSize);
}
