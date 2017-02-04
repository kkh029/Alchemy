//
//  EarthTalisman.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__EarthTalisman__
#define __Alchemy__EarthTalisman__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class EarthTalisman : public Alchemy
{
public:
	EarthTalisman(unsigned char index);
	~EarthTalisman();

	static Alchemy* create(PEObject*  obj);
	static float MAX_HP_UP;
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	Size m_winSize;
	cc_timeval event_time[2];
};

#endif /* defined(__Alchemy__EarthTalisman__) */
