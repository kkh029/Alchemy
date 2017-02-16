//
//  Thunder.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1307	Thunder	3	-	-	80	1 sq.	-	마법			1102	1203	3
//

#include "Thunder.h"

/* ALCHEMY PARAMETER */
#define ATTACT_INDEX	1
#define FADE_IN_INDEX	0
#define FADE_OUT_INDEX	2
#define LOOP			0
#define TWEEN_EASING_MAX_INDEX 0
#define AP 80

Thunder::Thunder(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_ap = AP;
	x_pos_offset = 30.0f;
	y_pos_offset = 0.0f;
}
Thunder::~Thunder()
{}

Alchemy* Thunder::create(PEObject* obj) 
{
	Thunder* pThunder = new Thunder(obj->PE_getResourceIndex());

	return pThunder;
}

void Thunder::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();
	m_ani_stage = FADE_IN_INDEX;
	ani->playWithIndex(FADE_IN_INDEX, -1, -1);
}


bool Thunder::PE_update(unsigned int flag) {
	ArmatureAnimation* ani = getAnimation();
	int ani_index = ani->getCurrentFrameIndex();


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
			if(ani_index / 20 > 0 && ani_index % 20 == 0)
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
			if(ani_index == 80)
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
