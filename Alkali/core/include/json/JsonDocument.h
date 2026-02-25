#ifndef ALK_JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include "system/String.h"

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
