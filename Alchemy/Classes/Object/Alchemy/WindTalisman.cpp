//
//  WindTalisman.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#include "WindTalisman.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	0
//#define ATTACT_INDEX	0
//#define FADE_IN_INDEX	1
//#define FADE_OUT_INDEX	2
#define LOOP			-1
#define TWEEN_EASING_MAX_INDEX 2

/* OPTION */ 
#define STAY 0
#define ATTACK 0

#define AP 0
#define HP 20

float WindTalisman::SPEED_UP = 1.2f;

WindTalisman::WindTalisman(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_hp = HP;
	m_max_hp = HP;
		
	cure = false;
	hp_up = false;

	x_pos_offset = -15.0f;
	y_pos_offset = 20.0f;
}

WindTalisman::~WindTalisman()
{}

Alchemy* WindTalisman::create(PEObject* obj) 
{
	WindTalisman* pWindTalisman = new WindTalisman(obj->PE_getResourceIndex());

	return pWindTalisman;
}

void WindTalisman::PE_initAnimation()
{
	CCArmatureAnimation* ani;

	init(m_name.c_str());
	setAnchorPoint(ccp(0.5f, 0.0f));
	setScale(1.3f);
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX_INDEX);
}


bool WindTalisman::PE_update(unsigned int flag) {
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