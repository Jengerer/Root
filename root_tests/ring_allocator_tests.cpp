#include <gtest/gtest.h>
#include <root/ring_allocator.h>

TEST(RingAllocatorTest, HandleSingleAllocation)
{
	static const Root::U32 BufferSize = 8;
	Root::RingAllocator<BufferSize> allocator;
	Root::U32* number = allocator.Allocate<Root::U32>();
	ASSERT_NE(number, nullptr);
	*number = BufferSize;
	EXPECT_EQ(*number, BufferSize);
	allocator.Free(number);
}

TEST(RingAllocatorTest, HandlesAlignment)
{
	static const Root::U32 BufferSize = 16;
	Root::RingAllocator<BufferSize> allocator;
	Root::U16* shortNumber = allocator.Allocate<Root::U16>();
	ASSERT_NE(shortNumber, nullptr);
	allocator.Free(shortNumber);
	Root::U32* number = allocator.Allocate<Root::U32>();
	ASSERT_NE(number, nullptr);
	ASSERT_NE(reinterpret_cast<Root::UPointer>(shortNumber), reinterpret_cast<Root::UPointer>(number));
	ASSERT_EQ(reinterpret_cast<Root::UPointer>(number) % std::alignment_of<Root::U32>(), 0);
}