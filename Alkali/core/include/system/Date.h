#ifndef ALK_DATE_H
#define ALK_DATE_H


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

		tString ToString() const
		{
			char sBuff[256];
			sprintf(sBuff, "%d/%d/%d %d:%02d:%02d", Day, Month, Year, Hours, Minutes, Seconds);
			return sBuff;
		}

		tString ToStringTime() const
		{
			char sBuff[256];
			sprintf(sBuff, "%d:%02d:%02d", Hours, Minutes, Seconds);
			return sBuff;
		}

		tString ToStringDate() const
		{
			char sBuff[256];
			sprintf(sBuff, "%d/%d/%d", Day, Month, Year);
			return sBuff;
		}
	};

}
#endif
