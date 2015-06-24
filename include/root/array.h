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
            allocator->Release(buffer);
        }

        // Non-const reference accessor to array element.
        Inline Type& operator[](Size index)
        {
            DebugAssert(index < used);
            return buffer[index];
        }

        // Const reference accessor to array element.
        Inline const Type& operator[](Size index) const
        {
            DebugAssert(index < used);
            return buffer[index];
        }

        // Get mutable pointer to array memory buffer.
        Inline Type* GetBuffer()
        {
            return buffer;
        }

        // Get immutable pointer to array memory buffer.
        Inline const Type* GetBuffer() const
        {
            return buffer;
        }

        // Returns the actual size of the buffer (in number of objects).
        Inline Size GetAllocatedSize() const
        {
            return allocated;
        }

        // Returns the number of valid objects in the array.
        Inline Size GetSize() const
        {
            return used;
        }

        // Buffer resizing and management.
        bool Resize(Size newSize)
        {
        }
        
    private:
        Type* buffer;
        Size allocated;
        Size used;
        Allocator* allocator;
    };

    template<typename Type, class Allocator>
    Array<Type, Allocator>::Array(): Array(Allocator::GetDefaultInstance())
    {
    }

    template<typename Type, class Allocator>
    Array<Type, Allocator>::Array(Allocator* allocator):
    buffer(nullptr),
    allocated(0),
    used(0),
    allocator(allocator)
    {
    }
}
