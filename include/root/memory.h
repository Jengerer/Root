#pragma once

#include "root/export.h"
#include "root/types.h"
#include "root/utilities.h"

namespace Root
{

	// Class containing memory manipulating utilities.
	class Memory
	{
	public:
		static RootLibrary void Zero(void* buffer, Size size);
		static RootLibrary void Copy(const void* source, void* destination, Size size);

		// Type-specific zero memory function.
		template<typename Type>
		Inline static void Zero(Type* object)
		{
			Zero(object, sizeof(Type));
		}

		// Returns the size of a C-style array.
		template<typename Type, Size length>
		Inline static Size ArraySize(Type (&)[length])
		{
			return length;
		}
	};

}