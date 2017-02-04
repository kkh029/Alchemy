//
//  PlainWater.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#include "PlainWater.h"
#include "WindTalisman.h"
#include "WaterTalisman.h"
#include "EarthTalisman.h"
#include "FireTalisman.h"

#define DEFAULT_INDEX	0
#define ATTACT_INDEX	1
#define LOOP			-1
#define	BULLET_SPEED 2.5f

#define STAY 0
#define ATTACK 1

#define AP 10
#define HP 40

PlainWater::PlainWater(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	isAttack = false;
	m_bulletFireTime = 0;
	m_hp = HP;
	m_max_hp = HP;
	m_ap = AP;
	
	ap_up = false;
	speed_up = false;
	hp_up = false;
	cure = false;

	/* bullet move size */
	m_winSize = CCDirector::sharedDirector()->getWinSize();
}

PlainWater::~PlainWater()
{}

Alchemy* PlainWater::create(PEObject* obj) 
{
	PlainWater* pPlainWater = new PlainWater(obj->PE_getResourceIndex());

	return pPlainWater;
}

void PlainWater::PE_initAnimation()
{
	CCArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(ccp(0.5f, 0.0f));
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
}


bool PlainWater::PE_update(unsigned int flag) {
	CCArmatureAnimation* ani = getAnimation();
	Vec2 index = getPosIndex();
	int index_x = (int)index.x;
	bool monster_appear = false;
	
	if( ((flag) & 0x1) != ap_up)
	{
		if(!ap_up)
		{
			ap_up = true;
			m_ap = AP*2;
		}
		else
		{
			ap_up = false;
			m_ap = AP;
		}
		CCLog("[AP] %d", m_ap);
	}
	if( ((flag>>1) & 0x1) != cure)
	{
		if(!cure)
		{
			cure = true;
			m_ap = AP*2;
		}
		else
		{
			cure = false;
			m_ap = AP;
		}
		CCLog("[Cure] %s", (cure)?"ON":"OFF");
	}
	if( (flag>>2 & 0x1) != speed_up)
	{
		if(!speed_up)
		{
			speed_up = true;
			ani->setSpeedScale(3.0f);
		}
		else
		{
			speed_up = false;
			ani->setSpeedScale(1.0f);
		}
		CCLog("[Speed] %f", ani->getSpeedScale());
	}
	if( (flag>>3 & 0x1) != hp_up)
	{
		if(!hp_up)
		{
			hp_up = true;
			m_hp += HP/5;
			m_max_hp += HP/5;
		}
		else
		{
			hp_up = false;
			m_max_hp -= HP/5;
			m_hp = (m_hp>m_max_hp)?m_max_hp:m_hp;
		}
		CCLog("[Max HP] %d", m_max_hp);
	}
	
    int size = m_pCollision->m_monsters_matrix[index_x].size();
    if(size > 0)
        monster_appear = true;
	
	if(isAttack != monster_appear)
	{
		isAttack = monster_appear;
		if(isAttack)
			ani->playWithIndex(ATTACT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
		else
			ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
	}

	/* 27 - animation fire index */
	if(isAttack)
	{
		if(m_bullets.size()>0)
		{
            CCSprite* pBullet = m_bullets[0];
        
            Monster* obj;
            for(int j=0; j<size; j++)
            {
                obj = m_pCollision->m_monsters_matrix[index_x][j];
                //Vec2 obj_index = PEBoardPos::getInstance()->getPosIndex(obj->getPosition());
                
                CCRect objBox = obj->boundingBox();
                Vec2 tower_pos = getPosition();
                CCRect objTargetBox =  CCRect(objBox.getMinX()-tower_pos.x, objBox.getMinY()-tower_pos.y + 60.0f, objBox.getMaxX()-tower_pos.x, objBox.getMaxY()-tower_pos.y);
                if(pBullet->boundingBox().intersectsRect(objTargetBox))
                {
                    pBullet->setVisible(false);
                    pBullet->stopAllActions();
                    obj->Hit(AP);
                    m_bullets.erase(m_bullets.begin());
                    break;
                }
            }
		}

		/* fire bullet */
		if(!fire_flag && ani->getCurrentFrameIndex() > 25)
		{
			fire_flag = true;
			m_bullets.push_back(FireBullet());
		}
		else if(fire_flag && ani->getCurrentFrameIndex() < 25)
		{
			fire_flag = false;
		}
	}
	
	return m_alive;
}

CCSprite* PlainWater::FireBullet()
{
	CCSprite* pBullet = CCSprite::create("Alchemy/waterbullet.png");
	addChild(pBullet);
	Size tower_size = getContentSize();
	Vec2 tower_pos = getPosition();
	float duration = BULLET_SPEED;
	
	pBullet->setPosition(ccp(0,103));
	
	CCCallFuncN* pCallFuncN = CCCallFuncN::create(this, callfuncN_selector(PlainWater::OnEndOfBullet));
	CCMoveBy* pMoveBy = CCMoveBy::create(duration, ccp(0.0f, m_winSize.height));
	pBullet->runAction(CCSequence::create(pMoveBy, pCallFuncN, NULL));
	
	return pBullet;
}

void PlainWater::OnEndOfBullet(CCNode* pNode) {
	m_bullets.pop_back();
    pNode->removeFromParent();
}

