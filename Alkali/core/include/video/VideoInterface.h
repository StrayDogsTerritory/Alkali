#ifndef ALK_VIDEOINTERFACE_H
#define ALK_VIDEOINTERFACE_H

namespace alk {

	class iVideo
	{
	public:
		virtual ~iVideo() {};
		virtual bool Init(int alHeight, int alWidth, int alWindowMode) = 0;
		

	
		
	};

}
#endif
