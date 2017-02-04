/*
d. 14.03.01
a. hwi
n. singleton class
Check Object Collisions...

*/

#ifndef Alchemy_PE_Collision
#define Alchemy_PE_Collision

#include "Common.h"
#include "PEObject.h"
#include "Alchemy.h"
#include "Monster.h"
#include "../Layer/PEBoardPos.h"

typedef void (Ref::*SEL_HITDOOR)(int);

class PE_Collision : public Ref
{
public:
	static PE_Collision* getPE_Collision();
	void addMonster(Monster* obj);
    void PE_updateMatrix();
	std::vector<Monster*> m_monsters_matrix[COL_NUM];
	void setHitDoorCallback(Ref* target, SEL_HITDOOR callback) ;
	void PE_reset();
    int PE_get_monster_num(void);
	
protected:
	
private:
	PE_Collision();
	~PE_Collision();
	static PE_Collision* instant;

	PEBoardPos *broadPos;
	
	Ref*	pListener;
    SEL_HITDOOR    hitDoor;
    
    void PE_clearVector();
    void removeMonster(Ref* pObject);
};

#endif
