#ifndef Alchemy_StageManagement
#define Alchemy_StageManagement

#include "Common.h"

#define MAX_STAGE				40
#define SPAWN_PROBABILITY		3
#define DEFAULT_MONSTER_LEVEL	100
#define MAX_GAME_TIME			240

enum e_peCaldronState {
	Caldron_Normal = 1,
	Caldron_Shakeup,
	Caldron_Eruption,
};

struct s_peTimeTable {
	bool spawnCheck;
	unsigned char monsterID;
	unsigned char monsterQuantity;
	unsigned char caldronState;
	bool finish;
};


struct s_peStageInform {
	int stage;
	double totalGameTime;
	int maxMonsterLevel;
	int monsterSpeed;
};

typedef void (CCObject::*SEL_SPAWN)(int monster_index, float move_speed_stage_scale);
typedef void (CCObject::*SEL_PASS)(void);

class StageManagement : public CCNode
{
public:
	StageManagement(int stage);
	~StageManagement();

	void resetTimeTable();
	void setTimeTable(int stage);
	void update(float delta);
	void setSpawnMonster(CCObject* target, SEL_SPAWN callback);
	void setPassCallback(CCObject* target, SEL_PASS callback);
	s_peTimeTable* getTimeTable(int time);

protected:

private:
	CCObject*	pListener;
    SEL_SPAWN	spawn_monster;
	CCObject*	pListener_pass_callback;
    SEL_PASS 	pass_callback;
	s_peTimeTable m_timeTable[MAX_GAME_TIME];
	s_peStageInform stage_status;
	bool send_success_flag;
	
	cc_timeval time_play[2];
	cc_timeval time_spawn[2];
	
	double* pSawnTime;
	int* pMonNum;
    int stage_count;
    int mon_index[10];
	double stage_timestamp;
	int stage_progress_index;

};

#endif
