//
//  WindTalisman.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__WindTalisman__
#define __Alchemy__WindTalisman__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class WindTalisman : public Alchemy
{
public:
	WindTalisman(unsigned char index);
	WindTalisman(string name);
	~WindTalisman();

	static Alchemy* create(PEObject*  obj);
	static float SPEED_UP;
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	Size m_winSize;
	_STRUCT_TIMEVAL event_time[2];
};

#endif /* defined(__Alchemy__WindTalisman__) */
