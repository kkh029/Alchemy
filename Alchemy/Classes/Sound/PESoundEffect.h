//
//  PEEffectSound.h
//  Alchemy
//
//  Created by Kyounghwan Kim on 2014. 11. 2..
//
//

#ifndef __Alchemy__PESoundEffect__
#define __Alchemy__PESoundEffect__

#include "../Common.h"

struct s_PE_SOUND_EFFECT
{
    char name[30];
    unsigned int time;   //msec
};

class PESoundEffect : public CCNode
{
public:
    void PE_play(int index);
    void PE_stop();
    void PE_pause();
    void PE_resume();
    static PESoundEffect* sharedPESoundEffect();
    void PE_mute(bool isMute);
    void PE_set_onoff(bool flag);
    bool PE_get_onoff(void);

    
    enum e_PE_SOUND_EFFECT
    {
        SE_BUTTON_1 = 0,
        SE_WHOOSH,
        SE_ENTER,
        SE_BUTTON_MAKE_1,
        SE_BUTTON_MAKE_2,
        SE_CHAREC,
        SE_SIT_WATER,
        SE_SIT_FIRE,
        SE_SIT_WIND,
        SE_SIT_LAND,
        SE_INDEX_MAX
    };
    
protected:
    
private:
    PESoundEffect();
    ~PESoundEffect();
    
    static PESoundEffect* sInstance;
    static s_PE_SOUND_EFFECT SE_file_list[SE_INDEX_MAX];
    
    bool onoff;
    int m_SE_index;
    
};


#endif /* defined(__Alchemy__PESoundEffect__) */
