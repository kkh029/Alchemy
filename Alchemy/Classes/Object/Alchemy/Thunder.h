//
//  Thunder.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Thunder__
#define __Alchemy__Thunder__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Thunder : public Alchemy
{
public:
	Thunder(unsigned char index);
	Thunder(string name);
	~Thunder();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	int m_ani_stage;
	Size m_winSize;
	cc_timeval event_time[2];
};

#endif /* defined(__Alchemy__Thunder__) */
