#ifndef ALK_RESOURCEBASE_H
#define ALK_RESOURCEBASE_H

#include "system/String.h"

#include <map>


namespace alk {

	class iResourceBase
	{
	public:
		iResourceBase(const tString& asName, const twString& asFullPath);
		
		virtual ~iResourceBase();

		virtual void Unload()=0;
		virtual bool Reload()=0;
		virtual void Destroy()=0;
		
		bool HasUsers() const { return mlUserCount > 0; }
		unsigned int NumUsers() const { return mlUserCount; }
		void AddUser() { mlUserCount++; }
		void RemoveUser() { if (mlUserCount > 0)mlUserCount--; }
		unsigned long GetID() const { return mlID; }


		tString GetName() { return msName; }
		twString GetPath() { return msPath; }
	protected:
		unsigned long mlID;
		unsigned int mlUserCount;
		tString msName;
		twString msPath;

	};
}

#endif
