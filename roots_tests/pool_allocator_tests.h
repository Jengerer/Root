#pragma once

class PoolAllocatorTests
{
public:
	bool RunTests();

private:
	// Tests allocating beyond pool capacity.
	bool TestOverflow();
};