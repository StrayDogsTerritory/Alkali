#ifndef ALK_XMLDOCUMENTTINYXML_H
#define ALK_XMLDOCUMENTTINYXML_H

#include "xml/XmlDocument.h"

namespace alk {

	class cXmlDocumentTinyXml : public iXmlDocument
	{
	public:
		cXmlDocumentTinyXml(const tString asName) : iXmlDocument(asName) {}


	private:
		bool LoadFromFile(const twString asPath);
		bool SaveToFile(const twString asPath);

	};

}


#endif //ALK_XMLDOCUMENTTINYXML_H
