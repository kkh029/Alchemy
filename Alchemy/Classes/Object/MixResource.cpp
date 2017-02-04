#include "MixResource.h"
#include "Alchemy.h"

char icon_name[27][30] =
{
	"",
	"Alchemy/iWind.png",
	"Alchemy/iWater.png",
	"Alchemy/iFire.png",
	"Alchemy/iEarth.png",
	"Alchemy/iMist.png",
	"Alchemy/iGlass.png",
	"Alchemy/iSteam.png",
	"Alchemy/iFlame.png",
	"Alchemy/iMud.png",
	"Alchemy/iIce.png",
	"Alchemy/iPlainWater.png",
	"Alchemy/iSand.png",
	"Alchemy/iTornado.png",
	"Alchemy/iRock.png",
	"Alchemy/iVirus.png",
	"Alchemy/iPlant.png",
	"Alchemy/iFireTalisman.png",
	"Alchemy/iWaterTalisman.png",
	"Alchemy/iWindTalisman.png",
	"Alchemy/iEarthTalisman.png",
	"Alchemy/iThunder.png",
	"Alchemy/iHighGlass.png",
	"Alchemy/iSandStorm.png",
	"Alchemy/iIcicle.png",
	"Alchemy/iBlock.png",
	"Alchemy/iHomunculus.png",
};

MixResource::MixResource(PE_s_resource obj)
: PEObject(obj)
{
	isTouchable = true;
}


MixResource::~MixResource() {
}

MixResource* MixResource::create(unsigned char index) {
	MixResource* pResource = NULL;

	if(index < RESOURCE_MAX)
	{
		pResource = new MixResource(Alchemy::resource_table[index]);
		pResource->initWithFile(icon_name[index]);
		pResource->autorelease();
	}

	return pResource;
}

void MixResource::setTouchable(bool valid)
{
	isTouchable = valid;
}
bool MixResource::getTouchable()
{
	return isTouchable;
}



