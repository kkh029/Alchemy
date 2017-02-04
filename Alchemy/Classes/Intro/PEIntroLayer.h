//
//  PEIntroLayer.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 10..
//
//

#ifndef __Alchemy__PEIntroLayer__
#define __Alchemy__PEIntroLayer__

#include "../Common.h"

class PEIntroLayer : public CCLayerColor
{
public:
	bool init();
	
	static CCScene* scene();
	CREATE_FUNC(PEIntroLayer);
	
protected:
	
private:
	void introOut(CCObject* in);
	CCSprite* m_title;
	void startButton(float in);
	void startIntro(float in);
	CCLayerColor* buttonLayer;
};

#endif /* defined(__Alchemy__PEIntroLayer__) */
