#ifndef ALK_JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

#include <list>

namespace alk {

	class cJsonNode
	{
	public:
		cJsonNode(const tString& asName);
		~cJsonNode();

		void AddNode(cJsonNode* apNode);
		void RemoveNode(const tString& asName);
		
		cJsonNode* GetJsonNode(const tString& asName);

		tString GetValueString(const tString& asName, int alIdx = 0);
		int GetValueInt(const tString& asName, size_t alIdx = 0);
		float GetValueFloat(const tString& asName, size_t alIdx = 0);
		tVector2l GetValueVector2l(const tString& asName, size_t alIdx = 0);
		tVector2f GetValueVector2f(const tString& asName, size_t alIdx = 0);
		tVector3l GetValueVector3l(const tString& asName, size_t alIdx = 0);
		tVector3f GetValueVector3f(const tString& asName, size_t alIdx = 0);
		tMatrixf GetValueMatrixf(const tString& asName, size_t alIdx = 0);
		cQuaternion GetValueQuaternion(const tString& asName, size_t alIdx = 0);

	private:
		tString msName;
		tString msValue;

		std::list<cJsonNode*> mLstJsonNode;

	};


	class iJsonDocument
	{
	public:
		iJsonDocument();
		~iJsonDocument();

		void Parse(const twString &asPath);

	private:
		std::list<cJsonNode*> mLstJsonSubNodes;
	};

}
#endif // JSONDOCUMENT_H
