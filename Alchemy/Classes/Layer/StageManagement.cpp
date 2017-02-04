#include <ctime>
#include "StageManagement.h"
#include "../PopUp/PEPopUpManager.h"
#include "../Object/PE_Collision.h"

s_peStageInform stage_table[MAX_STAGE] =
{
/*	stage		time		level	speed*/
	{0,			180000,		1,		1},
	{1,			180000,		1,		1},
	{2,			180000,		2,		1},
	{3,			180000,		2,		2},
	{4,			180000,		3,		2},
	{5,			180000,		3,		2},
	{6,			180000,		3,		3},
	{7,			180000,		3,		3},
	{8,			180000,		4,		3},
	{9,         180000,		4,		4},
	{10,		180000,		4,		4},
	{11,		180000,		4,		4},
};

int mon_num_table[12][10] =
{
	{1, 1, 1, 1, 1, 2, 2, 2, 2, 1},
	{1, 1, 1, 2, 2, 2, 2, 2, 3, 1},
	{1, 1, 2, 2, 2, 2, 2, 3, 3, 2},
	{1, 2, 2, 2, 2, 2, 3, 3, 3, 2},
	{1, 2, 2, 2, 2, 3, 3, 3, 3, 2},
	{1, 2, 2, 2, 3, 3, 3, 3, 4, 2},
	{1, 2, 2, 2, 3, 3, 3, 4, 4, 2},
	{1, 2, 2, 3, 3, 3, 4, 4, 4, 2},
	{2, 2, 2, 3, 3, 3, 4, 4, 4, 3},
	{2, 2, 3, 3, 3, 4, 4, 4, 5, 2},
	{2, 2, 3, 3, 3, 4, 4, 5, 5, 2},
	{2, 3, 3, 4, 4, 4, 5, 5, 5, 3},
};

int mon_index_table[12][10][10] =
{
    // stage 1
    {
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    //stage 2
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
    {
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    },
};

double spawn_time_table[12][10] =
{
	{4500, 4500, 4500, 4500, 4500, 4000, 4000, 3500, 3500, 4000},
	{4500, 4500, 4500, 4000, 4000, 4000, 3500, 3500, 3000, 4000},
	{4500, 4500, 4000, 4000, 4000, 3500, 3500, 3000, 3000, 4000},
	{4500, 4500, 4000, 4000, 3500, 3500, 3000, 3000, 3000, 4000},
	{4500, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000},
	{4500, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000},
	{4500, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000},
	{4500, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000},
	{4500, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000},
	{4500, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000},
	{4500, 4000, 4000, 3000, 3000, 3000, 2500, 2500, 4000, 4000},
	{4500, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000},
};

int monster_generate_prob[4] = {0,};

StageManagement::StageManagement(int stage)
{
	autorelease();
	scheduleUpdate();
	resetTimeTable();
	
	PRINT_LOG("stage : %d", stage);
	setTimeTable(stage);
	
	send_success_flag = false;
    monster_generate_prob[0] = 5;
    monster_generate_prob[1] = 1;
    
}

StageManagement::~StageManagement()
{}

void StageManagement::resetTimeTable(){
	s_peTimeTable tempTimeTable = {false, 0, 0, 0, true};
	int i = MAX_GAME_TIME;
	while(i--)
		m_timeTable[i] = tempTimeTable;
	
	CCTime::gettimeofdayCocos2d(&time_play[TIME_START], NULL);
	CCTime::gettimeofdayCocos2d(&time_play[TIME_END], NULL);
	
	CCTime::gettimeofdayCocos2d(&time_spawn[TIME_START], NULL);
	CCTime::gettimeofdayCocos2d(&time_spawn[TIME_END], NULL);
	
}

void StageManagement::setTimeTable(int stage) {
	stage_status = stage_table[stage];
	pSawnTime = spawn_time_table[stage];
	pMonNum = mon_num_table[stage];
	stage_timestamp = stage_status.totalGameTime/10;
	stage_progress_index = 0;
    stage_count = 0;
    memcpy(mon_index, mon_index_table[stage][0], sizeof(mon_index[0])*10);
    srandom((unsigned)time(NULL));

}

void StageManagement::setSpawnMonster(CCObject* target, SEL_SPAWN callback)
{
	pListener = target;
	spawn_monster = callback;
}

void StageManagement::setPassCallback(CCObject* target, SEL_PASS callback)
{
	pListener_pass_callback = target;
	pass_callback = callback;
}

void StageManagement::update(float delta)
{
	double play_time;
	double spawn_time;
    static int monster_count[4] ={0,};
    CCTime::gettimeofdayCocos2d(&time_play[TIME_END], NULL);
	play_time = CCTime::timersubCocos2d(
									   &time_play[TIME_START],
									   &time_play[TIME_END] );
	
	
	
	if(play_time > stage_timestamp*(stage_progress_index+1) )
	{
		stage_progress_index++;
        stage_count = 0;
        memcpy(mon_index, mon_index_table[stage_status.stage][stage_progress_index], sizeof(mon_index[0])*10);
		PRINT_LOG("progress change : %d", stage_progress_index);
	}

	
	if(stage_progress_index >= 10
	   && send_success_flag == false
	   && PE_Collision::getPE_Collision()->PE_get_monster_num() == 0)
	{
		(pListener_pass_callback->*pass_callback)();
		send_success_flag = true;
	}
	
	CCTime::gettimeofdayCocos2d(&time_spawn[TIME_END], NULL);
	spawn_time = CCTime::timersubCocos2d(
										&time_spawn[TIME_START],
										&time_spawn[TIME_END] );
	if(spawn_time > pSawnTime[stage_progress_index] && stage_progress_index < 10)
	{
		CCTime::gettimeofdayCocos2d(&time_spawn[TIME_START], NULL);
        
		for(int i=0; i<pMonNum[stage_progress_index]; i++)
		{
            /*
			int rand_num = rand()%(10-stage_count);
            int index = mon_index[rand_num];
			PRINT_LOG("mon index : %d(%d)", index, rand_num);
			if (index > 0) {
				(pListener->*spawn_monster)(index, 1.0f);
			}
            mon_index[rand_num] = mon_index[10-stage_count - 1];
             */
            int sum_prob = 0;
            int accum_prob = 0;
            for(int i=0; i<4; i++)
            {
                sum_prob += monster_generate_prob[i];
            }
            int rand_num = rand()%sum_prob;
            for(int i=0; i<4; i++)
            {
                accum_prob += monster_generate_prob[i];
                if(rand_num < accum_prob)
                {
                    (pListener->*spawn_monster)(i, 1.0f);
                    monster_count[i]++;
                    
                    if(monster_generate_prob[i] > 1)
                        monster_generate_prob[i]--;
                    
                    for(int j=i+1; j<4; j++)
                    {
                        if(monster_generate_prob[j] > 0)
                            monster_generate_prob[j]++;
                    }
                    
                    break;
                }
                monster_generate_prob[i] += 10;
            }
            printf("monster prob : %d %d %d %d\n",
                   monster_generate_prob[0],
                   monster_generate_prob[1],
                   monster_generate_prob[2],
                   monster_generate_prob[3]);
            printf("monster count : %d %d %d %d\n",
                   monster_count[0],
                   monster_count[1],
                   monster_count[2],
                   monster_count[3]);
            
		}
        stage_count++;
        CCLog("stage_count : %d\n", stage_count);
	}
	
}
