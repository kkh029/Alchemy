//
//  Glass.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1202	Glass	2	20s	1	10	-	Ground	접촉		접촉한 지상 몬스터에게 초당 20의 데미지. 공격받지 않음	1103	1104
//

#include "Glass.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	0
#define LOOP			-1
#define TWEEN_EASING_MAX_INDEX 2

/* OPTION */ 
#define LIFE_PERIOD 20000 //milisecond
#define AP 10
#define ATTACK_PERIOD 1000

Glass::Glass(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_ap = AP;
	
	ap_up = false;
	speed_up = false;
	
	CCTime::gettimeofdayCocos2d(&life_time[TIME_START], NULL);
	CCTime::gettimeofdayCocos2d(&life_time[TIME_END], NULL);
	CCTime::gettimeofdayCocos2d(&attack_time[TIME_START], NULL);
	CCTime::gettimeofdayCocos2d(&attack_time[TIME_END], NULL);
	attack_time[TIME_START].tv_sec -= 2;

	x_pos_offset = 0.0f;
	y_pos_offset = 15.0f;
}

Glass::~Glass()
{}

Alchemy* Glass::create(PEObject* obj) 
{
	Glass* pGlass = new Glass(obj->PE_getResourceIndex());

	return pGlass;
}

void Glass::PE_initAnimation()
{
	CCArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(ccp(0.5f, 0.0f));
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
}



bool Glass::PE_update(unsigned int flag) {
	double diffTime;
	Vec2 index = getPosIndex();
	Vec2 tower_pos = getPosition();
	CCRect tower_box = boundingBox();
	int idx_x = index.x;
	int idx_y = index.y;

	CCTime::gettimeofdayCocos2d(&attack_time[TIME_END], NULL);
	diffTime = CCTime::timersubCocos2d(
									   &attack_time[TIME_START],
									   &attack_time[TIME_END] );
	
	if(diffTime > ATTACK_PERIOD)
	{
		CCTime::gettimeofdayCocos2d(&attack_time[TIME_START], NULL);
		for(int y=idx_y-1; y<idx_y+2; y++)
		{
			if(y<0 || y>ROW_NUM-1) continue;
				
			int monster_num = m_pCollision->m_monsters_matrix[idx_x].size();
			if(monster_num>0)
			{
				for(int i=0; i<monster_num; i++)
				{
					Monster* obj;
					obj = m_pCollision->m_monsters_matrix[idx_x][i];
					if(obj->getType() == MONSTER_TYPE_WALKER
					   && tower_box.intersectsRect(obj->boundingBox()))
					{
						obj->Hit(m_ap);
					}
				}
			}
		}
	}
	
	CCTime::gettimeofdayCocos2d(&life_time[TIME_END], NULL);
	diffTime = CCTime::timersubCocos2d(
									   &life_time[TIME_START],
									   &life_time[TIME_END] );
	
	if(diffTime > LIFE_PERIOD)
	{
		setVisible(false);
		return false;
	}
	else
		return true;
}
