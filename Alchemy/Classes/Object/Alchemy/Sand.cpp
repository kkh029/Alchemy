//
//  Sand.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1208	Sand	2	-	-	30	1 sq.	-	마법	Blind	50% 확률로 3초간 Blind.	1101	1104	1
//

#include "Sand.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	0
#define LOOP			0
#define TWEEN_EASING_MAX_INDEX 0

#define AP 20


Sand::Sand(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_ap = AP;
}

Sand::~Sand()
{}

Alchemy* Sand::create(PEObject* obj) 
{
	Sand* pSand= new Sand(obj->PE_getResourceIndex());

	return pSand;
}

void Sand::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1);
}


bool Sand::PE_update(unsigned int flag) {
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
				if(tower_box.intersectsRect(obj->getBoundingBox()))
				{
					obj->Hit(m_ap);
					if(rand()%2 == 1)
					{
						log("success\n");
						obj->blind(3);
					}
					else
					{
						log("fail\n");
					}
				}
			}
		}
	}
	
	return false;
}
