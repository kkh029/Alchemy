//
//  SandStorm.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__SandStorm__
#define __Alchemy__SandStorm__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class SandStorm : public Alchemy
{
public:
	SandStorm(unsigned char index);
	SandStorm(string name);
	~SandStorm();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
};

#endif /* defined(__Alchemy__SandStorm__) */
