#ifndef ALK_VIDEO_H
#define ALK_VIDEO_H

namespace alk {

	class cVideoSDL;
	class iVideo;

	class cVideo
	{
	public:
		cVideo(iVideo* apVideo);
		~cVideo();
		bool Init(int alHeight, int alWidth, int alWindowMode);

	private:
		iVideo* mpiVideo;
	};

}

#endif