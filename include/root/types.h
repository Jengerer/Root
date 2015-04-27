#pragma once

#include <inttypes.h>

namespace Root
{
	// Sized integral type definitions.
	using I8 = int8_t;
	using U8 = uint8_t;
	using I16 = int16_t;
	using U16 = uint16_t;
	using I32 = int32_t;
	using U32 = uint32_t;
	using I64 = int64_t;
	using U64 = uint64_t;

	// Architecture based type definitions.
#if defined(ARCHITECTURE_X86)
	using INative = I32;
	using UNative = U32;
#else
	using INative = I64;
	using UNative = U64;
#endif

	// Type for storing size content.
	using Size = size_t;

	// Real value types.
	using Real = float;
}