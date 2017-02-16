//
//  FireTalisman.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1303	FireTalisman	3	30s	-	-	-	Tower	-		공격력 10% 증가. 같은 종류의 효과와 중복 불가.	1103	1202
//

#include "FireTalisman.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	0
//#define ATTACT_INDEX	0
//#define FADE_IN_INDEX	1
//#define FADE_OUT_INDEX	2
#define LOOP			-1
#define TWEEN_EASING_MAX_INDEX 2

/* OPTION */ 
#define HP 30

float FireTalisman::POWER_UP = 1.5;

FireTalisman::FireTalisman(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	m_hp = HP;
	m_max_hp = HP;
	
	cure = false;
	hp_up = false;

	x_pos_offset = -15.0f;
	y_pos_offset = 20.0f;
}

FireTalisman::~FireTalisman()
{}

Alchemy* FireTalisman::create(PEObject* obj) 
{
	FireTalisman* pFireTalisman = new FireTalisman(obj->PE_getResourceIndex());

	return pFireTalisman;
}

void FireTalisman::PE_initAnimation()
{
	ArmatureAnimation* ani;

	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	setScale(1.3f);
	ani = getAnimation();

	ani->playWithIndex(DEFAULT_INDEX, -1, -1);
}


bool FireTalisman::PE_update(unsigned int flag) {
	
	return m_alive;
}
