//
//  Mist.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Mist__
#define __Alchemy__Mist__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Mist : public Alchemy
{
public:
	Mist(unsigned char index);
	Mist(string name);
	~Mist();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	Size m_winSize;
	int m_ani_stage;
	_STRUCT_TIMEVAL event_time[2];
};

#endif /* defined(__Alchemy__Flame__) */
