#include "PEPopupFail.h"
#include "PEPopUpManager.h"
#include "../Sound/PEBackgroundMusic.h"
#include "../Layer/GameLayer.h"
#include "../Main/PEMain.h"

bool PEPopupFail::init()
{
	/*
    if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)) )
    {
        return false;
    }
	 */
	autorelease();
	
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
	
	CCSprite* pauseTitle = CCSprite::create("Layer/lPopUp/lFail.png");
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
														   menu_selector(PEPopupFail::restart) );
    CCMenu* RESTARTbtn = CCMenu::create(RESTARTItem, NULL);
    RESTARTbtn->setPosition(ccp(backSize.width/2, backSize.height/2 - 200.0f));
    popUpBack->addChild(RESTARTbtn);
	
	CCMenuItemImage *EXITItem = CCMenuItemImage::create(
														"Layer/lPopUp/lExitBase.png",
														"Layer/lPopUp/lExitTouch.png",
														this,
														menu_selector(PEPopupFail::exit) );
    CCMenu* EXITbtn = CCMenu::create(EXITItem, NULL);
	Size EXITbtnSize = EXITItem->getContentSize();
    EXITbtn->setPosition(ccp(EXITbtnSize.width/2+50, backSize.height/2 - 200.0f));
    popUpBack->addChild(EXITbtn);
	
	CCSprite* NEXTbtn = CCSprite::create("Layer/lPopUp/lNextFail.png");
	Size NEXTbtnSize = NEXTbtn->getContentSize();
    NEXTbtn->setPosition(ccp(backSize.width - (NEXTbtnSize.width/2+50), backSize.height/2 - 200.0f));
    popUpBack->addChild(NEXTbtn);
	
    return true;
}

void PEPopupFail::restart(CCObject* pSender)
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

void PEPopupFail::exit(CCObject* pSender)
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

void PEPopupFail::resume(CCObject* pSender)
{
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
}


CCSprite* PEPopupFail::makeStageNumber(int num, float *size)
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
