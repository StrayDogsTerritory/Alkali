#ifndef ALK_JSONWRAPPER_H
#define ALK_JSONWRAPPER_H

//===================================
/////////////////////////////////////
//			PURPOSE
// be able to use jsoncpp without needing to include the entire namespace.
// It's light as is, but I don't want to pollute alk and cause any conflicts in the future.
// I don't know how useful this is, but I'll be using it until it's proven obselete.
// 
// ignore this because im not usign jsoncpp anymore. Shit's ass. Use Nlohmann's thing.
/////////////////////////////////////
//===================================

#include "json/json.hpp"
#include "json/picojson.h"
namespace alk {

	typedef nlohmann::json cJson;
	typedef picojson::value cJsonValue;
	
}

#endif // ALK_JSONWRAPPER_H
