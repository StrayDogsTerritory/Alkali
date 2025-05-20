#ifndef ALK_VIDEOINTERFACE_H
#define ALK_VIDEOINTERFACE_H

class iVideo
{
public:
	virtual ~iVideo() {};
	virtual bool Init(int alHeight, int alWidth, bool abIsFullScreen = false) = 0;


};


#endif
