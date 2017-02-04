//
//  Flame.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1204	Flame	2	20	2	10	-	Tower	발사체		전방 몬스터에게 발사체로 공격	1103	1103
//

#include "Flame.h"
#include "WindTalisman.h"
#include "WaterTalisman.h"
#include "EarthTalisman.h"
#include "FireTalisman.h"
#include "../../Layer/PEBoardPos.h"

#define DEFAULT_INDEX	1
#define ATTACT_INDEX	2
#define LOOP			-1

#define STAY 0
#define ATTACK 1

#define AP 10
#define HP 20

#define	BULLET_FIRE_SPEED 120  //frame count
#define BATCH_BULLET_TAG 1

Flame::Flame(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	isAttack = false;
	m_hp = HP;
	m_max_hp = HP;
	m_ap = AP;
	
	ap_up = false;
	speed_up = false;
	hp_up = false;
	cure = false;
	
	y_pos_offset = 20.0f;

	/* bullet move size */
	m_winSize = CCDirector::sharedDirector()->getWinSize();
}

Flame::~Flame()
{}

Alchemy* Flame::create(PEObject* obj) 
{
	Flame* pFlame = new Flame(obj->PE_getResourceIndex());
    return pFlame;
}

void Flame::PE_initAnimation()
{
	CCArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(ccp(0.5f, 0.0f));
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
    
    batch_bullet = CCSpriteBatchNode::create("Alchemy/Flame/FlameBullet.png", 5);
    addChild(batch_bullet);
    
    batch_fire = CCSpriteBatchNode::create("fire.png", 5);
    addChild(batch_fire);
}

bool Flame::PE_update(unsigned int flag) {
	CCArmatureAnimation* ani = getAnimation();
	int attack = 0;
	
	if( ((flag) & 0x1) != ap_up)
	{
		if(!ap_up)
		{
			ap_up = true;
			m_ap = AP*FireTalisman::POWER_UP;
		}
		else
		{
			ap_up = false;
			m_ap = AP;
		}
		PRINT_LOG("[AP] %d", m_ap);
	}
	if( ((flag>>1) & 0x1) != cure)
	{
		if(!cure)
		{
			cure = true;
			PE_cure(true);
		}
		else
		{
			cure = false;
		}
		PRINT_LOG("[Cure] %s", (cure)?"ON":"OFF");
	}
	if( (flag>>2 & 0x1) != speed_up)
	{
		if(!speed_up)
		{
			speed_up = true;
			ani->setSpeedScale(WindTalisman::SPEED_UP);
		}
		else
		{
			speed_up = false;
			ani->setSpeedScale(1.0f);
		}
		PRINT_LOG("[Speed] %f", ani->getSpeedScale());
	}
	if( (flag>>3 & 0x1) != hp_up)
	{
		if(!hp_up)
		{
			hp_up = true;
			m_hp += HP*EarthTalisman::MAX_HP_UP;
			m_max_hp += HP*EarthTalisman::MAX_HP_UP;
		}
		else
		{
			hp_up = false;
			m_max_hp -= HP*EarthTalisman::MAX_HP_UP;
			m_hp = (m_hp>m_max_hp)?m_max_hp:m_hp;
		}
		PRINT_LOG("[Max HP] %d", m_max_hp);
	}

	int field_index_x = getPosXIndex();
	for(int index_x=field_index_x-1; index_x<field_index_x+2; index_x++)
	{
		if(index_x >= COL_NUM || index_x<0)
			continue;
		int size = m_pCollision->m_monsters_matrix[index_x].size();
		if(size == 0)
			continue;

		Monster* obj;
		for(int j=0; j<size; j++)
		{
			obj = m_pCollision->m_monsters_matrix[index_x][j];
			Vec2 obj_index = PEBoardPos::getInstance()->getPosIndex(obj->getPosition());
			if(obj_index.y <= getPosYIndex()+2 && obj_index.y >= getPosYIndex())
			{
				attack = 1;
			}
		}
	}
	
	if(isAttack != attack)
	{
		isAttack = attack;
		if(isAttack)
		{
			FireBullet();
			bullet_time_count = 0;
			bullet_time_last = 0;
			ani->playWithIndex(ATTACT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
		}
		else
			ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
	}
	
	if(isAttack)
	{
		int bullet_time_current = ani->getCurrentFrameIndex();
		/* fire bullet */
		if(bullet_time_current > bullet_time_last)
		{
			bullet_time_count += (bullet_time_current - bullet_time_last);
			bullet_time_last = bullet_time_current;
		}
		else
		{
			bullet_time_last = bullet_time_current;
		}

		if(bullet_time_count > BULLET_FIRE_SPEED)
		{
			FireBullet();
			bullet_time_count = 0;
		}
	}
	
	if(cure)
	{
		PE_cure(false);
	}
	return m_alive;
}


Vec2 bullet_move_table[6]=
{
	ccp(-150.0f, 250.0f),
	ccp(0.0f, 250.0f),
	ccp(150.0f, 250.0f),
	ccp(-140.0f, 110.0f),
	ccp(0.0f, 100.0f),
	ccp(140.0f, 110.0f),
};

int bullet_index[6][2]=
{
	{-1,2},
	{ 0,2},
	{ 1,2},
	{-1,1},
	{ 0,1},
	{ 1,1},
};


float bullet_rotation[6] =
{
	-30.963760,
	0.0,
	30.963757,
	-51.842773,
	0.0,
	51.842773
};

CCSprite* Flame::FireBullet()
{

	Size tower_size = getContentSize();
	Vec2 tower_pos = getPosition();
    CCRect rect;
    rect.origin = ccp(0,0);
    rect.size = ccp(33,116);
	CCSprite* pBullet[6];
	
	for(int i=0; i<6; i++)
	{
		if(m_pos_index.x == 0 && (i==0||i==3))
			continue;
		if(m_pos_index.x == COL_NUM-1 && (i==2||i==5))
			continue;

        pBullet[i] = CCSprite::createWithTexture(batch_bullet->getTexture());
		batch_bullet->addChild(pBullet[i]);
		pBullet[i]->setPosition(ccp(0,50));
		pBullet[i]->setScale(1.5f);
		pBullet[i]->setRotation( bullet_rotation[i]);

		CCArray* array = CCArray::create(CCInteger::create(i), pBullet[i], NULL);
		CCCallFuncO* pCallFuncN = CCCallFuncO::create(this, callfuncO_selector(Flame::OnEndOfBullet), array);
		CCActionInterval* wait = CCDelayTime::create(0.05);
		CCMoveBy* pMoveBy = CCMoveBy::create(0.3f, bullet_move_table[i]);
		pBullet[i]->runAction(CCSequence::create(pMoveBy, wait, pCallFuncN, NULL));
	}

	return NULL;
}

void Flame::OnEndOfBullet(CCObject* object) {
	CCArray *pParam=(CCArray*)object;
	CCInteger* pbullet_index = (CCInteger*)pParam->objectAtIndex(0);
	int bullut_index = pbullet_index->getValue();
	CCSprite* bullet = (CCSprite*)pParam->objectAtIndex(1);
	CCRect bullet_rect 
		= PEBoardPos::getInstance()->getRectByIndex(ccp(getPosIndex().x + bullet_index[bullut_index][0],getPosIndex().y + bullet_index[bullut_index][1]));
	

    CCParticleFire* m_emitter = CCParticleFire::create();
    m_emitter->retain();
    m_emitter->setTexture(batch_fire->getTexture());
    m_emitter->setPosition( bullet->getPosition());
    addChild(m_emitter);
    
    CCCallFuncO* pCallFuncN = CCCallFuncO::create(this, callfuncO_selector(Flame::OnEndOfFire), m_emitter);
    CCActionInterval* wait = CCDelayTime::create(0.5);
    m_emitter->runAction(CCSequence::create(wait, pCallFuncN, NULL));

    bullet->setVisible(false);
    bullet->removeFromParent();
    
	int field_index_x = getPosXIndex();
	for(int index_x = field_index_x-1; index_x < field_index_x+2; index_x++)
	{
		if(index_x >= COL_NUM || index_x<0)
			continue;
		int size = m_pCollision->m_monsters_matrix[index_x].size();
		if(size == 0)
			continue;
		Monster* obj;
		for(int j=0; j<size; j++)
		{
			obj = m_pCollision->m_monsters_matrix[index_x][j];

			CCRect objBox = obj->boundingBox();
			Vec2 tower_pos = getPosition();

			if(bullet_rect.intersectsRect(objBox))
			{
				obj->Hit(m_ap);
			}
			
		}
	}
}

void Flame::OnEndOfFire(CCObject* object) {
    CCParticleFire* par = (CCParticleFire*)object;
    par->stopSystem();
}
