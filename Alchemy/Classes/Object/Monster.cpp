#include "Monster.h"
#include "Monster/BeeRat.h"
#include "Monster/PigTurtle.h"
#include "Monster/ElePanda.h"
#include "Monster/Lamp.h"
#include "../Layer/Field.h"

Monster* Monster::create(int index)
{
    switch(index)
    {
        case 0:
            return BeeRat::create();
        case 1:
            return PigTurtle::create();
        case 2:
            return ElePanda::create();
        case 3:
            return Lamp::create();
        default:
            break;
    }
    return NULL;
}

Monster::Monster() : PEObject() {

}

Monster::Monster(PE_s_monster monster) : PEObject() {
	m_name = monster.name;
	m_index = monster.index;
	m_circle = monster.circle;
	m_hp	= monster.hp;
	m_range = monster.range;
	m_ap = monster.ap;
	m_movementSpeed = monster.movementSpeed;
	m_type = monster.type;
	reset = true;
	status = 0;
	slow_duration = 0.0f;
	blind_duration = 0.0f;
	move_speed_scale = 1.0f;
	move_speed_stage_scale = 1.0f;
}

Monster::~Monster() {	
}

void Monster::PE_initAnimation() {
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
}

bool Monster::PE_update(unsigned int flag) {
	int a = PETime::GetTime();

	/* status check */
	if(m_hitTime != 0 && m_hitTime + HIT_BLINK_TIME < a) {
		this->setColor(Color3B(255,255,255));
	}
	
	if(status & (0x1<< MONSTER_STATUS_SLOW))
	{
		slow_duration -= 1;
		if(slow_duration == 0)
		{
			status = status & !(0x1<<MONSTER_STATUS_SLOW);
			move_speed_scale = 1.0f;
		}
	}
	
	if(status & (0x1<< MONSTER_STATUS_BLIND))
	{
		blind_duration -= 1;
		if(blind_duration == 0)
		{
			status = status & !(0x1<<MONSTER_STATUS_BLIND);
			m_ap = 20;
		}
	}

	switch(m_mode)
	{
	case MONSTER_MOVE:
		move(move_speed_scale);
		break;
	case MONSTER_ATTACK:
		break;
	}

	Special();
	return true;
}

void Monster::move(float speed_scale){
	float move_distance = move_speed_stage_scale*m_movementSpeed*speed_scale;
	Vec2 pos = getPosition();
	
	if(m_ani_index != MONSTER_MOVE)
	{
		m_ani_index = MONSTER_MOVE;
		getAnimation()->playWithIndex(0, -1, -1);
	}
	pos.y = pos.y - (move_distance);
	setPosition(pos);
}

void Monster::slow(float speed_scale, float duration)
{
	slow_duration = duration*60;
	move_speed_scale = speed_scale;
	status = status | (0x1<< MONSTER_STATUS_SLOW);
	return;
}


void Monster::blind(float duration)
{
	blind_duration = duration;
	m_ap = 0;
	status = status | (0x1<< MONSTER_STATUS_BLIND);
	return;
}

void Monster::OnEndOfMoving(Node* pNode) {
	pNode->stopAllActions();
	pNode->setVisible(false);
}

void Monster::Attack(PEObject* obj)
{
	static timeval event_time[2];
	
	if(m_ani_index != MONSTER_ATTACK)
	{
		m_ani_index = MONSTER_ATTACK;
		getAnimation()->playWithIndex(1, -1, -1);
	}

	
	if (reset)
	{
		gettimeofday(&event_time[0], NULL);
		reset = false;
	}
	else
	{
		gettimeofday(&event_time[1], NULL);
        long diffTime = time_interval(event_time[0], event_time[1]);
 
		if(diffTime > 2000)
		{
			reset = true;
			obj->Hit(m_ap);
		}
	}
}

void Monster::Special() {

}

void Monster::Hit(int attackPoint) {
	m_hp -= attackPoint;
	m_hp = (m_hp>0)?m_hp:0;

	if(m_hp < 1) {
		Dead();
		return;
	}
		
	this->setColor(Color3B(255,180,175));
	m_hitTime = PETime::GetTime();

}

void Monster::Dead() {
	setVisible(false);
}

int Monster::getMode(void)
{
	return m_mode;
}

void Monster::setMode(int mode)
{
	m_mode = mode;
}

int Monster::getRange() {
	return m_range;
}

int Monster::getMovementSpeed(){
	return m_movementSpeed;
}

void Monster::setStageLevel(float speed_scale)
{
	move_speed_stage_scale = speed_scale;
}

