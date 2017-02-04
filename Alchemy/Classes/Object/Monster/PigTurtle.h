#ifndef Alchemy_PigTurtle
#define Alchemy_PigTurtle

#include "Common.h"
#include "../Monster.h"

class PigTurtle : public Monster {
public:
	PigTurtle();
	~PigTurtle();

	static Monster* create(void);
    static PE_s_monster param_PigTurtle;
private:


};

#endif