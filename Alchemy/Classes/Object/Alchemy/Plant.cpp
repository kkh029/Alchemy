//
//  Plant.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1302	Plant	3	30	-	-	-	Tower	-		재료.	1104	1201
//

#include "Plant.h"
#include "WindTalisman.h"
#include "WaterTalisman.h"
#include "EarthTalisman.h"
#include "FireTalisman.h"

/* ALCHEMY PARAMETER */
#define TWEEN_EASING_MAX_INDEX 10000
#define DEFAULT_INDEX	0
#define LOOP			-1

#define HP 30

Plant::Plant(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_hp = HP;
}

Plant::~Plant()
{}

Alchemy* Plant::create(PEObject* obj) 
{
	Plant* pPlant = new Plant(obj->PE_getResourceIndex());

	return pPlant;
}

void Plant::PE_initAnimation()
{
	CCArmatureAnimation* ani;
	init(m_name.c_str());
	setAnchorPoint(ccp(0.5f, 0.0f));
	ani = getAnimation();
	ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX_INDEX);
}


bool Plant::PE_update(unsigned int flag) {
	
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
	
	if(!m_alive)
		removeFromParent();
		
	return m_alive;
}
