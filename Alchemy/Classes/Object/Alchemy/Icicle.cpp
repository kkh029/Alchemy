//
//  Icicle.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1310	Icicle	3	-	-	50	1 sq.	-	마법	Slow	피격시 3초간 Slow.	1102	1206	1
//

#include "Icicle.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	0
#define LOOP			0
#define TWEEN_EASING_MAX_INDEX 0

/* OPTION */ 
#define AP 50

Icicle::Icicle(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_hp = 0;
	m_ap = AP;
}

Icicle::~Icicle()
{}

Alchemy* Icicle::create(PEObject* obj) 
{
	Icicle* pIcicle = new Icicle(obj->PE_getResourceIndex());

	return pIcicle;
}

void Icicle::PE_initAnimation()
{
	CCArmatureAnimation* ani;
	
	init(m_name.c_str());
	setScale(1.5f);
	setAnchorPoint(ccp(0.5f, 0.5f));
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
}


bool Icicle::PE_update(unsigned int flag) {
	Vec2 index = getPosIndex();
	Vec2 tower_pos = getPosition();
	CCRect tower_box = boundingBox();
	int idx_x = index.x;
	int idx_y = index.y;

	for(int y=idx_y-1; y<idx_y+2; y++)
	{
		for(int x=idx_x-1; x<idx_x+2; x++)
		{
			if(x<0 || y<0) continue;
			if(x>COL_NUM-1 || y>ROW_NUM-1) continue;
				
			int monster_num = m_pCollision->m_monsters_matrix[x].size();
			if(monster_num>0)
			{
				for(int i=0; i<monster_num; i++)
				{
					Monster* obj;
					obj = m_pCollision->m_monsters_matrix[x][i];
					if(tower_box.intersectsRect(obj->boundingBox()))
					{
						obj->Hit(m_ap);
						obj->slow(0.5, 3);
					}
				}
			}
		}
	}

	return false;
}
