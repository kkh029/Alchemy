//
//  PEIntroLayer.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 10..
//
//

#include "PEIntroLayer.h"
#include "../Main/PEMain.h"

#if defined(WIN32) || defined(CC_TARGET_OS_MAC)
#define INTRO_START_DELAY		0
#define INTRO_FADE_IN_DELAY		0
#define INTRO_FADE_OUT_DELAY	0
#define INTRO_BUTTON_DELAY		0
#define INTRO_BUTTON_FADE_IN_DELAY 0
#else
#define INTRO_START_DELAY		0.5f
#define INTRO_FADE_IN_DELAY		2.0f
#define INTRO_FADE_OUT_DELAY	1.0f
#define INTRO_BUTTON_DELAY		1.5f
#define INTRO_BUTTON_FADE_IN_DELAY 1.5f
#endif
CCScene* PEIntroLayer::scene(){
	CCScene* pScene = CCScene::create();
	PEIntroLayer* pIntroLayer = PEIntroLayer::create();
	pScene->addChild(pIntroLayer, 0);
	
	return pScene;
}

bool PEIntroLayer::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)) ) 
    {
        return false;
    }

	this->scheduleOnce(schedule_selector(PEIntroLayer::startIntro), INTRO_START_DELAY);
	this->scheduleOnce(schedule_selector(PEIntroLayer::startButton), INTRO_BUTTON_DELAY);
	
	
	return true;
}
void PEIntroLayer::startIntro(float in)
{
	setTouchEnabled(true);
	m_title = CCSprite::create("title.png");
	
	m_title->setPosition(Vec2Zero);
	m_title->setAnchorPoint(ccp(0.0f, 0.0f));
	addChild(m_title);
	
	m_title->setOpacity(0);
    CCFadeTo*  fadeto = CCFadeTo::create(INTRO_FADE_IN_DELAY, 255);
    m_title->runAction(fadeto);
}
void PEIntroLayer::startButton(float in)
{
	Size winSize=CCDirector::sharedDirector()->getWinSize();
	//popUpLayer
	buttonLayer=CCLayerColor::create(ccc4(0,0,0,255), 350,100);
	buttonLayer->setPosition( ccp((winSize.width - buttonLayer->getContentSize().width)/2, winSize.height/4 - buttonLayer->getContentSize().height/2) );
	buttonLayer->setAnchorPoint( ccp(0,0) );
	buttonLayer->setOpacity(0);
    CCFadeTo*  fadeLayer = CCFadeTo::create(INTRO_BUTTON_FADE_IN_DELAY, 255);
    buttonLayer->runAction(fadeLayer);

	CCMenuItemFont* startItem=CCMenuItemFont::create("START", this, menu_selector(PEIntroLayer::introOut) );
	startItem->setColor(ccc3(255,255,255));
	CCMenu* mStartButton=CCMenu::create();
	mStartButton->addChild(startItem);
	mStartButton->setPosition( ccp(winSize.width/2, winSize.height/4)  );
	mStartButton->setAnchorPoint( ccp(0.5f,0.5f) );
	mStartButton->setOpacity(0);
    CCFadeTo*  fadeButton = CCFadeTo::create(INTRO_BUTTON_FADE_IN_DELAY, 255);
    mStartButton->runAction(fadeButton);

	this->addChild(buttonLayer,1);
	this->addChild(mStartButton,2);
}

void PEIntroLayer::introOut(CCObject* in)
{
	//CCScene *nextScene = GameLayer::scene();
	CCScene *nextScene = PEMain::scene();
	if(nextScene != NULL)
	{
		CCTransitionScene* pTran = CCTransitionFade::create(INTRO_FADE_OUT_DELAY, nextScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}
}
