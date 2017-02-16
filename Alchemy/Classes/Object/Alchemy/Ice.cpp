//
//  Ice.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1206	Ice	2	-	-	30	1 sq.	-	마법	Slow	50% 확률로 3초간 Slow.	1102	1101	1
//

#include "Ice.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	0
#define LOOP			0
#define TWEEN_EASING_MAX_INDEX 0

/* OPTION */ 
#define AP 30

Ice::Ice(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_hp = 0;
	m_ap = AP;
}

Ice::~Ice()
{}

Alchemy* Ice::create(PEObject* obj) 
{
	Ice* pIce = new Ice(obj->PE_getResourceIndex());

	return pIce;
}

void Ice::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1);
}


bool Ice::PE_update(unsigned int flag) {
	Vec2 index = getPosIndex();
	Vec2 tower_pos = getPosition();
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
					if(rand()%2 == 1)
					{
						obj->slow(0.5, 3);
					}
				}
			}
		}
	}
	return false;
}
