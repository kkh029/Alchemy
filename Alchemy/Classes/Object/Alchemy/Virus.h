//
//  Virus.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Virus__
#define __Alchemy__Virus__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Virus : public Alchemy
{
public:
	Virus(unsigned char index);
	Virus(string name);
	~Virus();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	Size m_winSize;
	int m_ani_stage;
	timeval life_time[2];
	timeval event_time[2];
};

#endif /* defined(__Alchemy__Virus__) */
