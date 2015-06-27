#include "root/math.h"
#include <cmath>

namespace Root
{
	const Real Math::Pi = 3.141592653f;

	Real Math::Sine(Real x)
	{
		x = Radians(x);
		return sinf(x);
	}

	Real Math::Cosine(Real x)
	{
		x = Radians(x);
		return cosf(x);
	}

	Real Math::Arcsine(Real x)
	{
		float radians = asinf(x);
		return Degrees(radians);
	}

	Real Math::Arccosine(Real x)
	{
		float radians = acosf(x);
		return Degrees(radians);
	}
}
