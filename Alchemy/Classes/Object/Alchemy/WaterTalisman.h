//
//  WaterTalisman.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__WaterTalisman__
#define __Alchemy__WaterTalisman__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class WaterTalisman : public Alchemy
{
public:
	WaterTalisman(unsigned char index);
	WaterTalisman(string name);
	~WaterTalisman();

	static Alchemy* create(PEObject*  obj);
	static float CURE;
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	Size m_winSize;
	timeval event_time[2];
};

#endif /* defined(__Alchemy__WaterTalisman__) */
