#pragma once

#include <new>

namespace Roots
{
	// Class that manages heap memory.
	class HeapAllocator
	{
	public:
		HeapAllocator() = default;
		~HeapAllocator() = default;

		// Allocate (without constructing) memory for an object type.
		// Returns nullptr on failure.
		template<class Type>
		Type* Allocate();

		// Allocate an array of objects for a type.
		// Returns nullptr on failure.
		// Objects are constructed with default constructor.
		template<class Type>
		Type* AllocateArray(size_t count);

		// Free a single allocated object.
		// Object can be nullptr. If it isn't, it must have been constructed.
		template<class Type>
		void Free(Type* object);

		// Free an allocated array of objects.
		// Array can be nullptr.
		template<class Type>
		void FreeArray(Type* objects);

	public:
		static HeapAllocator instance;
	};

	template<class Type>
	Type* Allocate()
	{
		size_t size = sizeof(Type);
		unsigned char* buffer = new (std::nothrow) unsigned char[size];
		return reinterpret_cast<Type*>(buffer);
	}

	template<class Type>
	Type* AllocateArray(size_t count)
	{
		Type* objects = new (std::nothrow) Type[count];
		return objects;
	}

	template<class Type>
	void Free(Type* object)
	{
		delete object;
	}

	template<class Type>
	void FreeArray(Type* objects)
	{
		delete[] objects;
	}	
}