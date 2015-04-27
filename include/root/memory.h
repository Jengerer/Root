#pragma once

#include "root/types.h"
#include "root/utilities.h"

namespace Root
{

	// Class containing memory manipulating utilities.
	class Memory
	{
	public:
		static void Zero(void* buffer, Size size);
		static void Copy(const void* source, void* destination, Size size);

		// Type-specific zero memory function.
		template<typename Type>
		Inline static void Zero(Type* object)
		{
			Zero(object, sizeof(Type));
		}
	};

}