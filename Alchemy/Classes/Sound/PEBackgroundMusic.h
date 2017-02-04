//
//  PEBackgroundMusic.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 10..
//
//

#ifndef __Alchemy__PEBackgroundMusic__
#define __Alchemy__PEBackgroundMusic__

#include "../Common.h"

struct s_PE_BGM
{
	char name[30];
	unsigned int time;   //msec
};

class PEBackgroundMusic : public CCNode
{
public:
	void PE_play(int index);
	void PE_stop();
	void PE_pause();
	void PE_resume();
	static PEBackgroundMusic* sharedPEBackgroundMusic();
	void PE_mute(bool isMute);
    void PE_set_onoff(bool flag);
    bool PE_get_onoff(void);
	
	enum e_PE_BGM
	{
		BGM_MAIN1 = 1,
		BGM_MAIN2,
		BGM_BONUS,
		BGM_INVENTORY,
		BGM_THEME12,
		BGM_INDEX_MAX
	};
	
protected:
	
private:
	PEBackgroundMusic();
	~PEBackgroundMusic();
	
	static PEBackgroundMusic* sInstance;
	static s_PE_BGM m_BGM_list[BGM_INDEX_MAX];
	
    bool onoff;
	int m_music_index;
	
};

#endif /* defined(__Alchemy__PEBackgroundMusic__) */
