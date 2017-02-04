#ifndef Alchemy_Monster
#define Alchemy_Monster

#include "PEObject.h"
#include "Item.h"
#include "cocostudio/CCArmature.h"

using namespace cocostudio;

class PE_Collision;

class Monster : public PEObject, public Armature
{
public:
	Monster();
	Monster(PE_s_monster monster);
	~Monster();
    
    enum
    {
        MONSTER_STOP=0,
        MONSTER_MOVE,
        MONSTER_ATTACK,
    };
    
    enum
    {
        MONSTER_STATUS_SLOW = 1,
        MONSTER_STATUS_BLIND,
    };

    static const int MONSTER_MAX = 4;
    
    static Monster* create(int index);

	virtual void PE_initAnimation(void);
	virtual bool PE_update(unsigned int flag);
	
	void OnEndOfMoving(Node* obj);
	void Attack(PEObject* obj);
	void Hit(int attackPoint);
	virtual void Special();
	void Dead();

	
	
	/* move(float speed_scale, int duration)
	 * speed_scale : float, 1.0f=normal
	 */
	void move(float speed_scale);
	
	/* move(float speed_scale, int duration)
	 * speed_scale : float, 1.0f=normal
	 * duration : int, milisecond
	 */
	void slow(float speed_scale, float duration);
	void blind(float duration);
	void move_speed_update(float dt);
	
	int getRange();
	int getMovementSpeed();
	int getMode();
	void setMode(int mode);
	void setStageLevel(float scale);

	Armature* ball;

protected:
	float m_movementSpeed;
	int m_range;
	int m_mode;
	int m_ani_index;
	bool reset;
	int status;
	float slow_duration;
	float blind_duration;
	float move_speed_scale;
	float move_speed_stage_scale;

	static const int HIT_BLINK_TIME = 100;
	static const int END_OF_LINE = 1400;


private:
	


};

#endif
