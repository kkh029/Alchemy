//
//  Steam.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1203	Steam	2	20s	1	10	-	Air	접촉		접촉한 공중 몬스터에게 초당 20의 데미지. 공격받지 않음	1103	1101	3
//

#include "Steam.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	1
#define FADE_IN_INDEX	0
#define FADE_OUT_INDEX	2
#define LOOP			-1
#define TWEEN_EASING_MAX_INDEX 10000
#define LIFE_PERIOD 20000 //milisecond
#define ATTACK_PERIOD 1000
#define AP 20

Steam::Steam(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_ap = AP;
	
}

Steam::~Steam()
{}

Alchemy* Steam::create(PEObject* obj) 
{
	Steam* pSteam = new Steam(obj->PE_getResourceIndex());

	return pSteam;
}

void Steam::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();

	gettimeofday(&life_time[TIME_START], NULL);
	gettimeofday(&life_time[TIME_END], NULL);
	gettimeofday(&attack_time[TIME_START], NULL);
	gettimeofday(&attack_time[TIME_END], NULL);
	attack_time[TIME_START].tv_sec -= 2;
	
	ani->playWithIndex(FADE_IN_INDEX, -1, -1);
	m_ani_stage = FADE_IN_INDEX;
}


bool Steam::PE_update(unsigned int flag) {
	ArmatureAnimation* ani;
	double diffTime;
	Vec2 index = getPosIndex();
	Vec2 tower_pos = getPosition();
	Rect tower_box = getBoundingBox();
	int idx_x = index.x;
	int idx_y = index.y;
	
	gettimeofday(&attack_time[TIME_END], NULL);
    diffTime = (attack_time[TIME_END].tv_sec - attack_time[TIME_START].tv_sec) * 1000 + (attack_time[TIME_END].tv_usec - attack_time[TIME_START].tv_usec) / 1000;
	
	if(diffTime > ATTACK_PERIOD)
	{
		gettimeofday(&attack_time[TIME_START], NULL);
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
					if(obj->getType() == MONSTER_TYPE_FLYER
					   && tower_box.intersectsRect(obj->getBoundingBox()))
					{
						obj->Hit(m_ap);
					}
				}
			}
		}
	}
	
	gettimeofday(&life_time[TIME_END], NULL);
    diffTime = time_interval(life_time[TIME_START], life_time[TIME_END] );
    
	ani = getAnimation();
	if(m_ani_stage == FADE_IN_INDEX && ani->getCurrentFrameIndex() == 40)
	{
		ani->playWithIndex(DEFAULT_INDEX, -1, -1);
	}
	if(diffTime > LIFE_PERIOD)
	{
		ani->playWithIndex(FADE_OUT_INDEX, -1, -1);
		return false;
	}
	
	return true;
}
