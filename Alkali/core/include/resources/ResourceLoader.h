#ifndef  ALK_RESOURCELOADER_H
#define ALK_RESOURCELOADER_H

#include "system/String.h"

#include <list>
#include <vector>

/*
* Created by Simon Stroomer
* file type loaders, which contain sub loaders to specifically load files 
*/

namespace alk
{
	class cResources;
	class iSubLoader;

	class iResourceLoader
	{
	public:

		//-------------------------------------------------------------------------------------

		iResourceLoader(cResources* apResources); //constructor
		virtual ~iResourceLoader(); //destructor

		//-------------------------------------------------------------------------------------

		void AddSubLoader(iSubLoader* apSubLoader);// add a specific subloader to this loader

		//-------------------------------------------------------------------------------------

		virtual void SetupSubLoader(iSubLoader* apSubLoader)=0; // if any specific setup needs to be done per each sub loader

		//-------------------------------------------------------------------------------------

		//void AddSupportedExtension(const twString& asExtension);
		iSubLoader* GetSubLoaderForFile(const twString& asFile); //get the proprt subloader from the file extension

		//-------------------------------------------------------------------------------------

	protected:
		cResources* mpResources; // pointer to the resource module

		std::vector<iSubLoader*> mvSubLoaders; // array of sub loaders
		std::list<tString> mLstSupportedExtensions; // list of supported extensions
	};

}

#endif
