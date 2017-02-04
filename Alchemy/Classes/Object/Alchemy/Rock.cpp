//
//  Rock.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1210	Rock	2	100	-	-	-	Tower	-		¹ÙÀ§	1104	1104	1

//

#include "Rock.h"
#include "WindTalisman.h"
#include "WaterTalisman.h"
#include "EarthTalisman.h"
#include "FireTalisman.h"

#define DEFAULT_INDEX	0
#define LOOP			-1

#define HP 100

Rock::Rock(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_hp = HP;
	m_max_hp = HP;
	
	cure = false;
	hp_up = false;

	x_pos_offset = 0.0f;
	y_pos_offset = 50.0f;
}

Rock::~Rock()
{}

Alchemy* Rock::create(PEObject* obj) 
{
	Rock* pRock = new Rock(obj->PE_getResourceIndex());

	return pRock;
}

void Rock::PE_initAnimation()
{
	CCArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(ccp(0.5f, 0.0f));
	ani = getAnimation();
	ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
}


bool Rock::PE_update(unsigned int flag) {
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
		CCLog("[Cure] %s", (cure)?"ON":"OFF");
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
		CCLog("[Max HP] %d", m_max_hp);
	}
	
	if(cure)
	{
		PE_cure(false);
	}
	
	return m_alive;
}
