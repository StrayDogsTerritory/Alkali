#ifndef ALK_COLOUR_H
#define ALK_COLOUR_H

// yes, its colour with a 'u'. I'm Canadian. Get over it.

namespace alk {

	class cColour
	{
	public:
		union {
			struct
			{
				float r, g, b, a;
			};
		
			float v[4];
		};

		cColour();
		cColour(float ar, float ag, float ab, float aa);
		cColour(const cColour& acCol);
		cColour(float afX);
		cColour(float afX, float aa);

		cColour operator==(const cColour& acCol) const;
	};

}

#endif

