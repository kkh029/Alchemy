#ifndef Alchemy_Common
#define Alchemy_Common

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util/PETime.h"
#include "cocostudio/CocoStudio.h"

#if defined(WIN32) 
	#define PRINT_LOG(...) log(__VA_ARGS__)
#elif defined(CC_TARGET_OS_MAC)
	#define PRINT_LOG(...) log(__VA_ARGS__)
#else
	#define PRINT_LOG(...)
#endif

#define UI_FONT "fonts/HYGothic-Extra.ttf"

class Alchemy;

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

#define DESIGN_WIDTH		1080.0f
#define DESIGN_HEIGHT		1920.0f

#define MIX_WIDTH			1080.0f
#define MIX_HEIGHT			441.0f

#define BOARD_WIDTH			164.0f
#define BOARD_HEIGHT		148.0f

#define OBJECT_WIDTH 		128.0f
#define OBJECT_HEIGHT 		128.0f

#define ELEMENT_COUNT		4
#define	ALCHEMY_COUNT		6
#define	ITEM_COUNT			4
#define OBJECT_COUNT		ELEMENT_COUNT + ALCHEMY_COUNT + ITEM_COUNT

#define ICON				1
#define ALCHEMY				2
#define MONSTER				3

#define ROW_NUM			7
#define COL_NUM 		6
#define MAX_ROW_NUM 		10

#define ROW 0
#define COL 1

#define TYPE_COUNT 			4

#define NUM_OF_CACHED_BULLETS	3
#define BULLET_FIRE_COOLTIME	1500

#define NUM_OF_MONSTERS			6
#define MONSTER_SPAWN_COOLTIME	1000

#define TIME_START	0
#define TIME_END 	1

class Common
{
};

inline long time_interval(_STRUCT_TIMEVAL start, _STRUCT_TIMEVAL end)
{
    return (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
}

#endif
