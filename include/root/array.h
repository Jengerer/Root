#pragma once

#include "heap_allocator.h"

namespace Root
{
    // Class for managing a contiguous array of objects.
    template<typename Type, class Allocator = HeapAllocator>
    class Array
    {
    public:
        // Constructor using the default allocator instance for the allocator type.
        Array(): Array(Allocator::GetDefaultAllocator())
        {
        }
        
        Array(Allocator* allocator): buffer(nullptr), allocated(0), used(0), allocator(allocator)
        {
        }

        ~Array()
        {
            allocator->Release(start);
        }

        // Non-const reference accessor to array element.
        Inline Type& operator[](Size index)
        {
            DebugAssert(index < Getsize());
            return buffer[index];
        }

        // Const reference accessor to array element.
        Inline const Type& operator[](Size index) const
        {
            DebugAssert(index < GetSize());
            return start[index];
        }

        // Get mutable pointer to array memory buffer.
        Inline Type* GetBuffer()
        {
            return start;
        }

        // Get immutable pointer to array memory buffer.
        Inline const Type* GetBuffer() const
        {
            return start;
        }

        // Returns the actual size of the buffer (in number of objects).
        Inline Size GetAllocatedSize() const
        {
            return (end - start);
        }

        // Returns the number of valid objects in the array.
        Inline Size GetSize() const
        {
            return (last - start);
        }

        // Buffer resizing and management.
        bool Resize(Size newSize)
        {
        }
        
    private:
        Type* start; // Pointer to first valid array element.
		Type* last; // Pointer to address one element after last valid array element.
		Type* end; // Pointer to address one element after last allocated array element.
        Allocator* allocator;
    };

}
