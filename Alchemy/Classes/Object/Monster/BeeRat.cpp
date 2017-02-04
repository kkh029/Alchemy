#include "BeeRat.h"

PE_s_monster BeeRat::param_BeeRat =
{
    1,
    1,
    "BeeRat",
    MONSTER_TYPE_FLYER,
    80,
    10,
    80,
    1.0f
};

BeeRat::BeeRat():Monster(param_BeeRat) {
}

BeeRat::~BeeRat() {

}

Monster* BeeRat::create() 
{
	BeeRat* pBeeRat = new BeeRat();

	return pBeeRat;
}