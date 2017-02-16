//
//  PEIcon.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 11..
//
//

#include "PEIcon.h"
#include "GameLayer.h"
#include "../PopUp/PEPopUpManager.h"
#include "../Sound/PEBackgroundMusic.h"
#include "../Sound/PESoundEffect.h"

#define STAGE_POS_X 10.f
#define STAGE_POS_Y 1910.f

#define POS_TITLE_OFFSET_X 10.0f
#define POS_TITLE_OFFSET_Y 5.0f

#define POINT_TO_PERCENT(x,y) ((x)*100.0f/(y))

enum MixPanel_Zorder
{
	ZORDER_PANEL = 0,
	ZORDER_UI,
	ZORDER_LOW_ICON,
	ZORDER_HIGH_ICON = 10,
};

bool PEIcon::init(int stage)
{
    if ( !Layer::init() )
    {
        return false;
    }

	autorelease();
	m_stage = stage;
	/* pause button init */
	char text_buf[50];
    CCMenuItemImage *pauseItem = CCMenuItemImage::create(
		"Layer/lUpUi/lPauseOn.png",
		"Layer/lUpUi/lPauseOff.png",
		this,
		menu_selector(PEIcon::pauseCall) );
    pauseBtn = CCMenu::create(pauseItem, NULL);
	pauseBtn->setAnchorPoint(Vec2(1.0f, 1.0f));
    pauseBtn->setPosition(Vec2(POSITION_ICON_PAUSE_X, POSITION_ICON_PAUSE_Y));
    addChild(pauseBtn);
	
	/* stage UI */
	Sprite* stage_frame = Sprite::create("Layer/lUpUi/lFrame.png");
	this->addChild(stage_frame, 1);
	stage_frame->setAnchorPoint(Vec2(0.0f, 1.0f));
	stage_frame->setPosition(Vec2(STAGE_POS_X, STAGE_POS_Y));

	Size stage_frame_size = stage_frame->getContentSize();
	sprintf(text_buf, "Stage %d-%d", m_stage, 1);
	CCLabelTTF* stage_num =  CCLabelTTF::create(text_buf, "fonts/HYGothic-Extra.ttf", 40);
	stage_num->setColor(ccc3(153, 179, 179));
	stage_num->setAnchorPoint(Vec2(0.5f, 0.5f));
	stage_num->setPosition(Vec2(STAGE_POS_X+stage_frame_size.width/2, STAGE_POS_Y-stage_frame_size.height/2));
	this->addChild(stage_num, 1);

    touch_enable = true;

    return true;
}

void PEIcon::onExit()
{
}


void PEIcon::pauseCall(Ref* pSender)
{
    PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_BUTTON_1);
    
	// send notification - popup 
	char buf[5];
	sprintf(buf, "%d", POPUP_STOP);
	__String* popParam=__String::create(buf);
	__NotificationCenter::getInstance()->postNotification("scene_popup", popParam); 
}

void PEIcon::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void PEIcon::m_setTouchEnabled(bool enabled)
{
	touch_enable = enabled;
	pauseBtn->setTouchEnabled(enabled);
	setTouchEnabled(enabled);
}
