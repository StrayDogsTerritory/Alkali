#ifndef ALK_FLAGBITS_H
#define ALK_FLAGBITS_H

// AHHHHHHHHHHHHHHHHHHHHHH this file sucks now
#include <vector>


/*
* @TODO: rename this to something else, since this had a bunch of non-flagging related types in here now... 
* I don't really care, it's my project, but someone's gonna have to deal with my bullshit in the future.
* Sorry whoever that is. In my defence, I really don't know what I'm doing <3
*/

//////////////////////
// flag bits 
#define FLAGBITNONE      0x00000000
#define FLAGBITALL       0xFFFFFFFF

#define FLAGBITZERO      0x00000001
#define FLAGBITONE       0x00000002
#define FLAGBITTWO       0x00000004
#define FLAGBITTHREE     0x00000008
#define FLAGBITFOUR      0x00000010
#define FLAGBITFIVE      0x00000020
#define FLAGBITSIX       0x00000040
#define FLAGBITSEVEN     0x00000080
#define FLAGBITEIGHT     0x00000100
#define FLAGBITNINE      0x00000200
#define FLAGBITTEN       0x00000400
#define FLAGBITELEVEN    0x00000800
#define FLAGBITTWELVE    0x00001000
#define FLAGBITTHIRTEEN  0x00002000
#define FLAGBITFOURTEEN  0x00004000
#define FLAGBITFIFTEEN   0x00008000

///////////////////////////
// the rest of the flagging related things

typedef unsigned int tFlag;


// and non flagging, read the header 

typedef std::vector<int> tIntVec;
typedef std::vector<float> tFloatVec;

#endif
