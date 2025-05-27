#ifndef ALK_VIDEOINTERFACE_H
#define ALK_VIDEOINTERFACE_H

namespace alk {

	class iVideo
	{
	public:
		 iVideo() {};
		virtual ~iVideo() {};
		virtual bool Init(int alHeight, int alWidth, bool abIsFullScreen) = 0;


	};

}
#endif
