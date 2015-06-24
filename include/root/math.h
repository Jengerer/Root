#pragma once

#include <root/export.h>
#include <root/types.h>
#include <root/utilities.h>

namespace Root
{
	// Class with common mathematical functions and constants.
	class Math
	{
	public:
		static const Real Pi;

		// Convert a radian angle to degrees.
		static Inline Real Degrees(Real radians)
		{
			return (radians * (180.f / Pi));
		}

		// Convert a degree angle to radians.
		static Inline Real Radians(Real degrees)
		{
			return (degrees * (Pi / 180.f));
		}

		// Get sine value for a degree angle.
		static RootLibrary Real Sine(Real x);

		// Get cosine value for a degrees angle.
		static RootLibrary Real Cosine(Real x);

		// Get arcsine value in degrees for a value.
		static RootLibrary Real Arcsine(Real x);

		// Get arccos value in degrees for a value.
		static RootLibrary Real Arccosine(Real x);
	};
}