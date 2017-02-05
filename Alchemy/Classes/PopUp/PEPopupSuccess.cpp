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
	
	log("door remain : %d", door_num);
	
	Size winSize = Director::getInstance()->getWinSize();
	
	//backLayer
	LayerColor* backLayer=LayerColor::create(Color4B(0,0,0,150), winSize.width, winSize.height);
	backLayer->setAnchorPoint(Vec2(0,0));
	backLayer->setPosition(Vec2(0,0));
	this->addChild(backLayer);
	
	//popUpLayer
	popUpBack = Sprite::create("Layer/lPopUp/lPopUpBack.png");
	popUpBack->setPosition(Vec2((winSize.width/2), (winSize.height/2)+100) );
	this->addChild(popUpBack);
	backSize = popUpBack->getContentSize();
	
	Sprite* pauseTitle = Sprite::create("Layer/lPopUp/lClear.png");
	pauseTitle->setPosition(Vec2((backSize.width/2), (backSize.height/2 + 300)) );
	popUpBack->addChild(pauseTitle);
	
	float size_x;
	Sprite* stageTitle = makeStageNumber( GameLayer::getStageNum(), &size_x);
	stageTitle->setPosition(Vec2((backSize.width/2 - size_x/2), (backSize.height/2 + 170)) );
	popUpBack->addChild(stageTitle);

	MenuItemImage *RESTARTItem = MenuItemImage::create(
														   "Layer/lPopUp/lRestartBase.png",
														   "Layer/lPopUp/lRestartTouch.png",
														   this,
														   menu_selector(PEPopupSuccess::restart) );
    Menu* RESTARTbtn = CCMenu::create(RESTARTItem, NULL);
    RESTARTbtn->setPosition(Vec2(backSize.width/2, backSize.height/2 - 200.0f));
    popUpBack->addChild(RESTARTbtn);
	
	MenuItemImage *EXITItem = MenuItemImage::create(
														"Layer/lPopUp/lExitBase.png",
														"Layer/lPopUp/lExitTouch.png",
														this,
														menu_selector(PEPopupSuccess::exit) );
    Menu* EXITbtn = Menu::create(EXITItem, NULL);
	Size EXITbtnSize = EXITItem->getContentSize();
    EXITbtn->setPosition(Vec2(EXITbtnSize.width/2+50, backSize.height/2 - 200.0f));
    popUpBack->addChild(EXITbtn);
	
	MenuItemImage *NEXTItem = MenuItemImage::create(
														  "Layer/lPopUp/lNextBase.png",
														  "Layer/lPopUp/lNextTouch.png",
														  this,
														  menu_selector(PEPopupSuccess::resume) );
    Menu* NEXTbtn = Menu::create(NEXTItem, NULL);
	Size NEXTbtnSize = NEXTItem->getContentSize();
    NEXTbtn->setPosition(Vec2(backSize.width - (NEXTbtnSize.width/2+50), backSize.height/2 - 200.0f));
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
    
	Armature* star_0 = Armature::create("lStar");
	star_0->setPosition(backSize.width/4, backSize.height/2);
 	star_0->getAnimation()->playWithIndex(1, -1, -1);
	popUpBack->addChild(star_0);
	
	int door1_star_ani = 0;
	if(score > 1)
		door1_star_ani = 1;
		
	Armature* star_1 = Armature::create("lStar");
	star_1->setPosition(backSize.width/2, backSize.height/2);
	star_1->getAnimation()->playWithIndex(door1_star_ani, -1, -1);
	popUpBack->addChild(star_1);
	
	int door2_star_ani = 0;
	if(score > 2)
		door2_star_ani = 1;
	Armature* star_2 = Armature::create("lStar");
	star_2->setPosition(backSize.width*3/4 , backSize.height/2);
 	star_2->getAnimation()->playWithIndex(door2_star_ani, -1, -1);
	popUpBack->addChild(star_2);
	
    // check stage score - save stage score
	char buf[15];
    int pre_score;
	sprintf(buf, "stage%d", GameLayer::getStageNum());
    pre_score = UserDefault::getInstance()->getIntegerForKey(buf);
    if(pre_score < score)
    {
        if(door2_star_ani)
            UserDefault::getInstance()->setIntegerForKey(buf, 3);
        else if(door1_star_ani)
            UserDefault::getInstance()->setIntegerForKey(buf, 2);
        else
            UserDefault::getInstance()->setIntegerForKey(buf, 1);
    }
    return true;
}

void PEPopupSuccess::restart(Ref* pSender)
{
	
	PEBackgroundMusic::sharedPEBackgroundMusic()->PE_stop();
	Scene *nextScene = GameLayer::scene(GameLayer::getStageNum());
	if(nextScene != NULL)
	{
		TransitionScene* pTran = TransitionFade::create(2.0f, nextScene);
		Director::getInstance()->replaceScene(pTran);
	}
	
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	__String* popParam=__String::create(buf);
	__NotificationCenter::getInstance()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
	
}

void PEPopupSuccess::exit(Ref* pSender)
{
	Scene *nextScene = PEMain::scene();
	if(nextScene != NULL)
	{
		TransitionScene* pTran = TransitionFade::create(5.0f, nextScene);
		Director::getInstance()->replaceScene(pTran);
	}
	
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	__String* popParam=__String::create(buf);
	__NotificationCenter::getInstance()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
}

void PEPopupSuccess::resume(Ref* pSender)
{
	char buf[5];
	sprintf(buf, "%d", POPUP_RESUME);
	__String* popParam=__String::create(buf);
	__NotificationCenter::getInstance()->postNotification("scene_popup", popParam);
	this->removeFromParentAndCleanup(true);
}


Sprite* PEPopupSuccess::makeStageNumber(int num, float *size)
{
    Sprite *stageLabel = Sprite::create();
    int i, index;
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
        index = ( dynamic_cast<__Integer*>( num_array->getObjectAtIndex(i) ) )->getValue();
		sprintf(file_path, "Layer/lPopUp/lPopUpNum%d.png", index);
		
        spr = Sprite::create(file_path);
        spr->setAnchorPoint( Vec2( 0, 0 ) );
        spr->setPositionX( *size );
		
        stageLabel->addChild( spr );
		*size += spr->getContentSize().width;
	}
	
    return stageLabel;
}
