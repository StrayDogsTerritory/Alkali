#ifndef ALK_SYSTEMTYPES_H
#define ALK_SYSTEMTYPES_H

#include "system/MemoryManager.h"

//----------------------------
namespace alk {

	enum eMessageType
	{
		eTypeNormal,
		eTypeWarning,
		eTypeError,
		eTypeFatalError,
		eTypeDebug
	};

	enum eMessageBoxType
	{
		eBoxTypeMessage,
		eBoxTypeWarning,
		eBoxTypeError,
		eBoxTypeFatalError
	};

	enum eSystemSpecialPath
	{
		eSystemSpecialPath_ePersonalDirectory,
		eSystemSpecialPath_eLocal,
		eSystemSpecialPath_eLast_Enum
	};

	///////////////////
	// defines

	template <class Container, class T>
	void FindAndErase(Container& aContainer, const T* aVal)
	{
		typename Container::iterator it = aContainer.begin();
		for (; it != aContainer.end(); it++)
		{
			if (*it == aVal)
			{
				aContainer.erase(it);
				return;
			}
		}
	}

	template <class Container, class T>
	void FindAndEraseMap(Container& aContainer, const T* aVal)
	{
		typename Container::iterator it = aContainer.begin();
		for (; it != aContainer.end(); it++)
		{

			if (it->second == aVal)
			{
				aContainer.erase(it);
				return;
			}

		}
	}

	template <class Container, class T>
	void FindAndDelete(Container& aContainer, T* aVal)
	{
		typename Container::iterator it = aContainer.begin();
		for (; it != aContainer.end(); it++)
		{

			if (*it == aVal)
			{
				aContainer.erase(it);
				break;
			}

		}
		alkDelete(aVal);
	}

	template <class Container, class T>
	void FindAndDeleteMap(Container& aContainer, T* aVal)
	{
		typename Container::iterator it = aContainer.begin();
		for (; it != aContainer.end(); it++)
		{

			if (it->second == aVal)
			{
				aContainer.erase(it);
				return;
			}

		}
		alkDelete(aVal);
	}

	template <class Container>
	void DeleteAll(Container& aContainer)
	{
		typename Container::iterator it = aContainer.begin();
		for (; it != aContainer.end(); it++)
		{
			alkDelete(*it);
		}
		aContainer.clear();
	}

	template <class Container>
	void DeleteAllMap(Container& aContainer)
	{
		typename Container::iterator it = aContainer.begin();
		for (; it != aContainer.end(); it++)
		{
			alkDelete(it->second);
		}
		aContainer.clear();
	}

	template <class Container, class T>
	bool FindObject(Container& aContainer, T* apObject)
	{
		return aContainer.find(apObject) != aContainer.end();
	}
}
#endif //ALK_SYSTEMTYPES_H
