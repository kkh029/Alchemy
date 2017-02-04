//
//  Virus.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1301	Virus	3	30s	1	10	-	Air	접촉		접촉한 몬스터에게 초당 10의 데미지. 공격받지 않음.	1103	1201	3
//

#include "Virus.h"

/* ALCHEMY PARAMETER */
#define ATTACT_INDEX	1
#define FADE_IN_INDEX	0
#define FADE_OUT_INDEX	2
#define LOOP			-1
#define TWEEN_EASING_MAX_INDEX 10000

#define LIFE_PERIOD 30000 //milisecond
#define ATTACK_PERIOD 1000

#define AP 20

Virus::Virus(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_ap = AP;
}

Virus::~Virus()
{}

Alchemy* Virus::create(PEObject* obj) 
{
	Virus* pVirus = new Virus(obj->PE_getResourceIndex());

	return pVirus;
}

void Virus::PE_initAnimation()
{
	ArmatureAnimation* ani;

	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();

	gettimeofday(&life_time[TIME_START], NULL);
	ani->playWithIndex(FADE_IN_INDEX, -1, -1);
	m_ani_stage = FADE_IN_INDEX;
}


bool Virus::PE_update(unsigned int flag) {
	ArmatureAnimation* ani = getAnimation();
	int ani_index = ani->getCurrentFrameIndex();
	double diffTime;
	
	switch(m_ani_stage)
	{
		case FADE_IN_INDEX:
			if(ani_index == 30)
			{
				ani->playWithIndex(ATTACT_INDEX, -1, -1);
				m_ani_stage = ATTACT_INDEX;
			}
			break;
			
		case ATTACT_INDEX:
			if(ani_index == 60)
			{
				Vec2 index = getPosIndex();
				Rect tower_box = getBoundingBox();
				int idx_x = index.x;
				int idx_y = index.y;
				int monster_count = 0;
				for(int y=idx_y-1; y<idx_y+2; y++)
				{
					if(y<0 || y>ROW_NUM-1) continue;
						
					int monster_num = m_pCollision->m_monsters_matrix[idx_x].size();
					monster_count += monster_num;
					if(monster_num>0)
					{
						for(int i=0; i<monster_num; i++)
						{
							Monster* obj;
							obj = m_pCollision->m_monsters_matrix[idx_x][i];
							if(tower_box.intersectsRect(obj->getBoundingBox()))
							{
								obj->Hit(m_ap);
							}
						}
					}
				}
			}
			
			gettimeofday(&life_time[TIME_END], NULL);
            diffTime = (life_time[TIME_END].tv_sec - life_time[TIME_START].tv_sec)*1000 + (life_time[TIME_END].tv_usec - life_time[TIME_START].tv_usec)/1000;
			
			if(diffTime > LIFE_PERIOD)
			{
				ani->playWithIndex(FADE_OUT_INDEX, -1, -1);
				m_ani_stage = FADE_OUT_INDEX;
			}
			break;
			
		case FADE_OUT_INDEX:
			if(ani_index == 30)
			{
				removeFromParent();
				return false;
			}
			break;
	}
	
	return true;
}
