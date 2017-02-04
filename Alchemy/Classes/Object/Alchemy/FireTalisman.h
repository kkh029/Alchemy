//
//  FireTalisman.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__FireTalisman__
#define __Alchemy__FireTalisman__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class FireTalisman : public Alchemy
{
public:
	FireTalisman(unsigned char index);
	~FireTalisman();

	static Alchemy* create(PEObject*  obj);
	static float POWER_UP;
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	Size m_winSize;
	timeval event_time[2];
};

#endif /* defined(__Alchemy__FireTalisman__) */
