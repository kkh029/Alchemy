#ifndef Alchemy_Resource
#define Alchemy_Resource

#include "Common.h"
#include "PEObject.h"

class MixResource : public CCSprite, public PEObject
{
public:
	MixResource(PE_s_resource obj);
	~MixResource();

	static MixResource* create(unsigned char index);
	void setIsElement(bool element);
	void setTouchable(bool valid);
	bool getTouchable(void);

private:
	bool isTouchable;
};

#endif