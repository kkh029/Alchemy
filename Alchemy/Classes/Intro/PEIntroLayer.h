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

class PEIntroLayer : public LayerColor
{
public:
	bool init();
	
	static Scene* scene();
	CREATE_FUNC(PEIntroLayer);
	
protected:
	
private:
	void introOut(Ref* in);
	Sprite* m_title;
	void startButton(float in);
	void startIntro(float in);
	LayerColor* buttonLayer;
};

#endif /* defined(__Alchemy__PEIntroLayer__) */
