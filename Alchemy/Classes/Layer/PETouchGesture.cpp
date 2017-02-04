//
//  PETouchGesture.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 4..
//
//

#include "PETouchGesture.h"
PETouchGesture::PETouchGesture()
{}

PETouchGesture::~PETouchGesture()
{}

bool PETouchGesture::gestureDetector(CCTouch* pTouch, int event)
{
    bool ret = false;
    static int gesture_state = 0;
    static Vec2 pos[2];
    static cc_timeval event_time[2];
    switch (gesture_state) {
        case 0:
			if(event == PE_TOUCH_UP)
            {
				pos[0] = pTouch->getLocation();
				CCTime::gettimeofdayCocos2d(&event_time[TOUCH_GESTURE_START], NULL);
				if(event == PE_TOUCH_UP)
					gesture_state = 1;
			}
			break;
		case 1:
			CCTime::gettimeofdayCocos2d(&event_time[TOUCH_GESTURE_END], NULL);
			switch (event) {
				case PE_TOUCH_DOWN:
				{
					pos[1] = pTouch->getLocation();
					double diffTime = CCTime::timersubCocos2d(
															  &event_time[TOUCH_GESTURE_START],
															  &event_time[TOUCH_GESTURE_END] );
					float diffX = (pos[1].x - pos[0].x > 0)?(pos[1].x - pos[0].x):(pos[0].x - pos[1].x);
					float diffY = (pos[1].y - pos[0].y > 0)?(pos[1].y - pos[0].y):(pos[0].y - pos[1].y);
					if(diffTime>300 || diffX>50 || diffY>50)
						gesture_state = 0;
					break;
				}
				case PE_TOUCH_UP:
				{
					pos[1] = pTouch->getLocation();
					double diffTime = CCTime::timersubCocos2d(
															  &event_time[TOUCH_GESTURE_START],
															  &event_time[TOUCH_GESTURE_END] );
					float diffX = (pos[1].x - pos[0].x > 0)?(pos[1].x - pos[0].x):(pos[0].x - pos[1].x);
					float diffY = (pos[1].y - pos[0].y > 0)?(pos[1].y - pos[0].y):(pos[0].y - pos[1].y);
					if(diffTime<300 && diffX<50 && diffY<50)
					{
						onDoubleTap(pos[1]);
						ret = true;
					}
					gesture_state = 0;
					
				}
					break;
				default:
					break;

			}
		
            
        default:
            break;
    }
    
    return ret;
}

void PETouchGesture::onDoubleTap(Vec2 pos){
}
