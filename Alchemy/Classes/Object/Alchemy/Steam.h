//
//  Steam.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Steam__
#define __Alchemy__Steam__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Steam : public Alchemy
{
public:
	Steam(unsigned char index);
	Steam(string name);
	~Steam();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int m_ani_stage;
	timeval life_time[2];
	timeval attack_time[2];
};

#endif /* defined(__Alchemy__Steam__) */
