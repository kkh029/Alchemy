//
//  Tornado.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1209	Windpot	2	20	3	10	-	Tower	발사체		전방 몬스터에게 관통 공격	1101	1101	1
//

#include "Tornado.h"

#define DEFAULT_INDEX	0
#define ATTACT_INDEX	0
#define LOOP			-1

#define STAY 0
#define ATTACK 1

#define AP 10
#define HP 20

#define	BULLET_SPEED 5.0f


Tornado::Tornado(unsigned char index)
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
	m_winSize = Director::getInstance()->getWinSize();
}

Tornado::~Tornado()
{}

Alchemy* Tornado::create(PEObject* obj) 
{
	Tornado* pTornado = new Tornado(obj->PE_getResourceIndex());

	return pTornado;
}

void Tornado::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1);
}


bool Tornado::PE_update(unsigned int flag) {
	ArmatureAnimation* ani = getAnimation();
	Vec2 index = getPosIndex();
	Monster* obj;
	int index_x = (int)index.x;
	int attack = 0;
	
	log("ani index :%d", ani->getCurrentFrameIndex());
	
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
		log("[AP] %d", m_ap);
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
		log("[Cure] %s", (cure)?"ON":"OFF");
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
		log("[Speed] %f", ani->getSpeedScale());
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
		log("[Max HP] %d", m_max_hp);
	}
	
	for(int index_y=index.y; index_y<ROW_NUM+1; index_y++)
	{
		int size = m_pCollision->m_monsters_matrix[index_x].size();
		if(size > 0)
		{
			obj = m_pCollision->m_monsters_matrix[index_x][0];
			attack = 1;
			break;
		}
	}
	
	if(isAttack != attack)
	{
		isAttack = attack;
		if(isAttack)
			ani->playWithIndex(ATTACT_INDEX, -1, -1);
		else
			ani->playWithIndex(DEFAULT_INDEX, -1, -1);
	}
	
	/* 27 - animation fire index */
	if(isAttack)
	{
		for(int i=0; i<m_bullets.size(); i++)
		{
			CCArmature* pBullet = m_bullets[i];
			Rect objBox = obj->getBoundingBox();
			Vec2 tower_pos = getPosition();
			Rect objTargetBox =  Rect(objBox.getMinX()-tower_pos.x, objBox.getMinY()-tower_pos.y + 60.0f, objBox.getMaxX()-tower_pos.x, objBox.getMaxY()-tower_pos.y);
			
			if(pBullet->getBoundingBox().intersectsRect(objTargetBox))
			{
				obj->Hit(m_ap);
				m_bullets.erase(m_bullets.begin()+i);
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
	
	if(cure)
	{
		PE_cure(false);
	}
	return m_alive;
}

CCArmature* Tornado::FireBullet()
{
	CCArmature* pBullet  = CCArmature::create("Tornado");
	pBullet->getAnimation()->playWithIndex(DEFAULT_INDEX, -1, -1);
	pBullet->setScale(0.5);
	addChild(pBullet);
	Size tower_size = getContentSize();
	Vec2 tower_pos = getPosition();
	float duration = BULLET_SPEED;
	
	/* 110 - bullet position in animation */
	pBullet->setPosition(Vec2(0,103));
	
	CCCallFuncN* pCallFuncN = CCCallFuncN::create(this, callfuncN_selector(Tornado::OnEndOfBullet));
	CCMoveBy* pMoveBy = CCMoveBy::create(duration, Vec2(0.0f, m_winSize.height - tower_pos.y -500));
	pBullet->runAction(CCSequence::create(pMoveBy, pCallFuncN, NULL));
	
	return pBullet;
}

void Tornado::OnEndOfBullet(CCNode* pNode) {
	pNode->removeFromParent();
}
