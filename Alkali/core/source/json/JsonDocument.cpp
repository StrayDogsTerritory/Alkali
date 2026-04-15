#include "json/JsonDocument.h"

#include "system/MemoryManager.h"
#include "system/Platform.h"
#include "system/String.h"

#include "engine/LogWriter.h"

#include "json/cJson/cJSON.h"

namespace alk {

	//-----------------------------------------------------------------

	cJsonObject::~cJsonObject()
	{
		DeleteAll(mLstChildren); // delete all the children when we're being deleted (this is also called for each child)
	}

	//-----------------------------------------------------------------

	cJsonObject* cJsonObject::GetChildObject(const tString& asName)
	{
		std::list<cJsonObject*>::iterator it = mLstChildren.begin(); // get child list iterator
		for (; it != mLstChildren.end(); ++it) // loop through child list
		{
			cJsonObject* pObject = (*it); // points to the object at the value of the iterator
			cJsonObject* pChild = NULL; // allocate for sub child

			if (pObject->msName == asName) // check if its a sibling
				return pObject; // if it is, return it

			// if not found, search the children recursively
			pChild = pObject->GetChildObject(asName); // check each child of current object
			if (pChild != NULL) return pChild; // if it's found, return it
		}

		return NULL; // if no child by the specified name is found, return NULL
	}

	//-----------------------------------------------------------------

	cJsonObject* cJsonObject::CreateChildObject(const tString& asName)
	{
		cJsonObject* pObject = alkNew(cJsonObject, (asName)); // allocated heap memory for a new child
		AddChild(pObject); // add it is a child to current object

		return pObject; // return the created child
	}

	//-----------------------------------------------------------------

	void cJsonObject::DestroyChildObject(const tString& asName)
	{
		if (asName == "") return; // if the name is empty, don't bother deleting anything

		for (std::list<cJsonObject*>::iterator it = mLstChildren.begin(); it != mLstChildren.end(); ++it) // loop through children list
		{
			cJsonObject* pObject = (*it); // points to the object at the value of the iterator
			if (pObject->msName == asName) // if a child with the specifed name is found
			{
				alkDelete(pObject); // delete said child
			}
		}
	}

	//-----------------------------------------------------------------

	void cJsonObject::AddChild(cJsonObject* apObject)
	{
		if (apObject == NULL) return; // if no object is specified, don't add anything

		apObject->mpParent = this; // set the child's parent to current object

		mLstChildren.push_back(apObject); // add to the parents child list
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValue(const tString& asName, const tString asVal)
	{
		tMapValIterator it = mMapValues.find(asName); // finds the value in the map by name
		if (it == mMapValues.end()) return; // if it cannot be found, just return

		it->second = asVal; // set the value in the map to our specified value 
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValueString(const tString& asName, const tString& asValue, const tString& asFallBack)
	{
		SetValue(asName, asValue); // call to setValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValueInt(const tString& asName, int alX, const tString& asFallBack)
	{
		SetValue(asName,cString::ToStringInt(alX, asFallBack));// call to setValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValueFloat(const tString& asName, float afX, const tString& asFallBack)
	{
		SetValue(asName, cString::ToStringFloat(afX, asFallBack));// call to setValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValueBool(const tString& asName, bool abX, const tString& asFallBack)
	{
		SetValue(asName, cString::ToStringBool(abX, asFallBack));// call to setValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValueVector2l(const tString& asName, tVector2l avVec, const tString& asFallback)
	{
		SetValue(asName, cString::ToStringVector2l(avVec, asFallback));// call to setValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValueVector2f(const tString& asName, tVector2f avVec, const tString& asFallback)
	{
		SetValue(asName, cString::ToStringVector2f(avVec, asFallback));// call to setValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValueVector3l(const tString& asName, tVector3l avVec, const tString& asFallback)
	{
		SetValue(asName, cString::ToStringVector3l(avVec, asFallback));// call to setValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	void cJsonObject::SetValueVector3f(const tString& asName, tVector3f avVec, const tString& asFallback)
	{
		SetValue(asName, cString::ToStringVector3f(avVec, asFallback));// call to setValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	tString cJsonObject::GetValue(const tString& asName)
	{
		tMapValIterator it = mMapValues.find(asName); // finds the value in the map by name
		if (it == mMapValues.end()) return "";// if it cannot be found, just return

		return it->second;// return the retrieved value
	}

	//-----------------------------------------------------------------

	tString cJsonObject::GetValueString(const tString& asName, const char* asFallback)
	{
		return cString::toString(GetValue(asName).c_str(), asFallback); // call to GetValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	int cJsonObject::GetValueInt(const tString& asName, int alFallback)
	{
		return cString::ToInt(GetValue(asName).c_str(), alFallback);// call to GetValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	float cJsonObject::GetValueFloat(const tString& asName, float afFallback)
	{
		return cString::ToFloat(GetValue(asName).c_str(), afFallback);// call to GetValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	bool cJsonObject::GetValueBool(const tString& asName, bool abFallback)
	{
		return cString::ToBool(GetValue(asName).c_str(), abFallback);// call to GetValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	tVector2l cJsonObject::GetValueVector2l(const tString& asName, tVector2l avFallback)
	{
		return cString::ToVector2l(GetValue(asName).c_str(), avFallback);// call to GetValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	tVector2f cJsonObject::GetValueVector2f(const tString& asName, tVector2f avFallback)
	{
		return cString::ToVector2f(GetValue(asName).c_str(), avFallback);// call to GetValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	tVector3l cJsonObject::GetValueVector3l(const tString& asName, tVector3l avFallback)
	{
		return cString::ToVector3l(GetValue(asName).c_str(), avFallback);// call to GetValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	tVector3f cJsonObject::GetValueVector3f(const tString& asName, tVector3f avFallback)
	{
		return cString::ToVector3f(GetValue(asName).c_str(), avFallback);// call to GetValue with our possibly converted value
	}

	//-----------------------------------------------------------------

	iJsonDocument::iJsonDocument(const tString& asName)
		: cJsonObject(asName)
	{
		//does nothing
	}

	//-----------------------------------------------------------------

	iJsonDocument::~iJsonDocument() 
	{
		// does nothing
	}

	//-----------------------------------------------------------------

	bool  iJsonDocument::LoadDocument(const twString& asFile)
	{
		FILE* pFile = cPlatform::OpenFile(asFile, L"rb"); // opens the named file on disk, in read binary format 

		if (pFile == NULL) // if it can't be found...
		{
			Error("File '%s' could not be opened!\n", cString::To8BitChar(asFile)); // tell user it can't be found
			return false;
		} 
		///////////////
		// read file in as a C string
		fseek(pFile, 0, SEEK_END); // tell the file pointer to find the last byte of the file
		size_t lSize = ftell(pFile); // report back the size it traversed, in bytes
		rewind(pFile); // bring the file pointer back to the start of file

		char* pBuffer = (char*)alkMalloc(sizeof(char) * lSize +1); // allocate heap memory (the old fashioned way) for the text of the file, + 1 because it is a string,and must have the final byte be \0
		fread(pBuffer, sizeof(char), lSize, pFile); //reads the string of the file into the heap buffer 
		pBuffer[lSize] = 0; // null-terminate the string so that it is a properly formatted string
		fclose(pFile); //release the handle on the file, operating system takes control of it from here
		// parse the document
		bool bRet = Parse(pBuffer); // call the implementation-specific funtion here
		alkFree(pBuffer); // free the buffer's memory

		if (bRet == false) // if it fails to load
		{
			Error("Json document '%s' could not be loaded!\n", msName.c_str()); // let the user know it failed to load
			return false;
		}

		return true;
	}
	
	//-----------------------------------------------------------------

	bool iJsonDocument::SaveDocument(const twString& asFilePath)
	{
		FILE* pFile = cPlatform::OpenFile(asFilePath, L"w"); // opens the named file in write mode

		if (pFile == NULL) // if we can't open it for whatever reason
		{
			Error("Could not open file '%s' for saving!\n", cString::To8BitChar(asFilePath).c_str()); //let the user know
			return false;
		}

		char* sFile = Save(); // call implementation-specific saving function

		if (sFile == NULL) // if it can't create the string
		{
			Error("Could not save file '%s'\n", cString::To8BitChar(asFilePath).c_str()); // let the user know it failed to save
			return false;
		}

		fprintf(pFile, "%s", sFile); // copy the saved JSON data into the file

	}
	
	//-----------------------------------------------------------------

}

