#include "Field.h"
#include "../Object/Monster.h"
#include "../Object/PEObject.h"

#define FIELD_BOUNDARY_Y	435.0f
#define CALC_ENEMY_POS(x, y) ccp(130.0f + x * 164.0f, BOARD_HEIGHT_EDGE + y * 148.0f)

enum FIELD_Zorder
{
	FIELD_Z_BACKGROUND = 0,
	FIELD_Z_UI,
};

bool Field::init() {
	if(CCLayer::init() == false) {
		return false;
	}

	autorelease();
	m_move_to_y = 0;
	m_items.clear();

	m_pBackground = CCSprite::create("Layer/lBackground.png");
	m_pBackground->setPosition(ccp(0.0f, 100.0f));
	m_pBackground->setAnchorPoint(ccp(0.0f, 0.0f));
	background_size = m_pBackground->getContentSize();
	addChild(m_pBackground, FIELD_Z_BACKGROUND);

	PETime::init();
    
    box = CCDrawNode::create();
    box->init();
    addChild(box, FIELD_Z_UI);

	broadPos = PEBoardPos::getInstance();
	broadPos->init();
	m_winSize = CCDirector::sharedDirector()->getWinSize();
	m_monsterSpawnTime = PETime::GetTime();
	
	m_pot = Pot::create();
	m_pot->setPosition(ccp(540.0f, 1539.0f));
	m_pBackground->addChild(m_pot);

	/* Door Sprite */
	CCSprite* door = CCSprite::create("Layer/lDoor.png");
	door->setAnchorPoint(ccp(0.0f, 1.0f));
	door->setPosition(ccp(background_size.width/2-195, 239.0f));
	m_pBackground->addChild(door);
	
	for(int x=0; x<COL_NUM; x++)
	{
		for(int y=0; y<ROW_NUM; y++)
		{
			m_pBoard[x][y] = NULL;
			talisman_flag[x][y] = 0;
		}
	}

	m_pCollision = PE_Collision::getPE_Collision();
	m_pCollision->PE_reset();

	send_success_flag = false;
	
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
																			"Monster/MonsterBall/MonsterBall0.png",
																			"Monster/MonsterBall/MonsterBall0.plist",
																			"Monster/MonsterBall/MonsterBall.ExportJson");
	
	for(int x=0; x<COL_NUM; ++x){
		for(int y=0; y< ROW_NUM; ++y) {
			m_pBoard[x][y] = NULL;
		}
	}
	
	for(int i=0; i<6; i++)
		rand_num_count[i] = 0;
    
	scheduleUpdate();

	return true;
}

void Field::update(float dt) {
	int head_pos_y[COL_NUM];
	memset(head_pos_y, 1920, sizeof(float)*COL_NUM);
	int remainderMonster = 0;

	m_pot->color_change();
	m_pCollision->PE_updateMatrix();
	
	for(int i=0; i<COL_NUM; i++) {
		int monster_idx = m_pCollision->m_monsters_matrix[i].size();
		remainderMonster += monster_idx;
		while(monster_idx--)
		{
			Monster* pMonster = m_pCollision->m_monsters_matrix[i][monster_idx];
			pMonster->setMode(Monster::MONSTER_MOVE);
			this->reorderChild(pMonster, 2000 - (int)pMonster->getPositionY());
			
			for(int j=0; j<ROW_NUM; j++) {
				if(m_pBoard[i][j] != NULL
				   && m_pBoard[i][j]->getBlock() == true)
				{
					float range = pMonster->getPositionY() - m_pBoard[i][j]->getPositionY();
					if(range > 0 && range < pMonster->getRange()) 
					{
						pMonster->setMode(Monster::MONSTER_ATTACK);
						pMonster->Attack(m_pBoard[i][j]);
					}
				}
			}
			pMonster->PE_update(0);
		}
	}
	
	for(int x=0; x<COL_NUM; x++) {
		for(int y=0; y<ROW_NUM; y++) {
			if(m_pBoard[x][y] != NULL)
			{
				int index = m_pBoard[x][y]->getIndex();
				
				if(!m_pBoard[x][y]->PE_update(talisman_flag[x][y]))
				{
					/**
					 * check talisman tower
					 * FireTalisman(17) ~ EarthTalisman(20)
					 **/
					if(index >= 17 &&  index <= 20)
					{
						for(int i=-1; i<2; i++)
						{
							for(int j=-1; j<2; j++)
							{
								int idx_x = x + i;
								int idx_y = y + j;
								
								if(idx_x < 0)
									idx_x = 0;
								else if(idx_x > COL_NUM)
									idx_x = COL_NUM;
								
								if(idx_y < 0)
									idx_y = 0;
								else if(idx_y > ROW_NUM)
									idx_y = ROW_NUM;
								
								talisman_flag[idx_x][idx_y] = talisman_flag[idx_x][idx_y] & ~(0x1<<(index - 17));
							}
						}
					}
					m_pBoard[x][y] = NULL;
				}
			}
		}
	}
}

void Field::removeBall(CCObject* pObject)
{
	Monster* pMonster = (Monster*)pObject;
	pMonster->ball->stopAllActions();
}

void Field::createMonster(CCObject* pObject)
{
	Monster* pMonster = (Monster*)pObject;
	pMonster->getAnimation()->playWithIndex(0, -1, -1, -1, 10000);
	pMonster->setVisible(true);
	pMonster->move(1.0f);
	m_pCollision->addMonster(pMonster);
	
	CCDelayTime* pDelayTime = CCDelayTime::create(0.5f);
	CCCallFuncO* pCallFuncO =  CCCallFuncO::create(this, callfuncO_selector(Field::removeBall), pObject);
	pMonster->ball->runAction(CCSequence::create(pDelayTime, pCallFuncO, NULL));
}

void Field::openBall(CCObject* pObject)
{
	Monster* pMonster = (Monster*)pObject;
	pMonster->ball->getAnimation()->playWithIndex(2, -1, -1, 0, 0);
	
	CCDelayTime* pDelayTime = CCDelayTime::create(0.5f);
	CCCallFuncO* pCallFuncO =  CCCallFuncO::create(this, callfuncO_selector(Field::createMonster), pObject);
	pMonster->ball->runAction(CCSequence::create(pDelayTime, pCallFuncO, NULL));
}

void Field::SpawnMonsters(int monster_index, float speed_scale)
{
	int x_index; 
	int rand_index = rand()%6;

	x_index = rand_index;
	if(rand_index > 0)
		x_index = (rand_num_count[rand_index] > rand_num_count[rand_index-1])?(rand_index-1):rand_index;

	if(rand_index < 5)
		x_index = (rand_num_count[x_index] > rand_num_count[rand_index+1])?(rand_index+1):x_index;

	rand_num_count[x_index]++;

	float ball_duration = 1.5f;
	Vec2 pos = CALC_ENEMY_POS(x_index, 7);
	
	// create Monster object
    Monster* pMonster = Monster::create(monster_index);
	pMonster->setPosIndex(broadPos->getPosIndex(CALC_ENEMY_POS(x_index, 7)));
	pMonster->setVisible(false);
	pMonster->setStageLevel(speed_scale);
	pMonster->setPosition(pos);
	
	// create Ball object
	pMonster->ball  = CCArmature::create("MonsterBall");
	pMonster->ball->getAnimation()->playWithIndex(0, -1, -1, -1, 10000);
	pMonster->ball->setPosition(ccp(background_size.width/2,1800.f));
	
	ccBezierConfig bezierConfig;
	if(background_size.width/2 > pos.x)
	{
		bezierConfig.controlPoint_1 = ccp((background_size.width/2*2 + pos.x)/3, 1900.0f);
		bezierConfig.controlPoint_2 = ccp((background_size.width/2 + pos.x*2)/3, 1900.0f);
	}
	else
	{
		bezierConfig.controlPoint_1 = ccp((background_size.width/2*2 + pos.x)/3, 1900.0f);
		bezierConfig.controlPoint_2 = ccp((background_size.width/2 + pos.x*2)/3, 1900.0f);
	}
	bezierConfig.endPosition = pos;
	CCBezierTo* pBezier = CCBezierTo::create(ball_duration, bezierConfig);
	CCCallFuncO* pCallFuncO =  CCCallFuncO::create(this, callfuncO_selector(Field::openBall), (CCObject*)pMonster);
	pMonster->ball->runAction(CCSequence::create(pBezier, pCallFuncO, NULL));
	
	addChild(pMonster);
	addChild(pMonster->ball);
}

bool Field::draw_noti_box(CCTouch *pTouch, int index)
{
	bool ret = false;
    if(broadPos->setTouchPos(pTouch))
    {
		Vec2 *boxRound;
		Vec2 *boxIdx;
		ccColor4F c4;
        
        boxIdx = broadPos->getBoxIndex();
        if(m_pBoard[(int)boxIdx->x][(int)boxIdx->y] != NULL)
        {
			c4 = ccc4f(1,0,0,0.3);
        }
		else
		{
			c4 = ccc4f(1,1,1,0.3);
			ret = true;
		}

        boxRound = broadPos->getCrossBoxVertex(ROW);
        box->drawPolygon(boxRound, 4, c4, 0, c4);
        
        boxRound = broadPos->getCrossBoxVertex(COL);
        box->drawPolygon(boxRound, 4, c4, 0, c4);

		if(index >= 17 &&  index <= 20)
		{
			if(ret)
				c4 = ccc4f(0.55,0.85,0.15, 0.3);

			boxRound = broadPos->getTalismanArea();
			box->drawPolygon(boxRound, 4, c4, 0, c4);
		}

        CHECK_GL_ERROR_DEBUG();
    }

	return ret;
}

bool Field::peTouchMoveFromMix(CCTouch* pTouch, PEObject* object)
{
	mTouch = pTouch;
	box->clear();

	if(object == NULL)
	{
		return false;
	}
	else
	{
		return draw_noti_box(mTouch, object->getIndex());
	}
}

bool Field::peTouchEndFromMix(CCTouch* pTouch, PEObject* object)
{
	Vec2 *boxIdx;
	int x,y;
	box->clear();
	
	// check existance of tower on the board
	if(object == NULL || broadPos->setTouchPos(pTouch) == false)
	{
		return false;
	}
	else
	{
		boxIdx = broadPos->getBoxIndex();
		x = (int)boxIdx->x;
		y = (int)boxIdx->y;
		if(m_pBoard[x][y] != NULL)
			return false;
	}
	
	m_pBoard[x][y] = Alchemy::create(object);

	m_pBoard[x][y]->setPosition(
		broadPos->getBoxPos()->x + m_pBoard[x][y]->x_pos_offset, 
		broadPos->getBoxPos()->y + m_pBoard[x][y]->y_pos_offset);
	m_pBoard[x][y]->setPosIndex(*boxIdx);
	
	this->addChild(m_pBoard[x][y]);
	switch(m_pBoard[x][y]->getType())
	{
	case MAGIC_AIR:
		this->reorderChild(m_pBoard[x][y], 2000);
		break;
	case MAGIC_GND:
		this->reorderChild(m_pBoard[x][y], 0);
		break;
	case MAGIC_INS:
		this->reorderChild(m_pBoard[x][y], 2000);
		break;
	default:
		this->reorderChild(m_pBoard[x][y], 2000 - (int)m_pBoard[x][y]->getPositionY());
		break;
	}
	
	
	/**
	 * check talisman tower
	 * FireTalisman(17) ~ EarthTalisman(20)
	 **/
	if(object->getIndex() >= 17 &&  object->getIndex() <= 20)
	{
		for(int i=-1; i<2; i++)
		{
			for(int j=-1; j<2; j++)
			{
				int idx_x = x + i;
				int idx_y = y + j;
				
				if(idx_x < 0)
					idx_x = 0;
				else if(idx_x > COL_NUM)
					idx_x = COL_NUM;
				
				if(idx_y < 0)
					idx_y = 0;
				else if(idx_y > ROW_NUM)
					idx_y = ROW_NUM;
				
				talisman_flag[idx_x][idx_y] = talisman_flag[idx_x][idx_y] | (0x1<<(object->getIndex() - 17));
			}
		}
	}
	return true;
}

void Field::onExit()
{
	CCLog("Field - on Exit()");
	this->removeFromParentAndCleanup(true);
}


Pot::Pot()
:CCNode()
{
}

Pot::~Pot()
{
}

Pot* Pot::create()
{
	Pot* p_Pot = new Pot();
	p_Pot->init();
	p_Pot->autorelease();
	
	return p_Pot;
}

bool Pot::init(void)
{
	/* Pot animation Init */
	magic_circle = CCSprite::create("Layer/lPod/lMagicCircle.png");
	addChild(magic_circle);
	
	magic_circle_back = CCSprite::create("Layer/lPod/lMagicCircleBack.png");
	addChild(magic_circle_back);
	
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
                                                                            "Layer/lPod/lPot0.png", "Layer/lPod/lPot0.plist", "Layer/lPod/lPot.ExportJson");
	pot = CCArmature::create("lPot");
	pot->setAnchorPoint(ccp(0.5f, 0.0f));
	pot->setPosition(0, -50.0f);
 	pot->getAnimation()->playWithIndex(0, -1, -1, -1, 10000);
	addChild(pot);
	
	r = 134;
	g = 57;
	b = 206;
	magic_circle_back->setColor(ccc3(r,g,b));
	goto_bright = 1;
	change_index = 0;
	
	return true;
}

void Pot::color_change(void)
{
	if(goto_bright)
	{
		switch(change_index)
		{
		case 0:
			r += 1;
			change_index++;
			break;
		case 1:
			g += 1;
			change_index++;
			break;
		case 2:
			b += 1;
			change_index = 0;
			break;
		default:
			break;
		}
		if(b>=255)
			goto_bright = 0;
	}
	else 
	{
		switch(change_index)
		{
		case 0:
			r -= 1;
			change_index++;
			break;
		case 1:
			g -= 1;
			change_index++;
			break;
		case 2:
			b -= 1;
			change_index = 0;
			break;
		default:
			break;
		}
		if(g<=8)
			goto_bright = 1;
	}

	magic_circle_back->setColor(ccc3(r,g,b));
}
