//
//  Mud.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1205	Mud	2	20s	-	-	-	Ground	접촉	Slow	접촉한 지상 몬스터의 3초간 이속 50% 감소. 공격받지 않음	1102	1104	1
//

#include "Mud.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	0
//#define ATTACT_INDEX	0
//#define FADE_IN_INDEX	1
//#define FADE_OUT_INDEX	2
#define LOOP			-1
#define TWEEN_EASING_MAX_INDEX 10000
#define STAY_TIME 20000 //milisecond

/* OPTION */ 
#define STAY 0
#define ATTACK 1

#define TIME_START	0
#define TIME_END	1


Mud::Mud(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	x_pos_offset = 0.0f;
	y_pos_offset = 40.0f;
}

Mud::~Mud()
{}

Alchemy* Mud::create(PEObject* obj) 
{
	Mud* pMud = new Mud(obj->PE_getResourceIndex());

	return pMud;
}

void Mud::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();

	gettimeofday(&event_time[TIME_START], NULL);
	ani->playWithIndex(DEFAULT_INDEX, -1, -1);
}


bool Mud::PE_update(unsigned int flag) {
	double diffTime;
	Vec2 index = getPosIndex();
	Vec2 tower_pos = getPosition();
	Rect tower_box = getBoundingBox();
	int idx_x = index.x;
	int idx_y = index.y;
	
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
				if(tower_box.intersectsRect(obj->getBoundingBox())
				   && obj->getType() == MONSTER_TYPE_WALKER)
				{
					obj->slow(0.5, 3);
				}
			}
		}
	}

	gettimeofday(&event_time[TIME_END], NULL);
	diffTime = time_interval(event_time[TIME_START], event_time[TIME_END]);
	
	if(diffTime > STAY_TIME)
	{
		removeFromParent();
		return false;
	}

	return true;
}
