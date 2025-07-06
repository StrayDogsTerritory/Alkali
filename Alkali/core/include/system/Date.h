#ifndef ALK_DATE_H
#define ALK_DATE_H

#include "system/String.h"

namespace alk {

	class cDate
	{
	public:
		int Seconds;
		int Minutes;
		int Hours;
		int Day;
		int weeks;
		int Month;
		int Year;

		cDate() : Seconds(0),
			Minutes(0),
			Hours(0),
			Day(0),
			weeks(0),
			Month(0),
			Year(0)
		{
		}

		 tString PrintDate()
		{
			char buffer[256];
			
			sprintf(buffer, "%d/%d/%d %d:%02d:%02d", Hours, Minutes, Seconds, Day, Month, Year);

			return buffer;
		}
	};

}
#endif
