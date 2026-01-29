#ifndef ALK_WORLD_H
#define ALK_WORLD_H

namespace alk {

	class iNode;

	class cWorld
	{
	public:
		cWorld();
		~cWorld();
	private:
		iNode* mpRoot;
	};
}

#endif
