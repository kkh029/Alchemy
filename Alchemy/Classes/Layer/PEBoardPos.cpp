//
//  BoardPos.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 1. 30..
//
//

#include "PEBoardPos.h"

PEBoardPos PEBoardPos::sInstance;
float m_MoveDis;

PEBoardPos::PEBoardPos()
{}
PEBoardPos::~PEBoardPos()
{}

PEBoardPos* PEBoardPos::getInstance()
{
	if(!sInstance.isInit)
		sInstance.init();
	return &sInstance;
}

bool PEBoardPos::setTouchPos(CCTouch* pTouch)
{
	Vec2 point = pTouch->getLocation();
	point.y = point.y - m_MoveDis;
	if(pTouch == NULL)
		return false;
	if( (point.y < BOARD_HEIGHT_EDGE || point.y > BOARD_HEIGHT_EDGE + 1030)
		|| (point.x < BOARD_WIDTH_EDGE || point.x > 1022.0f) )
	{
		valid = false;
		return false;
	}
	else 
		valid = true;
 
	boxIndex.x = ((point.x - BOARD_WIDTH_EDGE) / floorf(BOARD_WIDTH));
	boxIndex.y = ((point.y - BOARD_HEIGHT_EDGE) / floorf(BOARD_HEIGHT));

	boxPos.x = (board_pos_decision_row[(int)boxIndex.x]
		+ board_pos_decision_row[(int)boxIndex.x+1])/2;
	boxPos.y = board_pos_decision_col[(int)boxIndex.y];
	return true;
}

Vec2* PEBoardPos::getBoxIndex(CCTouch* pTouch)
{
	setTouchPos(pTouch);

	if(valid == false)
		return NULL;
	else
		return &boxIndex;
}

Vec2* PEBoardPos::getBoxIndex()
{
	if(valid == false)
		return NULL;
	else
		return &boxIndex;
}

Vec2* PEBoardPos::getBoxPos()
{
	return &boxPos;
}

Vec2* PEBoardPos::getBoxVertex(CCTouch* pTouch)
{
	int x, y;
	setTouchPos(pTouch);
	if(valid == false)
		return NULL;

	x = boxIndex.x;
	y = boxIndex.y;

  oneBoxVertex[0].x = board_pos_decision_row[x];
  oneBoxVertex[0].y = board_pos_decision_col[y];
  oneBoxVertex[1].x = board_pos_decision_row[x+1];
  oneBoxVertex[1].y = board_pos_decision_col[y];
  oneBoxVertex[2].x = board_pos_decision_row[x+1];
  oneBoxVertex[2].y = board_pos_decision_col[y+1];
  oneBoxVertex[3].x = board_pos_decision_row[x];
  oneBoxVertex[3].y = board_pos_decision_col[y+1];
  return oneBoxVertex;
}

void PEBoardPos::convertPointtBoxRect(Vec2* pos, CCRect* rect)
{
	Vec2 index;
	index.x = ((pos->x - BOARD_WIDTH_EDGE) / floorf(BOARD_WIDTH));
	index.y = ((pos->y - BOARD_HEIGHT_EDGE) / floorf(BOARD_HEIGHT));

	rect->origin.x = board_pos_decision_row[(int)index.x];
	rect->origin.y = board_pos_decision_col[(int)index.y];
	rect->size.width = BOARD_WIDTH;
	rect->size.height = BOARD_HEIGHT;
}

CCRect PEBoardPos::getRectByIndex(Vec2 index)
{
	CCRect rect;
	rect.origin.x = board_pos_decision_row[(int)index.x];
	rect.origin.y = board_pos_decision_col[(int)index.y];
	rect.size.width = BOARD_WIDTH;
	rect.size.height = BOARD_HEIGHT;
	
	return rect;
}

Vec2* PEBoardPos::getBoxVertex()
{
	int x, y;
	if(valid == false)
		return NULL;

	x = boxIndex.x;
	y = boxIndex.y;

  oneBoxVertex[0].x = board_pos_decision_row[x];
  oneBoxVertex[0].y = board_pos_decision_col[y];
  oneBoxVertex[1].x = board_pos_decision_row[x+1];
  oneBoxVertex[1].y = board_pos_decision_col[y];
  oneBoxVertex[2].x = board_pos_decision_row[x+1];
  oneBoxVertex[2].y = board_pos_decision_col[y+1];
  oneBoxVertex[3].x = board_pos_decision_row[x];
  oneBoxVertex[3].y = board_pos_decision_col[y+1];
  return oneBoxVertex;
}

Vec2* PEBoardPos::getCrossBoxVertex(int axis)
{
	int x, y;
	if(valid == false)
		return NULL;
  
	x = boxIndex.x;
	y = boxIndex.y;
  
  if(axis == COL)
  {
    crossBoxVertex[0].x = board_pos_decision_row[x];
    crossBoxVertex[0].y = board_pos_decision_col[0];
    
    crossBoxVertex[1].x = board_pos_decision_row[x+1];
    crossBoxVertex[1].y = board_pos_decision_col[0];
    
    crossBoxVertex[2].x = board_pos_decision_row[x+1];
    crossBoxVertex[2].y = board_pos_decision_col[ROW_NUM];
    
    crossBoxVertex[3].x = board_pos_decision_row[x];
    crossBoxVertex[3].y = board_pos_decision_col[ROW_NUM];
  }
  else if(axis == ROW)
  {
    crossBoxVertex[0].x = board_pos_decision_row[COL_NUM];
    crossBoxVertex[0].y = board_pos_decision_col[y+1];
    
    crossBoxVertex[1].x = board_pos_decision_row[0];
    crossBoxVertex[1].y = board_pos_decision_col[y+1];
    
    crossBoxVertex[2].x = board_pos_decision_row[0];
    crossBoxVertex[2].y = board_pos_decision_col[y];
    
    crossBoxVertex[3].x = board_pos_decision_row[COL_NUM];
    crossBoxVertex[3].y = board_pos_decision_col[y];
  }

  return crossBoxVertex;
}

Vec2* PEBoardPos::getTalismanArea(void)
{
	int x, y;
	if(valid == false)
		return NULL;
  
	int x_min;
	int x_max;
	int y_min;
	int y_max;

	x = boxIndex.x;
	y = boxIndex.y;

	x_min = (x-1 < 0)?0:(x-1);
	x_max = (x+2 > COL_NUM)?COL_NUM:(x+2);
	y_min = (y-1 < 0)?0:(y-1);
	y_max = (y+2 > ROW_NUM)?ROW_NUM:(y+2);
	
    crossBoxVertex[0].x = board_pos_decision_row[x_max];
    crossBoxVertex[0].y = board_pos_decision_col[y_max];
    
    crossBoxVertex[1].x = board_pos_decision_row[x_min];
    crossBoxVertex[1].y = board_pos_decision_col[y_max];
    
    crossBoxVertex[2].x = board_pos_decision_row[x_min];
    crossBoxVertex[2].y = board_pos_decision_col[y_min];
    
    crossBoxVertex[3].x = board_pos_decision_row[x_max];
    crossBoxVertex[3].y = board_pos_decision_col[y_min];
	
	return crossBoxVertex;
}

void PEBoardPos::setTowerOnBoard()
{
  
}

void PEBoardPos::clearTowerOnBoard()
{
  
}

void PEBoardPos::init()
{
  int i;
  isInit = true;
  for(i=0; i<COL_NUM+1; i++)
  {
    board_pos_decision_row[i] = BOARD_WIDTH_EDGE + BOARD_WIDTH*i;
    PRINT_LOG("row:%f\n",board_pos_decision_row[i]);
  }
  for(i=0; i<ROW_NUM+1; i++)
  {
    board_pos_decision_col[i] = BOARD_HEIGHT_EDGE + BOARD_HEIGHT*i;
    PRINT_LOG("col:%f\n",board_pos_decision_col[i]);
  }
}

void PEBoardPos::setMoveField(float y)
{
	m_MoveDis = y;
}

Vec2 PEBoardPos::getPosIndex(Vec2 point)
{
	Vec2 index = Vec2(-0.0f,-0.0f);

	index.x = (int)((point.x - BOARD_WIDTH_EDGE) / floorf(BOARD_WIDTH));
	index.y = (int)((point.y - BOARD_HEIGHT_EDGE) / floorf(BOARD_HEIGHT));

	return index;
}
