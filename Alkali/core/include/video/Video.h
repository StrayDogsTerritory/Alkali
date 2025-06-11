#ifndef ALK_VIDEO_H
#define ALK_VIDEO_H

namespace alk {

	
	class iVideo;

	class cVideo
	{
	public:
		cVideo(iVideo* apVideo);
		~cVideo();
		bool Init(int alHeight, int alWidth, int alWindowMode);

		iVideo* GetVideo();

	private:
		iVideo* mpVideo;
	};

}

#endif