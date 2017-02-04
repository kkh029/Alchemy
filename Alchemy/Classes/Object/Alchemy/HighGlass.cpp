//
//  HighGlass.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1308	AdvancedGlass	3	30s	1	15	-	Ground	접촉		접촉한 지상 몬스터에게 초당 30의 데미지. 공격받지 않음.	1103	1208
//

#include "HighGlass.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	0
#define LOOP			-1
#define TWEEN_EASING_MAX_INDEX 2

/* OPTION */
#define LIFE_PERIOD 30000 //milisecond
#define AP 30
#define ATTACK_PERIOD 1000


HighGlass::HighGlass(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_ap = AP;
	
	ap_up = false;
	speed_up = false;
	
	gettimeofday(&life_time[TIME_START], NULL);
	gettimeofday(&life_time[TIME_END], NULL);
	gettimeofday(&attack_time[TIME_START], NULL);
	gettimeofday(&attack_time[TIME_END], NULL);
	attack_time[TIME_START].tv_sec -= 2;
	
	x_pos_offset = 0.0f;
	y_pos_offset = 15.0f;
}

HighGlass::~HighGlass()
{}

Alchemy* HighGlass::create(PEObject* obj) 
{
	HighGlass* pHighGlass = new HighGlass(obj->PE_getResourceIndex());

	return pHighGlass;
}

void HighGlass::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();

    ani->playWithIndex(DEFAULT_INDEX, -1, -1);
}


bool HighGlass::PE_update(unsigned int flag) {
	long diffTime;
	Vec2 index = getPosIndex();
	Vec2 tower_pos = getPosition();
	Rect tower_box = getBoundingBox();
	int idx_x = index.x;
	int idx_y = index.y;

	gettimeofday(&attack_time[TIME_END], NULL);
    diffTime = (attack_time[TIME_END].tv_sec - attack_time[TIME_START].tv_sec)*1000 + (attack_time[TIME_END].tv_usec - attack_time[TIME_START].tv_usec)/1000 ;
    
	
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
					if(obj->getType() == MONSTER_TYPE_WALKER
					  && tower_box.intersectsRect(obj->getBoundingBox()))
					{
						obj->Hit(m_ap);
					}
				}
			}
		}
	}
	
	gettimeofday(&life_time[TIME_END], NULL);
	diffTime = (life_time[TIME_END].tv_sec - life_time[TIME_START].tv_sec)*1000 + (life_time[TIME_END].tv_usec - life_time[TIME_START].tv_usec)/1000 ;
	
	if(diffTime > LIFE_PERIOD)
	{
		setVisible(false);
		return false;
	}
	else
		return true;
}
