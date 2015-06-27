#pragma once

#include "root/export.h"
#include "root/types.h"
#include "root/utilities.h"
#include <new>
#include <utility>

namespace Root
{
	// Class that manages heap memory.
	class HeapAllocator
	{
	public:
		HeapAllocator() = default;
		~HeapAllocator() = default;

		// Allocate memory for an object type.
		// Returns nullptr on failure.
		template<class Type, class... Parameters>
		Inline Type* Allocate(Parameters&&... parameters)
		{
			Type* object = new (std::nothrow) Type(std::forward<Parameters>(parameters)...);
			return object;
		}

		// Allocate an array of objects for a type.
		// Returns nullptr on failure.
		// Objects are constructed with default constructor.
		template<class Type>
		Inline Type* AllocateArray(Size count)
		{
			Type* objects = new (std::nothrow) Type[count];
			return objects;
		}

		// Free a single allocated object.
		// Object can be nullptr. If it isn't, it must have been constructed.
		template<class Type>
		Inline void Free(Type* object)
		{
			delete object;
		}

		// Free an allocated array of objects.
		// Array can be nullptr.
		template<class Type>
		Inline void FreeArray(Type* objects)
		{
			delete[] objects;
		}

	public:
		static RootLibrary HeapAllocator instance;
	};
}