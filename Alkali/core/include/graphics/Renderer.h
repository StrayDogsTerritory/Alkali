#ifndef ALK_RENDERER_H
#define ALK_RENDERER_H

namespace alk {

	class iRenderer
	{
	public:
		iRenderer();
		~iRenderer();

		void Render();

		void Update(float afStep);
	};

}

#endif
