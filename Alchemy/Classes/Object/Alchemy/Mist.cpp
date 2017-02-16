//
//  Mist.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1201	Mist	2	20s	-	-	-	Air	-		공중 몬스터 3초간 Block. 공격받지 않음	1103	1102	3
//  Block ∫∏∑˘

#include "Mist.h"

/* ALCHEMY PARAMETER */
#define DEFAULT_INDEX	1
#define FADE_IN_INDEX	0
#define FADE_OUT_INDEX	2
#define LOOP			0
#define TWEEN_EASING_MAX_INDEX 0
#define STAY_TIME 20000 //milisecond
#define DEFAULT_AP 20

/* OPTION */ 
#define STAY 0
#define ATTACK 1

#define TIME_START	0
#define TIME_END	1

Mist::Mist(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{}

Mist::~Mist()
{}

Alchemy* Mist::create(PEObject* obj) 
{
	Mist* pMist = new Mist(obj->PE_getResourceIndex());

	return pMist;
}

void Mist::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();

	gettimeofday(&event_time[TIME_START], NULL);
	ani->playWithIndex(FADE_IN_INDEX, -1, -1);
	m_ani_stage = FADE_IN_INDEX;
}


bool Mist::PE_update(unsigned int flag) {
	ArmatureAnimation* ani= getAnimation();
	gettimeofday(&event_time[TIME_END], NULL);
    double diffTime = time_interval(event_time[TIME_START], event_time[TIME_END]);

	if((m_ani_stage == FADE_IN_INDEX || ani->getCurrentFrameIndex() == 40))
	{
		ani->playWithIndex(DEFAULT_INDEX, -1, -1);
	}
	if(diffTime > STAY_TIME)
	{
		ani->playWithIndex(FADE_OUT_INDEX, -1, -1);
		return false;
	}
	return true;
}
