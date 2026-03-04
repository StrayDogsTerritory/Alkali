#ifndef ALK_JSONDOCUMENT_H
#define ALK_JSONDOCUMENT_H

#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

#include <map>

namespace alk {

	typedef std::map<tString, tString> tMapValues;
	typedef tMapValues::iterator tMapValIterator;


	class iJsonDocument
	{
	public:
		iJsonDocument();
		~iJsonDocument();

		bool LoadDocument(const twString& asFilePath);
		void SaveDocument(const twString& asFilePath);

		virtual bool Parse(char* apString) = 0;

		void SetValue(const tString& asName, const tString& asValue, bool abConvertToNonStringFormat = false);

		tString GetValueString(const tString& asName, int alIdx = 0);
		int GetValueInt(const tString& asName, size_t alIdx = 0);
		float GetValueFloat(const tString& asName, size_t alIdx = 0);
		bool GetValueBool(const tString& asName, bool abFallback);
		tVector2l GetValueVector2l(const tString& asName, size_t alIdx = 0);
		tVector2f GetValueVector2f(const tString& asName, size_t alIdx = 0);
		tVector3l GetValueVector3l(const tString& asName, size_t alIdx = 0);
		tVector3f GetValueVector3f(const tString& asName, size_t alIdx = 0);
		tMatrixf GetValueMatrixf(const tString& asName, size_t alIdx = 0);
		cQuaternion GetValueQuaternion(const tString& asName, size_t alIdx = 0);

	protected:
		tMapValues mMapValues;
	};

}
#endif // JSONDOCUMENT_H
