#ifndef ALK_JSONDOCUMENT_H
#define ALK_JSONDOCUMENT_H

#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

#include <list>

namespace alk {


	class iJsonDocument
	{
	public:
		iJsonDocument();
		~iJsonDocument();

		void LoadDocument(const twString& asFilePath);
		void SaveDocument(const twString& asFilePath);

		void SetValue(const tString& asName, const tString& asValue, bool abConvertToNonStringFormat = false);

		tString GetValueString(const tString& asName, int alIdx = 0);
		int GetValueInt(const tString& asName, size_t alIdx = 0);
		float GetValueFloat(const tString& asName, size_t alIdx = 0);
		tVector2l GetValueVector2l(const tString& asName, size_t alIdx = 0);
		tVector2f GetValueVector2f(const tString& asName, size_t alIdx = 0);
		tVector3l GetValueVector3l(const tString& asName, size_t alIdx = 0);
		tVector3f GetValueVector3f(const tString& asName, size_t alIdx = 0);
		tMatrixf GetValueMatrixf(const tString& asName, size_t alIdx = 0);
		cQuaternion GetValueQuaternion(const tString& asName, size_t alIdx = 0);

		virtual void Parse(char* apString)=0;

	protected:
		std::map<tString, tString> mMapValues;
	};

}
#endif // JSONDOCUMENT_H
