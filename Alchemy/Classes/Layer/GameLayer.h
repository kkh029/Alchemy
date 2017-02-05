#ifndef Alchemy_GameLayer
#define Alchemy_GameLayer

#include "../Common.h"
#include "../Object/Monster.h"
#include "StageManagement.h"

class MixPanel;
class Field;
class PEIcon;
class PEPopUpManager;

class GameLayer : public Layer
{
public:
	bool init(int stage);

	static Scene* scene(int stage);
	void GamePause(void);
	void GameResume(void);
	virtual void onExit();

	static int getStageNum();
	
protected:

private:
	static int m_stage;
	static MixPanel* m_MixPanel;
	static Field* m_Field;
	static PEIcon* m_PEIcon;
	static PEPopUpManager* m_PEPopupManager;
	StageManagement* stageManager;

	void PrepareResources(void);
	void PrepareMonsters(void);
};

#endif
