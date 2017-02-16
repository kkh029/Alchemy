#include "PEPopupFail.h"
#include "PEPopUpManager.h"
#include "../Sound/PEBackgroundMusic.h"
#include "../Layer/GameLayer.h"
#include "../Main/PEMain.h"

bool PEPopupFail::init()
{
	/*
    if ( !LayerColor::initWithColor(ccc4(0, 0, 0, 0)) )
    {
        return false;
    }
	 */
	autorelease();
	
	Size winSize = Director::getInstance()->getWinSize();
	
	//backLayer
	LayerColor* backLayer=LayerColor::create(ccc4(0,0,0,150), winSize.width, winSize.height);
	backLayer->setAnchorPoint(Vec2(0,0));
	backLayer->setPosition(Vec2(0,0));
	this->addChild(backLayer);
	
	//popUpLayer
	popUpBack = Sprite::create("Layer/lPopUp/lPopUpBack.png");
	popUpBack->setPosition( Vec2((winSize.width/2), (winSize.height/2)+100) );
	this->addChild(popUpBack);
	backSize = popUpBack->getContentSize();
	
	Sprite* pauseTitle = Sprite::create("Layer/lPopUp/lFail.png");
	pauseTitle->setPosition( Vec2((backSize.width/2), (backSize.height/2 + 300)) );
	popUpBack->addChild(pauseTitle);
	
	float size_x;
	Sprite* stageTitle = makeStageNumber( GameLayer::getStageNum(), &size_x);
	stageTitle->setPosition( Vec2((backSize.width/2 - size_x/2), (backSize.height/2 + 170)) );
	popUpBack->addChild(stageTitle);
	
	CCMenuItemImage *RESTARTItem = CCMenuItemImage::create(
														   "Layer/lPopUp/lRestartBase.png",
														   "Layer/lPopUp/lRestartTouch.png",
														   this,
														   menu_selector(PEPopupFail::restart) );
    CCMenu* RESTARTbtn = CCMenu::create(RESTARTItem, NULL);
    RESTARTbtn->setPosition(Vec2(backSize.width/2, backSize.height/2 - 200.0f));
    popUpBack->addChild(RESTARTbtn);
	
	CCMenuItemImage *EXITItem = CCMenuItemImage::create(
														"Layer/lPopUp/lExitBase.png",
														"Layer/lPopUp/lExitTouch.png",
														this,
														menu_selector(PEPopupFail::exit) );
    CCMenu* EXITbtn = CCMenu::create(EXITItem, NULL);
	Size EXITbtnSize = EXITItem->getContentSize();
    EXITbtn->setPosition(Vec2(EXITbtnSize.width/2+50, backSize.height/2 - 200.0f));
    popUpBack->addChild(EXITbtn);
	
	Sprite* NEXTbtn = Sprite::create("Layer/lPopUp/lNextFail.png");
	Size NEXTbtnSize = NEXTbtn->getContentSize();
    NEXTbtn->setPosition(Vec2(backSize.width - (NEXTbtnSize.width/2+50), backSize.height/2 - 200.0f));
    popUpBack->addChild(NEXTbtn);
	
    return true;
}

void PEPopupFail::restart(Ref* pSender)
{
	
	PEBackgroundMusic::sharedPEBackgroundMusic()->PE_stop();
	Scene *nextScene = GameLayer::scene(GameLayer::getStageNum());
	if(nextScene != NULL)
	{
		CCTransitionScene* pTran = CCTransitionFade::create(2.0f, nextScene);
		Director::getInstance()->replaceScene(pTran);
	}
	
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	__String* popParam=__String::create(buf);
	__NotificationCenter::getInstance()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
	
}

void PEPopupFail::exit(Ref* pSender)
{
	Scene *nextScene = PEMain::scene();
	if(nextScene != NULL)
	{
		CCTransitionScene* pTran = CCTransitionFade::create(5.0f, nextScene);
		Director::getInstance()->replaceScene(pTran);
	}
	
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	__String* popParam=__String::create(buf);
	__NotificationCenter::getInstance()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
}

void PEPopupFail::resume(Ref* pSender)
{
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	__String* popParam=__String::create(buf);
	__NotificationCenter::getInstance()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
}


Sprite* PEPopupFail::makeStageNumber(int num, float *size)
{
    Sprite *stageLabel = Sprite::create();
    int i, index;
	//float offset = 0.0f;
    Sprite *spr;
	char file_path[40];
	
	*size = 0.0;
    stageLabel->setAnchorPoint( Vec2( 0, 0 ) );
	
	Sprite *stage =  Sprite::create("Layer/lPopUp/lStage.png");
	stage->setAnchorPoint( Vec2( 0, 0 ) );
    stage->setPosition( Vec2(*size, -5.0f) );
	stageLabel->addChild( stage );
	*size += (stage->getContentSize().width + 20.0f);
	
    /* cur gauge */
    __Array *num_array = __Array::create();
    if( num > 0 )
	{
        while( num != 0 )
		{
            num_array->addObject( __Integer::create( num%10 ) );
            num /= 10;
		}
	}
    else
        num_array->addObject( __Integer::create( 0 ) );
	
    
    for( i=num_array->count()-1; i>=0; i-- )
	{
        index = ( dynamic_cast<__Integer*>( num_array->objectAtIndex(i) ) )->getValue();
		sprintf(file_path, "Layer/lPopUp/lPopUpNum%d.png", index);
		
        spr = Sprite::create(file_path);
        spr->setAnchorPoint( Vec2( 0, 0 ) );
        spr->setPositionX( *size );
		
        stageLabel->addChild( spr );
		*size += spr->getContentSize().width;
	}
	
    return stageLabel;
}
