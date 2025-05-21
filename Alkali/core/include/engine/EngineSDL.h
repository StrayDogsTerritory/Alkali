#ifndef ALK_ENGINESDL_H
#define ALK_ENGINESDL_H


namespace alk {

	class cVideoSDL;


	class cSDLEngine
	{
	public:
		cSDLEngine();
		~cSDLEngine();

		cVideoSDL* CreateVideo();

	private:

		cVideoSDL* mpVideoSDL;

	};

}
#endif