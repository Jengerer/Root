#include "root/types.h"
#include "root/memory.h"

namespace Root
{
	// Assign all zeroes to a given memory block.
	void Memory::Zero(void *buffer, size_t size)
	{
		U8* bufferEnd = reinterpret_cast<U8*>(buffer) + size;

		// Write in native integers.
		size_t natives = size / sizeof(UNative);
		UNative* bufferNatives = reinterpret_cast<UNative*>(buffer);
		while (natives--) {
			*bufferNatives++ = 0;
		}

		// Write the rest in bytes.
		U8* bufferRaw = reinterpret_cast<U8*>(bufferNatives);
		while (bufferRaw != bufferEnd) {
			*bufferRaw++ = 0;
		}
	}

	// Copy memory data from one location to another in bytes.
	void Memory::Copy(const void* from, void *to, size_t size)
	{
		const U8* fromEnd = reinterpret_cast<const U8*>(from) + size;

		// Write in native integers.
		size_t natives = size / sizeof(UNative);
		const UNative* fromNatives = reinterpret_cast<const UNative*>(from);
		UNative* toNatives = reinterpret_cast<UNative*>(to);
		while (natives--) {
			*toNatives++ = *fromNatives++;
		}

		// Write the rest in bytes.
		const U8* fromRaw = reinterpret_cast<const U8*>(fromNatives);
		U8* toRaw = reinterpret_cast<U8*>(toNatives);
		while (fromRaw != fromEnd) {
			*toRaw++ = *fromRaw++;
		}
	}
}