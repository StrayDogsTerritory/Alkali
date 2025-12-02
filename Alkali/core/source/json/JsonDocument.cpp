#include "json/JsonDocument.h"

#include "system/MemoryManager.h"
#include "system/String.h"
#include "system/Platform.h"

#include "engine/LogWriter.h"

#include "json/simdjson/picojson.h"

namespace alk {

	iJsonDocument::iJsonDocument() 
	{
	}

	iJsonDocument::~iJsonDocument()
	{
	}

	void iJsonDocument::Parse(const twString& asPath)
	{
		tString sJson = "[ \"Hello World!\" ]";
		picojson::value Val;
		tString sOut = picojson::parse(Val, sJson);

		if (!Val.is<picojson::object>())
		{
			Error("Json Document '%s' is not valid!\n", cString::To8BitChar(asPath).c_str());
			
			const picojson::value::array& arr = Val.get<picojson::array>();
			for (picojson::value::array::const_iterator i = arr.begin(); i != arr.end(); ++i)
			{
				Log("%s\n",i->to_str().c_str());
			}

			return;
		}

		const picojson::value::object& obj = Val.get<picojson::object>();
		for (picojson::value::object::const_iterator i = obj.begin(); i != obj.end(); ++i)
		{
			Log("%s : %s\n", i->first, i->second.to_str());
		}

		//Log("%s\n", sOut.c_str());
	}
}

