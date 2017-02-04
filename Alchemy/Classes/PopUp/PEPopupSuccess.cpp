#include "PEPopupSuccess.h"
#include "PEPopUpManager.h"
#include "../Sound/PEBackgroundMusic.h"
#include "../Layer/GameLayer.h"
#include "../Main/PEMain.h"

PEPopupSuccess::PEPopupSuccess(int doors)
{
	door_num = doors;
}

PEPopupSuccess::~PEPopupSuccess()
{
}

bool PEPopupSuccess::init()
{
	/*
    if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)) )
    {
        return false;
    }
	 */
	autorelease();
	scheduleUpdate();
	
	CCLog("door remain : %d", door_num);
	
	Size winSize = CCDirector::sharedDirector()->getWinSize();
	
	//backLayer
	CCLayerColor* backLayer=CCLayerColor::create(ccc4(0,0,0,150), winSize.width, winSize.height);
	backLayer->setAnchorPoint(ccp(0,0));
	backLayer->setPosition(ccp(0,0));
	this->addChild(backLayer);
	
	//popUpLayer
	popUpBack = CCSprite::create("Layer/lPopUp/lPopUpBack.png");
	popUpBack->setPosition( ccp((winSize.width/2), (winSize.height/2)+100) );
	this->addChild(popUpBack);
	backSize = popUpBack->getContentSize();
	
	CCSprite* pauseTitle = CCSprite::create("Layer/lPopUp/lClear.png");
	pauseTitle->setPosition( ccp((backSize.width/2), (backSize.height/2 + 300)) );
	popUpBack->addChild(pauseTitle);
	
	float size_x;
	CCSprite* stageTitle = makeStageNumber( GameLayer::getStageNum(), &size_x);
	stageTitle->setPosition( ccp((backSize.width/2 - size_x/2), (backSize.height/2 + 170)) );
	popUpBack->addChild(stageTitle);

	CCMenuItemImage *RESTARTItem = CCMenuItemImage::create(
														   "Layer/lPopUp/lRestartBase.png",
														   "Layer/lPopUp/lRestartTouch.png",
														   this,
														   menu_selector(PEPopupSuccess::restart) );
    CCMenu* RESTARTbtn = CCMenu::create(RESTARTItem, NULL);
    RESTARTbtn->setPosition(ccp(backSize.width/2, backSize.height/2 - 200.0f));
    popUpBack->addChild(RESTARTbtn);
	
	CCMenuItemImage *EXITItem = CCMenuItemImage::create(
														"Layer/lPopUp/lExitBase.png",
														"Layer/lPopUp/lExitTouch.png",
														this,
														menu_selector(PEPopupSuccess::exit) );
    CCMenu* EXITbtn = CCMenu::create(EXITItem, NULL);
	Size EXITbtnSize = EXITItem->getContentSize();
    EXITbtn->setPosition(ccp(EXITbtnSize.width/2+50, backSize.height/2 - 200.0f));
    popUpBack->addChild(EXITbtn);
	
	CCMenuItemImage *NEXTItem = CCMenuItemImage::create(
														  "Layer/lPopUp/lNextBase.png",
														  "Layer/lPopUp/lNextTouch.png",
														  this,
														  menu_selector(PEPopupSuccess::resume) );
    CCMenu* NEXTbtn = CCMenu::create(NEXTItem, NULL);
	Size NEXTbtnSize = NEXTItem->getContentSize();
    NEXTbtn->setPosition(ccp(backSize.width - (NEXTbtnSize.width/2+50), backSize.height/2 - 200.0f));
    popUpBack->addChild(NEXTbtn);
	
    // show stage score - star
    // door life 5   - 3
    // door life 3,4 - 2
    // door life 1,2 - 1
    int score = 1;
    if(door_num > 4)
        score = 3;
    else if(door_num > 2)
        score = 2;
    
	CCArmature* star_0 = CCArmature::create("lStar");
	star_0->setPosition(backSize.width/4, backSize.height/2);
 	star_0->getAnimation()->playWithIndex(1, -1, -1, -0, 0);
	popUpBack->addChild(star_0);
	
	int door1_star_ani = 0;
	if(score > 1)
		door1_star_ani = 1;
		
	CCArmature* star_1 = CCArmature::create("lStar");
	star_1->setPosition(backSize.width/2, backSize.height/2);
	star_1->getAnimation()->playWithIndex(door1_star_ani, -1, -1, 0, 0);
	popUpBack->addChild(star_1);
	
	int door2_star_ani = 0;
	if(score > 2)
		door2_star_ani = 1;
	CCArmature* star_2 = CCArmature::create("lStar");
	star_2->setPosition(backSize.width*3/4 , backSize.height/2);
 	star_2->getAnimation()->playWithIndex(door2_star_ani, -1, -1, 0, 0);
	popUpBack->addChild(star_2);
	
    // check stage score - save stage score
	char buf[15];
    int pre_score;
	sprintf(buf, "stage%d", GameLayer::getStageNum());
    pre_score = CCUserDefault::sharedUserDefault()->getIntegerForKey(buf);
    if(pre_score < score)
    {
        if(door2_star_ani)
            CCUserDefault::sharedUserDefault()->setIntegerForKey(buf, 3);
        else if(door1_star_ani)
            CCUserDefault::sharedUserDefault()->setIntegerForKey(buf, 2);
        else
            CCUserDefault::sharedUserDefault()->setIntegerForKey(buf, 1);
    }
    return true;
}

void PEPopupSuccess::restart(CCObject* pSender)
{
	
	PEBackgroundMusic::sharedPEBackgroundMusic()->PE_stop();
	CCScene *nextScene = GameLayer::scene(GameLayer::getStageNum());
	if(nextScene != NULL)
	{
		CCTransitionScene* pTran = CCTransitionFade::create(2.0f, nextScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}
	
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
	
}

void PEPopupSuccess::exit(CCObject* pSender)
{
	CCScene *nextScene = PEMain::scene();
	if(nextScene != NULL)
	{
		CCTransitionScene* pTran = CCTransitionFade::create(5.0f, nextScene);
		CCDirector::sharedDirector()->replaceScene(pTran);
	}
	
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
}

void PEPopupSuccess::resume(CCObject* pSender)
{
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
}


CCSprite* PEPopupSuccess::makeStageNumber(int num, float *size)
{
    CCSprite *stageLabel = CCSprite::create();
    int i, index;
	//float offset = 0.0f;
    CCSprite *spr;
	char file_path[40];
	
	*size = 0.0;
    stageLabel->setAnchorPoint( ccp( 0, 0 ) );
	
	CCSprite *stage =  CCSprite::create("Layer/lPopUp/lStage.png");
	stage->setAnchorPoint( ccp( 0, 0 ) );
    stage->setPosition( ccp(*size, -5.0f) );
	stageLabel->addChild( stage );
	*size += (stage->getContentSize().width + 20.0f);
	
    /* cur gauge */
    CCArray *num_array = CCArray::create();
    if( num > 0 )
	{
        while( num != 0 )
		{
            num_array->addObject( CCInteger::create( num%10 ) );
            num /= 10;
		}
	}
    else
        num_array->addObject( CCInteger::create( 0 ) );
	
    
    for( i=num_array->count()-1; i>=0; i-- )
	{
        index = ( dynamic_cast<CCInteger*>( num_array->objectAtIndex(i) ) )->getValue();
		sprintf(file_path, "Layer/lPopUp/lPopUpNum%d.png", index);
		
        spr = CCSprite::create(file_path);
        spr->setAnchorPoint( ccp( 0, 0 ) );
        spr->setPositionX( *size );
		
        stageLabel->addChild( spr );
		*size += spr->getContentSize().width;
	}
	
    return stageLabel;
}
