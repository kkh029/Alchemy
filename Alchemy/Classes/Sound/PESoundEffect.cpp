//
//  PEEffectSound.cpp
//  Alchemy
//
//  Created by Kyounghwan Kim on 2014. 11. 2..
//
//

#include "PESoundEffect.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

PESoundEffect* PESoundEffect::sInstance = new PESoundEffect();

s_PE_SOUND_EFFECT PESoundEffect::SE_file_list[SE_INDEX_MAX]=
{
    {"Effect/button_1.mp3", 1000},
    {"Effect/whoosh.mp3", 1000},
    {"Effect/enter.mp3", 1000},
    {"Effect/button_make1.mp3", 1000},
    {"Effect/button_make2.mp3", 1000},
    {"Effect/charac.mp3", 1000},
    {"Effect/sit_water.mp3", 1000},
    {"Effect/sit_fire.mp3", 1000},
    {"Effect/sit_wind.mp3", 1000},
    {"Effect/sit_land.mp3", 1000},
};

PESoundEffect::PESoundEffect()
{
}

PESoundEffect::~PESoundEffect()
{}

PESoundEffect* PESoundEffect::sharedPESoundEffect()
{
    static PESoundEffect s_SharedPESoundEffect;
    s_SharedPESoundEffect.onoff = UserDefault::sharedUserDefault()->getBoolForKey("EFFECT");
    return &s_SharedPESoundEffect;
}

void PESoundEffect::PE_play(int index)
{
    if(onoff)
        SimpleAudioEngine::sharedEngine()->playEffect(PESoundEffect::SE_file_list[index].name, false);
}

void PESoundEffect::PE_stop()
{
    if(onoff)
        SimpleAudioEngine::sharedEngine()->stopEffect(true);
}

void PESoundEffect::PE_pause()
{
    if(onoff)
        SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void PESoundEffect::PE_resume()
{
    if(onoff)
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void PESoundEffect::PE_mute(bool isMute)
{
    if(onoff)
    {
        if(isMute)
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
        else
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    }
}

void PESoundEffect::PE_set_onoff(bool flag)
{
    onoff = flag;
    if(!onoff)
        SimpleAudioEngine::sharedEngine()->stopEffect(true);
    UserDefault::sharedUserDefault()->setBoolForKey("EFFECT", onoff);
}

bool PESoundEffect::PE_get_onoff(void)
{
    return onoff;
}
