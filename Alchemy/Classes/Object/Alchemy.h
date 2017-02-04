#ifndef Alchemy_Alchemy
#define Alchemy_Alchemy

#include "Common.h"
#include "PEObject.h"
#include "Monster.h"
#include "PE_Collision.h"

#define RESOURCE_MAX 27
#define RESOURCE_START 5

class PE_Collision;

class Alchemy : public Armature, public PEObject
{
public:
	Alchemy(PE_s_resource obj);
	~Alchemy();

	static Alchemy* create(PEObject* obj);

	/* virtual func */
	virtual bool PE_update(unsigned int flag);
	virtual void PE_initAnimation(void);
	virtual void Hit(int attackPoint);
	virtual void PE_cure(bool start);
	
	void SetLocation(Vec2* location);
	Vec2* GetLocation();
	bool isElement();

	static PE_s_resource resource_table[RESOURCE_MAX];
	static void PE_makeResource();
	static SpriteBatchNode* PE_getBatchNode_bullets();

	float x_pos_offset;
	float y_pos_offset;

protected:
	Vec2* m_location;
	bool update_flag;

	int start_t;

	int m_nextBullet;
	int m_dualShotFinishTime;

	// before point
	int m_prevBoardX;
	int m_prevBoardY;

	Size m_winSize;
	timeval event_time[2];
	static SpriteBatchNode* m_pBatchNode_bullets;
	PE_Collision* m_pCollision;

	int m_max_hp;
	
	/* buff */
	bool ap_up;
	bool speed_up;
	bool hp_up;
	bool cure;


	

private:

	


};

#endif
