#pragma once

namespace Roots
{
	// Templated class for allocating objects from a fixed size buffer.
	// Objects that are allocated may have been used and are not reconstructed.
	template<class Type, size_t Size>
	class PoolAllocator
	{
	private:
		// Union to allow reusing the object space to point to next.
		union PoolElement
		{
			PoolElement* next;
			Type object;
		};

	public:
		PoolAllocator();
		~PoolAllocator() = default;

		// Allocate a single object from the pool.
		// Returns nullptr on failure.
		Type* Allocate();

		// Free an object to be reused by the pool.
		void Free(Type* object);

	private:
		PoolElement pool[Size];
		PoolElement *head;
	};

	template<class Type, size_t Size>
	PoolAllocator<Type, Size>::PoolAllocator()
	{
		// Create linked list of next elements.
		PoolElement** lastPointer = &head;
		for (size_t i = 0; i < Size; ++i)
		{
			PoolElement* current = &pool[i];
			*lastPointer = current;
			lastPointer = &current->next;
		}
		*lastPointer = nullptr;
	}

	template<class Type, size_t Size>
	Type* PoolAllocator<Type, Size>::Allocate()
	{
		PoolElement* allocated = head;
		if (allocated != nullptr) {
			head = allocated->next;
		}
		return &allocated->object;
	}

	template<class Type, size_t Size>
	void PoolAllocator<Type, Size>::Free(Type* object)
	{
		PoolElement* element = reinterpret_cast<PoolElement*>(object);
		element->next = head;
		head = element;
	}
}