#include "MixPanel.h"
#include "PEIcon.h"
#include "../Object/MixResource.h"
#include "../Object/PEObject.h"
#include "../Object/PE_Collision.h"
#include "../PopUp/PEPopUpManager.h"
#include "../Sound/PESoundEffect.h"
#include "PEProgressBar.h"

#define SELECT_NOTI_OFFSET_X		38.0f
#define SELECT_NOTI_OFFSET_Y		(-38.0f)

#define MIX_INVALID_NOTI_OFFSET_X		150.0f
#define MIX_INVALID_NOTI_OFFSET_Y		80.0f

char icon_background_filename[4][50] =
{
	"Layer/lInGame/lIconBarWind.png",
	"Layer/lInGame/lIconBarWater.png",
	"Layer/lInGame/lIconBarFire.png",
	"Layer/lInGame/lIconBarEarth.png"
};
Vec2 mov_dist_4element[4] =
{
	ccp(-34.0, 20.0f),
	ccp(-20.0, 34.0f),
	ccp(20.0, 34.0f),
	ccp(34.0, 20.0f),
};

Vec2 mixBtn_pos = ccp(540.0f, 87.0f);

/* 1 Circle Position */
Vec2 element_icon_pos[4] =
{
	ccp(-248, 248),
	ccp(-91, 339),
	ccp(91, 339),
	ccp(248, 248),
};

/* 2~3 Circle Position */
Vec2 alchemy_icon_pos[7] =
{
	ccp(-350, 0),
	ccp(-305, 175),
	ccp(-175, 303),
	ccp(0, 350),
	ccp(175, 303),
	ccp(305, 175),
	ccp(350, 0),
};

float alchemy_icon_angle[7] =
{
	-90.0f,
	-60.0f,
	-30.0f,
	0.0f,
	30.0f,
	60.0f,
	90.0f,
};

Vec2 mix_result_pos[4] =
{
	ccp(95.0f, 90.0f),
	ccp(285.0f, 90.0f),
	ccp(795.0f, 90.0f),
	ccp(985.0f, 90.0f)
};

/*
 first index : 
 0 - 1 element
 1 - 2 element
 2 - 3 element
 3 - 4 element

 second index : 
 0 - left
 1 - right
 */
int icon_pos_index[4][2][4] =
{
	{{3,0,0,0}, {3,0,0,0}},
	{{3,4,0,0}, {2,3,0,0}},
	{{2,3,4,0}, {2,3,4,0}},
	{{2,3,4,5}, {1,2,3,4}},
};

enum MixPanel_Zorder
{
	ZORDER_PANEL = 0,
	ZORDER_LOW_ICON,
	ZORDER_HIGH_ICON = 10,
};

float fade_in_t = 0.2f;

MixPanel::MixPanel()
:PETouchGesture()
{}
MixPanel::~MixPanel()
{}


bool MixPanel::init() {
	if(CCLayer::init() == false) {
		return false;
	}
    
	autorelease();
	setTouchEnabled(true);
	
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
	"Layer/lInGame/lEssenceButton/lEssenceButton0.png", 
	"Layer/lInGame/lEssenceButton/lEssenceButton0.plist", 
	"Layer/lInGame/lEssenceButton/lEssenceButton.ExportJson");
	mixBtn  = CCArmature::create("lEssenceButton");
    mixBtn->setPosition(mixBtn_pos);
	mixBtn->getAnimation()->playWithIndex(0, -1, -1, -1, 10000);
    addChild(mixBtn,11);
 	
	/* MixPenal : background */
	mixPanel = CCSprite::create("Layer/lInGame/lMixPanel.png");
	Size panel_size = mixPanel->getContentSize();
	mixPanel->setPosition(Vec2Zero);
	mixPanel->setAnchorPoint(ccp(0.0f, 0.0f));
	addChild(mixPanel,10);

	/* Mana Bar */
	mana_bar = PEProgressBar::create("Layer/lInGame/lManaBar.png", 10, 0, ccp(0.0f, 0.5f));
	mana_bar->setPosition(ccp(panel_size.width - 62.0f - mana_bar->get_bar_width(), 203.0f));
	mana_bar->set_bar_start_pos(ccp(panel_size.width - 62.0f - mana_bar->get_bar_width(), 203.0f));
	mixPanel->addChild(mana_bar);
	
	/* Con Bar */
	con_bar = PEProgressBar::create("Layer/lInGame/lConBar.png", 10, 1, ccp(1.0f, 0.5f));
	con_bar->setPosition(ccp(62.0f + con_bar->get_bar_width(), 203.0f));
	con_bar->set_bar_start_pos(ccp(62.0f + con_bar->get_bar_width(), 203.0f));
	mixPanel->addChild(con_bar);
	
	Vec2 doorLife_pos[5] =
	{
		ccp(panel_size.width/2 - 110.0f,	231.0f),
		ccp(panel_size.width/2 - 58.0f,		260.0f),
		ccp(panel_size.width/2+1,			270.0f),
		ccp(panel_size.width/2 + 60.0f,		260.0f),
		ccp(panel_size.width/2 + 112.0f,	231.0f)
	};
	
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
		"Layer/lInGame/lDoorLife/lDoorLife0.png", 
		"Layer/lInGame/lDoorLife/lDoorLife0.plist", 
		"Layer/lInGame/lDoorLife/lDoorLife.ExportJson");

	for(int i=0; i<5; i++)
	{
		doorLife[i]  = CCArmature::create("lDoorLife");
		doorLife[i]->setPosition(doorLife_pos[i]);
		doorLife[i]->getAnimation()->playWithIndex(0, -1, -1, -1, 10000);
		mixPanel->addChild(doorLife[i],10);
	}
	doorLifeCount = 5;
	send_fail_flag = false;
	
	for(int i=0 ; i<ICON_NUM_MAX; i++)
	{
		icon[i] = NULL;
		icon_background[i] = NULL;
	}
	
	for(int i=0; i<4; i++)
	{
		circle_index[i] = 0;
		icon_count_per_circle[i] = 0;
		alchemy_icon[i] = NULL;
	}
	
	/* selected icon noti */
	select_noti = CCSprite::create("Layer/lSelect.png");
	this->addChild(select_noti, ZORDER_LOW_ICON);
	select_noti->setVisible(false);

	/* invalid mix noti */
	mix_invalid_noti = CCSprite::create("Layer/lMixShow.png");
	this->addChild(mix_invalid_noti, ZORDER_LOW_ICON);
	mix_invalid_noti->setVisible(false);
	touched_id = -1;
	
	PE_Collision::getPE_Collision()->setHitDoorCallback(this, (SEL_HITDOOR)&MixPanel::decreaseDoorLife);
	
	previous_selected_index = -1;
	double_tap_called = false;

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,	callfuncO_selector(MixPanel::regen_con_mana),"regen_con_mana", NULL);

	
	batch_par = CCSpriteBatchNode::create("fire.png", 5);
	addChild(batch_par);
	
	return true;
}

void MixPanel::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "regen_con_mana");
}

void MixPanel::particle_end(CCObject* pObject)
{
	CCArray *pParam=(CCArray*)pObject;
	CCParticleSun* par = (CCParticleSun*)pParam->objectAtIndex(0);

	par->stopSystem();
}

void MixPanel::bar_change(CCObject* pObject)
{
	CCArray *pParam=(CCArray*)pObject;
	CCInteger* type = (CCInteger*)pParam->objectAtIndex(0);
	CCInteger* value = (CCInteger*)pParam->objectAtIndex(1);
	CCParticleSun* par = (CCParticleSun*)pParam->objectAtIndex(2);

	switch(type->getValue())
	{
		//con
		case 0:
			con_bar->change_result_bar(value->getValue());
			con_bar->erase_particle_from_vector();
			break;
		//mana	
		case 1:
			mana_bar->change_result_bar(value->getValue());
			mana_bar->erase_particle_from_vector();
			check_alchemy_icon_valid();
			break;
	}
	par->removeFromParent();
}

void MixPanel::add_particle_to_bar(CCObject* object)
{
	CCArray *pParam=(CCArray*)object;
	CCParticleSun* par = (CCParticleSun*)pParam->objectAtIndex(0);
	CCInteger* type = (CCInteger*)pParam->objectAtIndex(1);
	
	switch(type->getValue())
	{
		//con
		case 0:
			par->setPosition(ccp(con_bar->get_bar_start_pos().x - con_bar->get_bar_end_pos(), con_bar->get_bar_start_pos().y));
			con_bar->push_particle_to_vector(par);
			break;
		//mana
		case 1:
			par->setPosition(ccp(mana_bar->get_bar_start_pos().x + mana_bar->get_bar_end_pos(), mana_bar->get_bar_start_pos().y));
			mana_bar->push_particle_to_vector(par);
			break;
	}
}

void MixPanel::regen_con_mana(CCObject *obj){
	CCArray *pParam=(CCArray*)obj;
	CCInteger* data = (CCInteger*)pParam->objectAtIndex(0);
	CCFloat* pos_x =(CCFloat*)pParam->objectAtIndex(1);
	CCFloat* pos_y =(CCFloat*)pParam->objectAtIndex(2);
	int type = data->getValue()%2;
	int value = data->getValue()/2;
	float x = pos_x->getValue();
	float y = pos_y->getValue();

	PRINT_LOG("regen %s - %d\n", (type==0)?"CON":"MANA", value);
	

	ccBezierConfig bezierConfig;
	if(type == 0)
	{
		bezierConfig.endPosition = ccp(con_bar->get_bar_start_pos().x - con_bar->get_bar_end_pos(), con_bar->get_bar_start_pos().y);
		bezierConfig.controlPoint_1 = ccp(x,y+100.0f);
		bezierConfig.controlPoint_2 = ccp(bezierConfig.endPosition.x, y+100.0f);
	}
	else
	{
		bezierConfig.endPosition = ccp(mana_bar->get_bar_start_pos().x + mana_bar->get_bar_end_pos(), mana_bar->get_bar_start_pos().y);
		bezierConfig.controlPoint_1 = ccp(x,y+100.0f);
		bezierConfig.controlPoint_2 = ccp(bezierConfig.endPosition.x, y+100.0f);
	}
	
	CCBezierTo* pBezier = CCBezierTo::create(0.7, bezierConfig);
	CCParticleSun* par = CCParticleSun::create();
    addChild(par, 10);
    par->setTexture(batch_par->getTexture());
	par->setStartColor(ccc4f(1,1,1,0.7));
	par->setEndColor(ccc4f(1,0.8,0.8,0.7));
	par->setPosition(x,y);
	par->setLife(0.4);

	CCActionInterval* wait = CCDelayTime::create(0.5);
	CCArray* array1 = CCArray::create(par, CCInteger::create(type), NULL);
	CCArray* array2 = CCArray::create(par, NULL);
	CCArray* array3 = CCArray::create(CCInteger::create(type), CCInteger::create(value), par, NULL);
	CCCallFuncO* pCallFunc0 =  CCCallFuncO::create(this, callfuncO_selector(MixPanel::add_particle_to_bar), (CCObject*)array1);
	CCCallFuncO* pCallFunc1 =  CCCallFuncO::create(this, callfuncO_selector(MixPanel::particle_end), (CCObject*)array2);
	CCCallFuncO* pCallFunc2 =  CCCallFuncO::create(this, callfuncO_selector(MixPanel::bar_change), (CCObject*)array3);
    par->runAction(CCSequence::create( pBezier, pCallFunc0, wait, pCallFunc1, wait, pCallFunc2, NULL));
}

void MixPanel::setField(Field* field)
{
	mField = field;
	return;
}

void MixPanel::setPEIcon(PEIcon* peicon){
	mPEIcon = peicon;
	return;
}

bool MixPanel::PE_checkClickMixBtn(Vec2* pos)
{
	return mixBtn->boundingBox().containsPoint(*pos);
}

void MixPanel::resetPanel()
{
	for(int i=0; i<ICON_NUM_MAX; i++)
	{
		if(icon_background[i] != NULL)
		{
			CCFadeOut* action_Fade_1 =  CCFadeOut::create(fade_in_t);
			CCFadeOut* action_Fade_2 =  CCFadeOut::create(fade_in_t);
			icon_background[i]->runAction(action_Fade_1);
			icon_background[i] = NULL;
			icon[i]->runAction(action_Fade_2);
			icon[i] = NULL;
		}
	}
	mix_invalid_noti->setVisible(false);
}

void MixPanel::cancel_display_icon(int idx)
{
	int showed_circle;
	if(idx == -1)
		showed_circle = 0;
	else
		showed_circle = icon[idx]->getCircle();

	for(int i=showed_circle+1; i<3; i++)
	{
		for(int j=icon_count_per_circle[i]; j<icon_count_per_circle[i+1]; j++)
		{
			if(icon[j] != NULL)
			{
				icon_background[j]->stopAllActions();
				icon_background[j]->setVisible(false);
				icon_background[j]->removeFromParentAndCleanup(true);
				icon_background[j] = NULL;

				icon[j]->stopAllActions();
				icon[j]->setTouchable(false);
				icon[j]->setVisible(false);
				icon[j]->removeFromParentAndCleanup(true);
				icon[j] = NULL;
			}
		}
	}
	for(int i=icon_count_per_circle[showed_circle]; i<icon_count_per_circle[showed_circle+1]; i++)
	{
		if(icon[i] != NULL)
		{
			icon_background[i]->setScale(0.8f);
			icon_background[i]->setOpacity(255);

			icon[i]->setScale(0.8f);
			icon[i]->setTouchable(true);
			icon[i]->setOpacity(255);
		}
	}

	last_icon_index = icon_count_per_circle[showed_circle+1];
}

void MixPanel::reset_alchemy_icon(void)
{
	for(int j=0; j<MIX_RESULT_MAX; j++)
	{
		if(alchemy_icon[j] != NULL
		   && alchemy_icon[j]->getOpacity() == 128)
		{
			alchemy_icon[j]->removeFromParentAndCleanup(true);
			alchemy_icon[j] = NULL;
		}
	}
}

void MixPanel::add_alchemy_icon(int icon_index)
{
	if(icon_index < 5)
		return;
	for(int j=0; j<MIX_RESULT_MAX; j++)
	{
		if(alchemy_icon[j] == NULL)
			alchemy_icon[j] = MixResource::create(icon_index);
		else if(alchemy_icon[j]->getOpacity() == 128)
		{
			alchemy_icon[j]->removeFromParentAndCleanup(true);
			alchemy_icon[j] = MixResource::create(icon_index);
		}
		else
			continue;
		
		alchemy_icon[j]->setOpacity(128);
		alchemy_icon[j]->setPosition(mix_result_pos[j]);
		alchemy_icon[j]->setTouchable(true);
		addChild(alchemy_icon[j],12);
		break;
		
	}
}

void MixPanel::check_alchemy_icon_valid(void)
{
	int remain_mana = mana_bar->get_remain_value();
	for(int i=0; i<MIX_RESULT_MAX; i++)
	{
		if(alchemy_icon[i]!= NULL)
		{
			if(alchemy_icon[i]->getTouchable()
			   && remain_mana < alchemy_icon[i]->getCircle())
			{
				alchemy_icon[i]->setTouchable(false);
				alchemy_icon[i]->setColor(ccc3(255,128,128));
			}
			if(!alchemy_icon[i]->getTouchable()
			   && remain_mana >= alchemy_icon[i]->getCircle())
			{
				alchemy_icon[i]->setTouchable(true);
				alchemy_icon[i]->setColor(ccc3(255,255,255));
			}
		}
	}
}

void MixPanel::makeIcon(int icon_index, int element_index)
{
	/* icon background */
	icon_background[icon_index] = CCSprite::create(icon_background_filename[element_index]);
	icon_background[icon_index]->setAnchorPoint(ccp(0.5f, 0.78f));
	icon_background[icon_index]->setPosition(ccp(mixBtn_pos.x + element_icon_pos[element_index].x, mixBtn_pos.y + element_icon_pos[element_index].y));
	icon_background[icon_index]->setScale(0.8f);
	icon_background[icon_index]->setRotation(-45.0f + 30.0f*element_index); //-45, -15, 15, 45 degree
	addChild(icon_background[icon_index],5);

	/* icon */
	icon[icon_index] = MixResource::create(icon_index+1);
	icon[icon_index]->setPosition(ccp(mixBtn_pos.x + element_icon_pos[element_index].x, mixBtn_pos.y + element_icon_pos[element_index].y));
	icon[icon_index]->setScale(0.8f); 
	addChild(icon[icon_index],5);
}

void MixPanel::ccTouchesBegan(CCSet *pTouches, CCEvent* pEvent) {
	CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
	Vec2 point = pTouch->getLocation();
	int touchId = pTouch->getID();
	selected_index = -1;
	select_touch_action = 0;
	select_alchemy_icon_index = -1;

	gestureDetector(pTouch, PE_TOUCH_DOWN);
	
	if(touched_id != -1)
		return;
	
	if(PE_checkClickMixBtn(&point))
	{
		PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_BUTTON_MAKE_1);
		
		touched_id = touchId;
		select_touch_action = 1;
		for(int i=0; i<4; i++)
		{
			makeIcon(i, i);
		}
		icon_count_per_circle[1] = 4;
		last_icon_index = 4;
	}
	else
	{
		for(int i=0; i<4; i++)
		{
			if(alchemy_icon[i] != NULL
			   && alchemy_icon[i]->getTouchable()
			   && alchemy_icon[i]->boundingBox().containsPoint(point))
			{
				select_alchemy_icon_index = i;
				touched_id = touchId;
				mana_bar->change_pre_bar(-alchemy_icon[select_alchemy_icon_index]->getCircle());
				break;
			}
		}
	}

	return;
}


void MixPanel::ccTouchesMoved(CCSet *pTouches, CCEvent* pEvent) {
	CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    Vec2 point;
    CCSetIterator iter;
    bool selected_touch = false;
	int i, j;
	int left_right_flag = 0;
	
	gestureDetector(pTouch, PE_TOUCH_MOVE);
	
	if(touched_id == -1)
		return;

    for(iter = pTouches->begin(); iter != pTouches->end(); ++iter)
    {
    	pTouch = (CCTouch *)(*iter);
    	if(touched_id == pTouch->getID())
    	{
	   		selected_touch = true;
	   		break;
    	}
    }

    if(!selected_touch)
    	return;

	pTouch = (CCTouch*)pTouches->anyObject();
    point = pTouch->getLocation();

	if(select_alchemy_icon_index != -1)
	{
		alchemy_icon[select_alchemy_icon_index]->setPosition(point);
		mField->peTouchMoveFromMix(pTouch, alchemy_icon[select_alchemy_icon_index]);
		
	}
	else if(select_touch_action == 1)
	{
		for(i=last_icon_index-1; i >=0 ; i--)
		{
			if(icon[i] != NULL
			   && icon[i]->getTouchable()
			   && icon[i]->boundingBox().containsPoint(point)
			   && selected_index != i)
			{
				int make_icon[4];
				int make_background[4];
				int icon_index = icon[i]->getIndex();
				int icon_circle = icon[i]->getCircle();
				int cand_count = 0;
				Vec2 select_icon_pos = icon[i]->getPosition();
				
				PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_BUTTON_MAKE_2);
				
				if(icon_circle > 1)
				{
					add_alchemy_icon(icon_index);
					con_bar->change_pre_bar(-icon_circle);
				}
				
				/* cancel icon */
				if(selected_index > i)
				{
					cancel_display_icon(i);
					con_bar->change_pre_bar(0);
					selected_index = i;
					return;
				}

				/* select icon */
				selected_index = i;
				circle_index[icon_circle] = icon_index;
				if(select_icon_pos.x < 540)
					left_right_flag = 0;
				else
					left_right_flag = 1;

				for(j=0; j<4; j++)
				{
					if(Alchemy::resource_table[icon_index].make_candidate[j] != 0)
					{
						make_icon[cand_count] = Alchemy::resource_table[icon_index].make_candidate[j];
						make_background[cand_count] = j;
						cand_count++;
					}
				}

				for(int j=0; j<cand_count; j++)
				{
					/* icon background */
					icon_background[last_icon_index+j] = CCSprite::create(icon_background_filename[make_background[j]]);
					icon_background[last_icon_index+j]->setAnchorPoint(ccp(0.5f, 0.78f));
					icon_background[last_icon_index+j]->setPosition(ccp(
						select_icon_pos.x 
						+ alchemy_icon_pos[icon_pos_index[cand_count-1][left_right_flag][j]].x, 
						select_icon_pos.y 
						+ alchemy_icon_pos[icon_pos_index[cand_count-1][left_right_flag][j]].y) );
					icon_background[last_icon_index+j]->setScale(0.8f);
					icon_background[last_icon_index+j]->setRotation(
						alchemy_icon_angle[icon_pos_index[cand_count-1][left_right_flag][j]] ); //-45, -15, 15, 45 degree
					addChild(icon_background[last_icon_index+j], 5-icon_circle);

					/* icon */
					icon[last_icon_index+j] = MixResource::create(make_icon[j]);
					addChild(icon[last_icon_index+j], 5-icon_circle);
					icon[last_icon_index+j]->setPosition(ccp(
						select_icon_pos.x 
						+ alchemy_icon_pos[icon_pos_index[cand_count-1][left_right_flag][j]].x, 
						select_icon_pos.y 
						+ alchemy_icon_pos[icon_pos_index[cand_count-1][left_right_flag][j]].y) );
					icon[last_icon_index+j]->setScale(0.8f);

					if(con_bar->get_remain_value() < icon_circle+1)
					{
						icon[last_icon_index+j]->setOpacity(126);
						icon[last_icon_index+j]->setColor(ccc3(255,128,128));
						icon_background[last_icon_index+j]->setOpacity(126);
						icon_background[last_icon_index+j]->setColor(ccc3(255,128,128));
						icon[last_icon_index+j]->setTouchable(false);
					}	
				}
			
				icon_count_per_circle[icon_circle+1] = icon_count_per_circle[icon_circle] + cand_count;
				last_icon_index = icon_count_per_circle[icon_circle+1];
			
				if(icon_circle > 0)
				{
					/* change icons on same circle with selected icon */
					for(int j=icon_count_per_circle[icon_circle-1]; j<icon_count_per_circle[icon_circle]; j++ )
					{
						if(i==j)
						{
							icon_background[j]->setScale(1.0f);
							icon_background[j]->setZOrder(5-icon_circle);

							icon[j]->setScale(1.0f);
							icon[j]->setZOrder(5-icon_circle);
						}
						else
						{
							icon_background[j]->setOpacity(128);
							icon_background[j]->setZOrder(0);

							icon[j]->setTouchable(false);
							icon[j]->setOpacity(128);
							icon[j]->setZOrder(0);	
						}
					}
				}
				return;
			}
		}

		if(PE_checkClickMixBtn(&point) && selected_index != -1)
		{
			reset_alchemy_icon();
			cancel_display_icon(-1);
			selected_index = -1;
		}
	}
}

void MixPanel::ccTouchesEnded(CCSet *pTouches, CCEvent* pEvent) {
	CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
	
	gestureDetector(pTouch, PE_TOUCH_UP);
	
	if(touched_id != pTouch->getID())
		return;

	if(select_alchemy_icon_index != -1)
	{
		if(mField->peTouchEndFromMix(pTouch, alchemy_icon[select_alchemy_icon_index]))
		{
			PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_SIT_FIRE);
			mana_bar->change_result_bar(-alchemy_icon[select_alchemy_icon_index]->getCircle());
			
			alchemy_icon[select_alchemy_icon_index]->setVisible(false);
			alchemy_icon[select_alchemy_icon_index]->setTouchable(false);
			alchemy_icon[select_alchemy_icon_index] = NULL;
		}
		else
		{
			if(alchemy_icon[select_alchemy_icon_index] != NULL)
				alchemy_icon[select_alchemy_icon_index]->setPosition(mix_result_pos[select_alchemy_icon_index]);
			mana_bar->change_result_bar(0);
		}
	}
	else
	{
		for(int j=0; j<MIX_RESULT_MAX; j++)
		{
			if(alchemy_icon[j] != NULL
			   && alchemy_icon[j]->getOpacity() == 128)
			{
				PESoundEffect::sharedPESoundEffect()->PE_play(PESoundEffect::SE_CHAREC);
				alchemy_icon[j]->setOpacity(255);
				previous_selected_index = alchemy_icon[j]->getIndex();
				con_bar->change_result_bar(-alchemy_icon[j]->getCircle());
				
				break;
			}
		}
	}
	check_alchemy_icon_valid();

	resetPanel();
	touched_id = -1;
}

/* double tap listener */
void MixPanel::onDoubleTap(Vec2 pos)
{
	double_tap_called = true;
	if(PE_checkClickMixBtn(&pos))
	{
		if(previous_selected_index != -1)
		{
			if(con_bar->get_remain_value() >= Alchemy::resource_table[previous_selected_index].circle)
				add_alchemy_icon(previous_selected_index);
		}
	}
	else
	{
		for(int i=0; i<4; i++)
		{
			if(alchemy_icon[i] != NULL
			   && alchemy_icon[i]->boundingBox().containsPoint(pos))
			{
				alchemy_icon[i]->removeFromParentAndCleanup(true);
				alchemy_icon[i] = NULL;
				
			}
		}
	}
}

void MixPanel::decreaseDoorLife(int num)
{
	if(send_fail_flag)
		return;

	for(int i=0; i<num; i++)
	{
		doorLifeCount--;
		doorLife[doorLifeCount]->getAnimation()->playWithIndex(1, -1, -1, 0, 0);

		if(doorLifeCount == 0)
		{
			scheduleOnce(schedule_selector(MixPanel::sendFail), 0.5f);
			send_fail_flag = true;
			break;
		}
	}
}

void MixPanel::sendFail(float in)
{
	char buf[5];
	sprintf(buf, "%d", POPUP_FAIL);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("scene_popup", popParam);
}

void MixPanel::sendPass(void)
{
	char buf[5];
	sprintf(buf, "%d", POPUP_SUCCESS+doorLifeCount*10);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("scene_popup", popParam);
}
