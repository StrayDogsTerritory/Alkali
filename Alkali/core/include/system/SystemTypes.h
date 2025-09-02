#ifndef ALK_SYSTEMTYPES_H
#define ALK_SYSTEMTYPES_H



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
}
#endif //ALK_SYSTEMTYPES_H
