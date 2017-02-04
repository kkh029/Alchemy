#include "PigTurtle.h"

PE_s_monster PigTurtle::param_PigTurtle = {
    2,
    2,
    "PigTurtle",
    MONSTER_TYPE_WALKER,
    400,
    5,
    80,
    0.5f
};

PigTurtle::PigTurtle():Monster(param_PigTurtle) {
}

PigTurtle::~PigTurtle() {

}

Monster* PigTurtle::create()
{
	PigTurtle* pPigTurtle = new PigTurtle();
	
	return pPigTurtle;
}

