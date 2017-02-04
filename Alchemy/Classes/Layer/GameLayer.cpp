#include "GameLayer.h"
#include "Field.h"
#include "MixPanel.h"
#include "PEIcon.h"
#include "../Object/Alchemy.h"
#include "../Object/MixResource.h"
#include "../Sound/PEBackgroundMusic.h"
#include "../PopUp/PEPopUpManager.h"
#include "../Object/PE_Collision.h"

MixPanel* GameLayer::m_MixPanel;
Field* GameLayer::m_Field;
PEIcon* GameLayer::m_PEIcon;
PEPopUpManager* GameLayer::m_PEPopupManager;
int GameLayer::m_stage;

CCScene* GameLayer::scene(int stage){
	CCScene* pScene = CCScene::create();
	GameLayer* pGameLayer = new GameLayer();
	pGameLayer->init(stage);
	pScene->addChild(pGameLayer);

	return pScene;
}

bool GameLayer::init(int stage) {
	if(CCLayer::init() == false) {
		return false;
	}
	
	autorelease();
	m_stage = stage;
	//PrepareResources();
	//PrepareMonsters();
	setKeypadEnabled(true);
	
	srand(time(NULL));

	m_Field = new Field();
	m_Field->init();
	addChild(m_Field, 0);
	
	m_PEIcon = new PEIcon();
	m_PEIcon->init(stage);
	addChild(m_PEIcon, 1);

	m_MixPanel = new MixPanel();
	m_MixPanel->init();
	m_MixPanel->setContentSize(ccp(1080.0f, 441.0f));
	m_MixPanel->setField(m_Field);
	m_MixPanel->setPEIcon(m_PEIcon);
	addChild(m_MixPanel, 2);

	m_PEPopupManager = new PEPopUpManager();
	m_PEPopupManager->init();
	addChild(m_PEPopupManager, 3);

	m_PEPopupManager->setResume(this, (SEL_Resume)(&GameLayer::GameResume));
	m_PEPopupManager->setPause(this, (SEL_Resume)(&GameLayer::GamePause));
	
	PE_Collision::getPE_Collision()->PE_reset();
	
	stageManager = new StageManagement(m_stage);
	stageManager->setSpawnMonster(m_Field, (SEL_SPAWN)(&Field::SpawnMonsters));
	stageManager->setPassCallback(m_MixPanel, (SEL_PASS)(&MixPanel::sendPass));
	addChild(stageManager);

    PEBackgroundMusic::sharedPEBackgroundMusic()->PE_play(PEBackgroundMusic::BGM_THEME12);

	return true;
}

void GameLayer::keyBackClicked(void)
{
	char buf[5];
	sprintf(buf, "%d", POPUP_STOP);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("scene_popup", popParam);
}

void GameLayer::GamePause(void)
{
	m_MixPanel->setTouchEnabled(false);
	m_Field->setTouchEnabled(false);
	m_PEIcon->m_setTouchEnabled(false);
}

void GameLayer::GameResume(void)
{
	m_MixPanel->setTouchEnabled(true);
	m_Field->setTouchEnabled(true);
	m_PEIcon->m_setTouchEnabled(true);
}
/*
void GameLayer::PrepareResources() {
	string Alchemy_folder = "Alchemy/";
	string png_expand = "0.png";
	string plist_expand = "0.plist";
	string json_expand = ".ExportJson";
	int i;
	char png_path[50];
	char plist_path[50];
	char json_path[50];
	for(i=5; i<27; i++)
	{
		sprintf(png_path, "%s%s/%s%s",
				Alchemy_folder.c_str(),
				Alchemy::resource_table[i].name,
				Alchemy::resource_table[i].name,
				png_expand.c_str() );
		
		sprintf(plist_path, "%s%s/%s%s",
				Alchemy_folder.c_str(),
				Alchemy::resource_table[i].name,
				Alchemy::resource_table[i].name,
				plist_expand.c_str() );
		
		sprintf(json_path, "%s%s/%s%s",
				Alchemy_folder.c_str(),
				Alchemy::resource_table[i].name,
				Alchemy::resource_table[i].name,
				json_expand.c_str());
	
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(png_path, plist_path, json_path);
	}
	
	
	
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
																			"Layer/lPopUp/lStar/lStar0.png", "Layer/lPopUp/lStar/lStar0.plist", "Layer/lPopUp/lStar/lStar.ExportJson");

	Alchemy::PE_makeResource();
}
*/
/*
void GameLayer::PrepareMonsters() {
	string Monster_folder = "Monster/";
	string png_expand = "0.png";
	string plist_expand = "0.plist";
	string json_expand = ".ExportJson";
	int i;
	char png_path[50];
	char plist_path[50];
	char json_path[50];
	for(i=1; i < Monster::MONSTER_MAX; i++)
	{
		sprintf(png_path, "%s%s/%s%s",
			Monster_folder.c_str(),
			Monster::monster_table[i].name,
			Monster::monster_table[i].name,
			png_expand.c_str() );

		sprintf(plist_path, "%s%s/%s%s",
			Monster_folder.c_str(),
			Monster::monster_table[i].name,
			Monster::monster_table[i].name,
			plist_expand.c_str() );

		sprintf(json_path, "%s%s/%s%s",
			Monster_folder.c_str(),
			Monster::monster_table[i].name,
			Monster::monster_table[i].name,
			json_expand.c_str());

		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(png_path, plist_path, json_path);
	}
}
*/
void GameLayer::onExit()
{
	PRINT_LOG("GameLayer - on Exit()");
	this->removeFromParentAndCleanup(true);
}

int GameLayer::getStageNum()
{
	return m_stage;
}