//
//  BoardPos.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 1. 30..
//
//

#ifndef __Alchemy__BoardPos__
#define __Alchemy__BoardPos__

#include "Common.h"

#define BOARD_WIDTH_EDGE 48.0f
#define BOARD_HEIGHT_EDGE 470.0f

class PEBoardPos
{
private:
	PEBoardPos();
	~PEBoardPos();
	bool valid;
	Vec2 oneBoxVertex[4];
	Vec2 crossBoxVertex[12];
	Vec2 boxIndex;
	Vec2 boxPos;
	bool check_board[ROW_NUM][COL_NUM];
	bool isInit;

protected:
  static PEBoardPos sInstance;

public:
	static PEBoardPos* getInstance();
	void init();
	bool setTouchPos(Touch* pTouch);
	Vec2* getBoxVertex(Touch* pTouch);
	Vec2* getBoxVertex();
	Vec2* getBoxIndex(Touch* pTouch);
	Vec2* getBoxIndex();
	Vec2 getPosIndex(Vec2 point);
	Vec2* getBoxPos();
	Vec2* getCrossBoxVertex(int axis);
	Vec2* getTalismanArea(void);
	void setTowerOnBoard();
	void clearTowerOnBoard();
	void setMoveField(float y);
	float board_pos_decision_row[COL_NUM+1];
	float board_pos_decision_col[ROW_NUM+1];
	void convertPointtBoxRect(Vec2* pos, Rect* rect);
	Rect getRectByIndex(Vec2 index);
};

#endif /* defined(__Alchemy__BoardPos__) */
