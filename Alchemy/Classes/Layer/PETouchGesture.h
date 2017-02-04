//
//  PETouchGesture.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 4..
//
//

#ifndef __Alchemy__PETouchGesture__
#define __Alchemy__PETouchGesture__

#include "Common.h"
USING_NS_CC;

typedef enum
{
	TOUCH_GESTURE_START = 0,
	TOUCH_GESTURE_END
}PETouchGestureTime;

class PETouchGesture
{
public:
	PETouchGesture();
	~PETouchGesture();
	bool gestureDetector(Touch* pTouch, int event);
	virtual void onDoubleTap(Vec2 pos);
	
	enum
	{
		PE_TOUCH_DOWN=0,
		PE_TOUCH_MOVE,
		PE_TOUCH_UP,
	};
};

USING_NS_CC_EXT;
#endif /* defined(__Alchemy__PETouchGesture__) */
