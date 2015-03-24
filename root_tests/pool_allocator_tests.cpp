#include <gtest/gtest.h>
#include "pool_allocator.h"

// Test parameters.
static const int PoolSize = 20;
typedef int PoolType;

TEST(PoolAllocatorTest, HandleSingleAllocation)
{
	Root::PoolAllocator<PoolType, PoolSize> pool;
	PoolType* object = pool.Allocate();
	EXPECT_NE(object, nullptr);
}

TEST(PoolAllocatorTest, HandlesRelease)
{
	// Just don't crash...
	Root::PoolAllocator<PoolType, PoolSize> pool;
	PoolType* object = pool.Allocate();
	ASSERT_NE(object, nullptr);
	pool.Free(object);
}

TEST(PoolAllocatorTest, HandlesFullAllocation)
{
	Root::PoolAllocator<PoolType, PoolSize> pool;
	for (int i = 0; i < PoolSize; ++i)
	{
		PoolType* object = pool.Allocate();
		ASSERT_NE(object, nullptr);
	}
}

TEST(PoolAllocatorTest, HandlesOverflow)
{
	Root::PoolAllocator<PoolType, PoolSize> pool;
	PoolType* object;
	for (int i = 0; i < PoolSize; ++i)
	{
		object = pool.Allocate();
	}
	object = pool.Allocate();
	EXPECT_EQ(object, nullptr);
}

TEST(PoolAllocatorTest, AllowReallocate)
{
	Root::PoolAllocator<PoolType, PoolSize> pool;
	PoolType* objects[PoolSize];
	
	// Use full pool and release.
	for (int i = 0; i < PoolSize; ++i)
	{
		objects[i] = pool.Allocate();
	}
	for (int i = 0; i < PoolSize; ++i)
	{
		pool.Free(objects[i]);
	}

	// Make sure all were freed.
	for (int i = 0; i < PoolSize; ++i)
	{
		PoolType *object = pool.Allocate();
		ASSERT_NE(object, nullptr);
	}
}
