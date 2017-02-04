//
//  Lamp.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 7. 13..
//
//

#ifndef __Alchemy__Lamp__
#define __Alchemy__Lamp__

#include "Common.h"
#include "../Monster.h"

class Lamp : public Monster {
public:
	Lamp();
	~Lamp();
	
	static Monster* create(void);
    static PE_s_monster param_Lamp;
	
private:
	
};

#endif /* defined(__Alchemy__Lamp__) */
