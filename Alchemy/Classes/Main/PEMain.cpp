//
//  PEMain.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 10..
//
//

#include "PEMain.h"
#include "../Sound/PEBackgroundMusic.h"
#include "../Sound/PESoundEffect.h"
#include "../Layer/GameLayer.h"
#include "../PopUp/PEPopUpSetting.h"

#if defined(WIN32) || defined(CC_TARGET_OS_MAC)
#define START_DELAY		0
#define FADE_IN_DELAY		0
#define FADE_OUT_DELAY	0
#define BUTTON_DELAY		0
#define BUTTON_FADE_IN_DELAY 0
#else
#define START_DELAY		0.5f
#define FADE_IN_DELAY		2.0f
#define FADE_OUT_DELAY	1.0f
#define BUTTON_DELAY		1.5f
#define BUTTON_FADE_IN_DELAY 1.5f
#endif

#define MAIN_TOP_BACK_X 162.0f
#define MAIN_TOP_BACK_Y 1830.0f

#define MAIN_TITLE_X 1060.0f
#define MAIN_TITLE_Y 1775.0f

#define TITLE_CHANGE_DURATION 0.5f

enum BOTTOM_ICON
{
	ICON_PROFILE = 0,
	ICON_STAGE,
	ICON_NOTE,
	ICON_INFINITE,
	ICON_MAX,
};

char bottom_selected_icon[4][50] =
{
	"Layer/lMainUi/IMainProfile_select.png",
	"Layer/lMainUi/IMainStage_select.png",
	"Layer/lMainUi/IMainNote_select.png",
	"Layer/lMainUi/IMainInfinite_select.png"
};

char bottom_unselected_icon[4][50] =
{
	"Layer/lMainUi/IMainProfile.png",
	"Layer/lMainUi/IMainStage.png",
	"Layer/lMainUi/IMainNote.png",
	"Layer/lMainUi/IMainInfinite.png"
};

char main_title_file[4][50] =
{
	"Layer/lMainUi/lMainProfile.png",
	"Layer/lMainUi/lMainStage.png",
	"Layer/lMainUi/lMainNote.png",
	NULL
};

char main_card_file[4][50] =
{
	"Layer/lStage/lProfileBack.png",
	"Layer/lStage/lStageBack.png",
	"Layer/lStage/lNoteBack.png",
	NULL
};

Scene* PEMain::scene(){
	Scene* pScene = Scene::create();
	PEMain* pPEMain = new PEMain();
	pPEMain->init();
	pScene->addChild(pPEMain);
	
	return pScene;
}

bool PEMain::init()
{
	autorelease();
	this->scheduleOnce(schedule_selector(PEMain::startMain), START_DELAY);
	setTouchEnabled(true);
	setKeypadEnabled(true);
	
	selected_bottom_icon = ICON_STAGE;
	tracking_bottom_icon = ICON_STAGE;
	main_stage_index = 0;
	bottom_ani_playing = false;
	bottom_btn_selected = false;
	bottom_card_enable = true;
	touched_id = -1;
	
	
	onButtonSelect[ICON_PROFILE] = &PEMain::profile;
	onButtonSelect[ICON_STAGE] = &PEMain::stage;
	onButtonSelect[ICON_NOTE] = &PEMain::note;
	onButtonSelect[ICON_INFINITE] = &PEMain::infinite;
	
	return true;
}

float main_card_pos_x[ICON_MAX] =
{
	-540.0f,
	540.0f,
	1620.0f,
	2700.0f,
};



void PEMain::startMain(float in)
{
	Sprite* background = Sprite::create("Layer/lMainUi/IMainBackground.png");
	background->setPosition(Vec2::ZERO);
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	addChild(background);
	
	main_card = Sprite::create();
	
	for(int i=0; i<ICON_MAX; i++)
	{
		main_card_array[i] = Sprite::create(main_card_file[i]);
		if(main_card_array[i] != NULL)
		{
			main_card_array[i] ->setPosition(Vec2(main_card_pos_x[i], 1000.0f));
			main_card->addChild(main_card_array[i]);
		}
	}
	addChild(main_card);
	
	Size main_size = main_card_array[ICON_STAGE]->getContentSize();
	main_left_top = Vec2(main_card_pos_x[ICON_STAGE] - main_size.width/2, 1000.0f - main_size.height/2);
	
	init_Main_stageBtn(1);
	
	init_topBtn();
	init_bottonBtn();
	
    CCFadeTo*  fadeto = CCFadeTo::create(FADE_IN_DELAY, 255);
    background->runAction(fadeto);

    PEBackgroundMusic::sharedPEBackgroundMusic()->PE_play(PEBackgroundMusic::BGM_THEME12);
	
}


float main_stage_btn_pos_y[4] =
{
	1203.0f,
	893.0f,
	583.0f,
	273.0f
};

void PEMain::init_Main_stageBtn(int stage_num_start)
{
	Size main_panel_size = main_card_array[ICON_STAGE]->getContentSize();
	Size main_button_size;
	int i, j;
	int prev_stage_star = 3;
	for(j=0; j<4; j++)
	{
		for(i=0; i<3; i++)
		{
			int stage_num = stage_num_start + j*3 + i;
			bool btn_enable = true;
			if(prev_stage_star == 0)
				btn_enable = false;
		
			stage_btn[j*3 + i] = PEStageBtn::create(stage_num, btn_enable);
			stage_btn[j*3 + i]->setPosition(Vec2(main_panel_size.width/2 + 290.0f*(i-1), main_stage_btn_pos_y[j]));
			main_card_array[ICON_STAGE]->addChild(stage_btn[j*3 + i]);
			

			prev_stage_star = stage_btn[j*3 + i]->get_stage_stars();
		}
	}
}

void PEMain::init_topBtn()
{
	CCMenuItemImage* top_back = CCMenuItemImage::create(
														"Layer/lMainUi/IMainTopBack.png",
														"Layer/lMainUi/IMainTopBack_select.png",
														this,
														menu_selector(PEMain::back) );
	
	CCMenuItemImage* top_setting = CCMenuItemImage::create(
														   "Layer/lMainUi/IMainTopSetting.png",
														   "Layer/lMainUi/IMainTopSetting_select.png",
														   this,
														   menu_selector(PEMain::setting) );
	
	top_btn = CCMenu::create(top_back, top_setting, NULL);
	top_btn->alignItemsHorizontallyWithPadding(10.0f);
    top_btn->setPosition(Vec2(MAIN_TOP_BACK_X, MAIN_TOP_BACK_Y));
	addChild(top_btn);
}

Vec2 bottom_select_pos[ICON_MAX] =
{
	Vec2(113.0f, 135.0f),
	Vec2(325.0f, 135.0f),
	Vec2(537.0f, 135.0f),
	Vec2(749.0f, 135.0f),
};

void PEMain::init_bottonBtn()
{
	int i;
	
	for(i=0; i<ICON_MAX; i++)
	{
		bottom_unselect_icon_array[i] = Sprite::create(bottom_unselected_icon[i]);
		bottom_unselect_icon_array[i]->setPosition(bottom_select_pos[i]);
		addChild(bottom_unselect_icon_array[i]);
	}
	
	for(i=0; i<ICON_MAX; i++)
	{
		bottom_select_icon_array[i] = Sprite::create(bottom_selected_icon[i]);
		bottom_select_icon_array[i]->setPosition(bottom_select_pos[i]);
		bottom_select_icon_array[i]->setVisible(false);
		addChild(bottom_select_icon_array[i]);
	}
	
	bottom_select_stroke = Sprite::create("Layer/lMainUi/IMainBottomSelectStroke.png");
	addChild(bottom_select_stroke,10);
	
	bottom_select_icon_array[selected_bottom_icon]->setVisible(true);
	bottom_select_stroke->setPosition(bottom_select_pos[selected_bottom_icon]);
	
	for(i=0; i<ICON_MAX; i++)
	{
		main_title_array[i] = Sprite::create(main_title_file[i]);
		if( main_title_array[i] == NULL)
			continue;
		
		main_title_array[i]->setPosition(Vec2(MAIN_TITLE_X,MAIN_TITLE_Y));
		main_title_array[i]->setAnchorPoint(Vec2(1.0f, 0.0f));
		addChild(main_title_array[i]);
		main_title_array[i]->setVisible(false);
	}
	
	main_title_array[selected_bottom_icon]->setVisible(true);
}

void PEMain::back(Ref* pSender)
{
    PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_BUTTON_1);
	keyBackClicked();
}

void PEMain::resume(void)
{
	setTouchEnabled(true);
	setKeypadEnabled(true);
	top_btn->setTouchEnabled(true);
}

void PEMain::setting(Ref* pSender)
{
    PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_BUTTON_1);
	PEPopUpSetting* pPopUp = new PEPopUpSetting();
	pPopUp->init();
	pPopUp->setResume(this, (SEL_Resume)(&PEMain::resume));
	setTouchEnabled(false);
	setKeypadEnabled(false);
	top_btn->setTouchEnabled(false);
	addChild(pPopUp, 20);
}

void PEMain::note()
{
	last_selected_bottom_icon = selected_bottom_icon;
	selected_bottom_icon = ICON_NOTE;
	
	bottom_select_icon_array[last_selected_bottom_icon]->setVisible(false);
	bottom_select_icon_array[selected_bottom_icon]->setVisible(true);
	
	bottom_select_stroke->stopAllActions();
	bottom_select_stroke->setPosition(bottom_select_pos[selected_bottom_icon]);
}

void PEMain::profile()
{
	last_selected_bottom_icon = selected_bottom_icon;
	selected_bottom_icon = ICON_PROFILE;
	
	bottom_select_icon_array[last_selected_bottom_icon]->setVisible(false);
	bottom_select_icon_array[selected_bottom_icon]->setVisible(true);
	
	bottom_select_stroke->stopAllActions();
	bottom_select_stroke->setPosition(bottom_select_pos[selected_bottom_icon]);
}

void PEMain::stage()
{
	last_selected_bottom_icon = selected_bottom_icon;
	selected_bottom_icon = ICON_STAGE;
	bottom_select_icon_array[last_selected_bottom_icon]->setVisible(false);
	bottom_select_icon_array[selected_bottom_icon]->setVisible(true);
	
	bottom_select_stroke->stopAllActions();
	bottom_select_stroke->setPosition(bottom_select_pos[selected_bottom_icon]);
	
}

void PEMain::infinite()
{
	last_selected_bottom_icon = selected_bottom_icon;
	selected_bottom_icon = ICON_INFINITE;
	
	bottom_select_icon_array[last_selected_bottom_icon]->setVisible(false);
	bottom_select_icon_array[selected_bottom_icon]->setVisible(true);
	
	bottom_select_stroke->stopAllActions();
	bottom_select_stroke->setPosition(bottom_select_pos[selected_bottom_icon]);
	
}

int current_main_card;
int last_main_card;
void PEMain::title_out()
{
	float diff_x = (last_main_card < current_main_card)?-250:250;
	if(last_main_card == current_main_card)
	{
		bottom_card_enable = true;
		return;
	}
	
	if(main_title_array[last_main_card] == NULL)
	{
		title_in(NULL);
		bottom_card_enable = true;
		return;
	}
	
	CCMoveBy* pMoveBy = CCMoveBy::create(TITLE_CHANGE_DURATION, Vec2(diff_x, 0.0f));
	CCFadeTo* actionFadeTo = CCFadeTo::create(TITLE_CHANGE_DURATION,0);
	CCSpawn* pSpwan = CCSpawn::create(pMoveBy, actionFadeTo, NULL);
	CCCallFuncO* pCallFuncO =  CCCallFuncO::create(this, callfuncO_selector(PEMain::title_in), this);
	main_title_array[last_main_card]->runAction(CCSequence::create(pSpwan, pCallFuncO, NULL));
}

void PEMain::title_in(Ref* obj)
{
	float diff_x = (last_main_card < current_main_card)?-250:250;
	
	if(main_title_array[current_main_card] != NULL)
	{
		main_title_array[current_main_card]->setVisible(true);
		main_title_array[current_main_card]->setPosition(Vec2(MAIN_TITLE_X - diff_x, MAIN_TITLE_Y));
		
		CCMoveBy* pMoveBy_select = CCMoveBy::create(TITLE_CHANGE_DURATION, Vec2(diff_x, 0.0f));
		CCFadeIn* actionFadeIn_select = CCFadeIn::create(TITLE_CHANGE_DURATION);
		CCSpawn* pSpwan_select = CCSpawn::create(pMoveBy_select, actionFadeIn_select,NULL);
		main_title_array[current_main_card]->runAction(pSpwan_select);
	}
	
	bottom_card_enable = true;
	last_main_card = current_main_card;
}

void PEMain::changeMainCard()
{
	if(bottom_card_enable)
	{
        if(current_main_card != selected_bottom_icon)
        {
        PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_WHOOSH);
        
		float diff = (main_card_pos_x[selected_bottom_icon] - 540.0f) + main_card->getPosition().x;
		CCMoveBy* pMoveBy = CCMoveBy::create(TITLE_CHANGE_DURATION, Vec2(-diff, 0.0f));
		
		current_main_card = selected_bottom_icon;
		bottom_card_enable = false;
		main_card->stopAllActions();
		main_card->runAction(CCSequence::create(pMoveBy,NULL));
		title_out();
        }
	}
}

void PEMain::stage_select(int stage)
{
	PEBackgroundMusic::sharedPEBackgroundMusic()->PE_stop();
	Scene *nextScene = GameLayer::scene(stage);
	if(nextScene != NULL)
	{
		CCTransitionScene* pTran = CCTransitionFade::create(FADE_OUT_DELAY, nextScene);
		Director::getInstance()->replaceScene(pTran);
	}
}

bool PEMain::PE_check_bottom_btn(Vec2 pos)
{
	int i;
	bool ret = false;

	for(i=0; i<ICON_MAX; i++)
	{
		if(bottom_unselect_icon_array[i]->getBoundingBox().containsPoint(pos) )
		{
			Vec2 strok_pos = bottom_select_stroke->getPosition();
			if(tracking_bottom_icon != i)
			{
				float diff_x = bottom_select_pos[i].x - strok_pos.x;
				float duration = 0.1f;
				CCMoveBy* pMoveBy = CCMoveBy::create(duration, Vec2(diff_x, 0.0f));
				CCCallFuncO* pCallFuncO =  CCCallFuncO::create(this, callfuncO_selector(PEMain::onEndOfSelecctorMoving), this);
				bottom_select_stroke->runAction(CCSequence::create(pMoveBy, pCallFuncO, NULL));
				tracking_bottom_icon = i;
				bottom_btn_selected = true;
				ret = true;
			}
			break;
		}
	}

	return ret;
}

int PEMain::check_touched_btn(Vec2 pos)
{
	int i;

	Size stage_card_size = main_card_array[ICON_STAGE]->getContentSize();
	Vec2 stage_card_pos = main_card_array[ICON_STAGE]->getPosition();
	pos.x -= (540 - stage_card_size.width/2);
	pos.y -= (stage_card_pos.y-stage_card_size.height/2);

	for(i=0; i<12; i++)
	{
		if( stage_btn[i]->get_valid()
			&& stage_btn[i]->get_boundingbox().containsPoint( Vec2(pos.x, pos.y) ) )
		{
			stage_btn[i]->toggle_btn(true);	

			return i;
		}
	}

	return -1;
}

void PEMain::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	int touchId = touches[0]->getID();
	Vec2 pos = touches[0]->getLocation();

	if(touched_id != -1)
		return;

	if(!bottom_ani_playing)
	{
		bottom_ani_playing = PE_check_bottom_btn(pos);
        if(bottom_ani_playing)
            PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_BUTTON_1);
        
		if(current_main_card == ICON_STAGE)
		{
			select_stage_btn = check_touched_btn(pos);
            if(select_stage_btn != -1)
                PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_ENTER);
		}
		touched_id = touchId;
	}
	return;
}

void PEMain::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
    Touch* touch;
	Vec2 pos;
    bool selected_touch = false;

	if(touched_id == -1 
		|| bottom_ani_playing
		|| !bottom_btn_selected)
    	return;

    for(auto& pTouch : touches)
    {
    	if(touched_id == pTouch->getID())
    	{
    		selected_touch = true;
            touch = pTouch;
    		break;
    	}
    }
	
    if(!selected_touch)
    	return;

	pos = touch->getLocation();
	bottom_ani_playing = PE_check_bottom_btn(pos);
}

void PEMain::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
	int i;
	Touch* pTouch = (Touch*)touches[0];
	Vec2 pos = pTouch->getLocation();
	int touchId = pTouch->getID();

	if(bottom_btn_selected
		|| touched_id != -1)
	{
		if(touched_id == touchId)
		{
			for(i=0; i<ICON_MAX; i++)
			{
				if(bottom_unselect_icon_array[i]->getBoundingBox().containsPoint(pos))
				{
					bottom_select_stroke->stopAllActions();
					bottom_select_stroke->setPosition(bottom_select_pos[i]);
					(this->*onButtonSelect[i])();
					break;
				}
			}
			tracking_bottom_icon = -1;
			bottom_btn_selected = false;
			bottom_ani_playing = false;
			touched_id = -1;
		}
	}

	changeMainCard();

	
	if(current_main_card == ICON_STAGE)
	{
		if(select_stage_btn > -1 && select_stage_btn < 12)
		{
			int i = check_touched_btn(pos);
			
			if( select_stage_btn == i)
			{
				stage_select(stage_btn[i]->getTag());
			}
			else
			{
				stage_btn[select_stage_btn]->toggle_btn(false);	
			}
		}
		select_stage_btn = -1;
	}
}

void PEMain::onEndOfSelecctorMoving(Ref* obj)
{
	bottom_ani_playing = false;
}

bool back_key_clicked = false;
/*
void PEMain::keyBackClicked(void)
{
	PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_BUTTON_1);
	if(selected_bottom_icon != ICON_STAGE)
	{
		(this->*onButtonSelect[ICON_STAGE])();
		changeMainCard();
	}
	else
	{
		if(!back_key_clicked)
		{
			back_key_clicked = true;
			this->scheduleOnce(schedule_selector(PEMain::back_key_clicked_reset), 0.5f);
		}
		else
			Director::getInstance()->end();
	}
}
*/

void PEMain::back_key_clicked_reset(float in)
{
	back_key_clicked = false;
}

/*  
 * PEStageBtn class
 * for stage button 
 */

PEStageBtn* PEStageBtn::create(int index, bool valid)
{
	PEStageBtn* btn = new PEStageBtn();
	btn->init_btn(index, valid);
	btn->autorelease();
	
	return btn;
}

void PEStageBtn::init_btn(int index, bool valid)
{
	float main_num_text_size; 
	touched_btn_back = NULL;
	stage = index;
	setTag(index);
	isTouched = false;
	is_valid = valid;
	stars = load_stage_stars();
	touched_btn_back = Sprite::create("Layer/lMainUi/IStageUi/IMainStageBtn.png");
	addChild(touched_btn_back);
	if(!is_valid)
	{
		touched_btn_back->setOpacity(128);
	}

	touched_btn_back_select = Sprite::create("Layer/lMainUi/IStageUi/IMainStageBtn_select.png");
	touched_btn_back_select->setVisible(false);
	touched_btn_back_select->setAnchorPoint(Vec2(0.0f, 0.0f));
	touched_btn_back->addChild(touched_btn_back_select);

	Size main_button_size = touched_btn_back->getContentSize();
	
	stage_num_text = makeStageNumber(index, &main_num_text_size, is_valid);
	stage_num_text->setPosition(Vec2(main_button_size.width/2-main_num_text_size/2 - 3, 95));
	touched_btn_back->addChild(stage_num_text);

	// show stage stars
	char buf[15];
	sprintf(buf, "stage%d", index);
	int stars = UserDefault::sharedUserDefault()->getIntegerForKey(buf);
	log("stage:%d - star:%d\n", index, stars);
	if(stars > 0)
	{
		for(int i=0; i<stars; i++)
		{
			char path[50];
			sprintf(path, "Layer/lMainUi/IStageUi/IMainStageBtn_star%d.png", i+1);
			Sprite* main_stageBtn_star = Sprite::create(path);
			main_stageBtn_star->setPosition(Vec2(0.0f, 0.0f));
			main_stageBtn_star->setAnchorPoint(Vec2(0.0f, 0.0f));
			touched_btn_back->addChild(main_stageBtn_star);
		}
	}
}

Sprite* PEStageBtn::makeStageNumber(int num, float *size, bool opacity)
{
    Sprite *numberLabel = Sprite::create();
    int i, index;
    Sprite *spr;
	char file_path[40];
	
	*size = 0.0;
    
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
		sprintf(file_path, "Layer/lMainUi/IStageUi/%d.png", index);
		
		spr = Sprite::create(file_path);
		spr->setAnchorPoint( Vec2( 0, 0 ) );
		spr->setPositionX( *size );
		
		if(!opacity)
			spr->setOpacity(128);

		numberLabel->addChild( spr );
		*size += spr->getContentSize().width;

	}
    return numberLabel;
}

int PEStageBtn::load_stage_stars(void)
{
	char buf[15];
	sprintf(buf, "stage%d", this->stage);
	return UserDefault::sharedUserDefault()->getIntegerForKey(buf);
}

int PEStageBtn::get_stage_stars(void)
{
	return this->stars;
}

void PEStageBtn::set_stage_stars(int star)
{
	char buf[15];
	this->stars = star;
	sprintf(buf, "stage%d", this->stage);
	UserDefault::sharedUserDefault()->setIntegerForKey(buf, star);
	UserDefault::sharedUserDefault()->flush();
}

void PEStageBtn::toggle_btn(bool flag)
{
	if(flag)
	{
		if(!isTouched)
		{
			touched_btn_back_select->setVisible(true);
			isTouched = true;
		}
	}
	else
	{
		if(isTouched)
		{
			touched_btn_back_select->setVisible(false);
			isTouched = false;
		}

	}
}

bool PEStageBtn::get_valid(void)
{
	return is_valid;
}

Rect PEStageBtn::get_boundingbox(void)
{
	Rect rect = touched_btn_back->getBoundingBox();
	Size size = touched_btn_back->getContentSize();
	rect.setRect(getPositionX() - size.width/2, getPositionY() - size.height/2, size.width, size.height);
	return rect;
}
