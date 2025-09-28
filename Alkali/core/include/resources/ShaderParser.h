#ifndef ALK_SHADERPARSER_H
#define ALK_SHADERPARSER_H


namespace alk {

	class cShaderParser
	{
		friend class cPreprocessParser;
	public:
		cShaderParser();
		~cShaderParser();

		bool Parse();
	};

}
#endif