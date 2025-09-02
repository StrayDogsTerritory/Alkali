#include "graphics/Colour.h"

namespace alk 
	{
	cColour::cColour() 
	{ 
		r = 0.0f; 
		g = 0.0f; 
		b = 0.0f; 
		a = 1.0f;
	}

	cColour::cColour(float ar, float ag, float ab, float aa) 
	{ 
		r = ar; g = ag; b = ab; a = aa; 
	}

	cColour::cColour(const cColour& acCol) 
	{ 
		r = acCol.r; g = acCol.g; b = acCol.b; a = acCol.a; 
	}

	cColour::cColour(float afX) 
	{ 
		r = afX; g = afX; b = afX; a = afX; 
	}

	cColour::cColour(float afX, float aa) 
	{ 
		r = afX; g = afX; b = afX; a = aa; 
	}



	cColour cColour::operator==(const cColour& acCol) const
	{
		if (r == acCol.r && g == acCol.g && b == acCol.b && a == acCol.a)
			return true;
		else
			return false;
	}
}