#pragma once

#include "root/types.h"
#include "root/utilities.h"
#include <memory>

namespace Root
{
	// Allocator for temporary memory with very localized usage (e.g. temporary buffer to complete a calculation).
	// Allocates sequentially in the buffer, assuming that by the time it has wrapped around, that memory is no longer
	// in use.
	template<Size BufferSize>
	class RingAllocator
	{
	public:
		RingAllocator() : cursor(buffer)
		{
		}

		// Allocate memory for an object type.
		// Will only return nullptr if allocating more than the buffer size.
		template<class Type, class... Parameters>
		Type* Allocate(Parameters&&... parameters)
		{
			// For simplicity's sake, verify using worst-case align offset.
			const UPointer TypeAlignment = std::alignment_of<Type>();
			const UPointer Misalignment = reinterpret_cast<UPointer>(cursor) % TypeAlignment;
			const UPointer RequiredOffset = (TypeAlignment - Misalignment) % TypeAlignment;
			const Size TotalAllocation = static_cast<Size>(sizeof(Type) + RequiredOffset);
			if (TotalAllocation > BufferSize) {
				return nullptr;
			}

			// Reset if we can't fit.
			const Size Available = BufferSize - (cursor - buffer);
			if (TotalAllocation > Available) {
				cursor = buffer;
			}

			// Align to the allocated object type.
			cursor += RequiredOffset;
			Type* result = reinterpret_cast<Type*>(cursor);
			new (result) Type(std::forward<Parameters>(parameters)...);
			cursor += sizeof(Type);
			return result;
		}

		// Allocate an array of objects for a type.
		// Returns nullptr only if allocating more than the buffer size.
		// Objects are constructed with default constructor.
		template<class Type, class... Parameter>
		Type* AllocateArray(Size count)
		{
			// For simplicity's sake, verify using worst-case align offset.
			const Size TypeAlignment = std::alignment_of<Type>();
			Size requiredMaximum = (sizeof(Type) * count) + (alignof(Type) - 1);
			if (requiredMaximum > BufferSize) {
				return nullptr;
			}

			// Reset if we can't fit.
			Size available = BufferSize - (cursor - buffer);
			if (requiredMaximum > available) {
				cursor = buffer;
			}

			// Align to the allocated object type.
			Size relative = cursor - buffer;
			const Size offset = (TypeAlignment - (relative % TypeAlignment)) % TypeAlignment;
			cursor = cursor + offset;

			Type* result = reinterpret_cast<Type*>(cursor);
			new (result) Type[count];
			cursor += sizeof(Type);
			return result;
		}

		// Free a single allocated object.
		template<class Type>
		Inline void Free(Type* object)
		{
			object->~Type();
		}

		// Free an allocated array of objects.
		// Array can be nullptr.
		template<class Type>
		Inline void FreeArray(Type* objects, Size size)
		{
			for (Size i = 0; i < Size; ++i) {
				objects[i].~Type();
			}
		}
		
	private:
		U8* cursor;
		U8 buffer[BufferSize];
	};
}