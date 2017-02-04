//
//  Mud.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Mud__
#define __Alchemy__Mud__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Mud : public Alchemy
{
public:
	Mud(unsigned char index);
	Mud(string name);
	~Mud();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	Size m_winSize;
	cc_timeval event_time[2];
};

#endif /* defined(__Alchemy__Mud__) */
