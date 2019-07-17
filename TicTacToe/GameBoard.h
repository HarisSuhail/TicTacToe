#pragma once
#include <stdio.h>
#include <stdint.h>
#include <iostream>

using namespace std;

#define GAMEBOARDSIZE 3
#define TRUE 1 
#define FALSE 0
typedef enum
{
	clearMark,
	xMark,
	oMark
} PlayerMarkTypeDef;

typedef struct {
	int row;
	int column;
} CoordinateTypeDef;


class GameBoard
{
private:
	uint8_t boardLayout[GAMEBOARDSIZE][GAMEBOARDSIZE];
	PlayerMarkTypeDef currentTurn;

public:
	GameBoard(PlayerMarkTypeDef firstTurn);
	void DisplayBoard();
	uint8_t PlaceMark(int row, int column);
	uint8_t PlaceSpecificMark(int row, int column, PlayerMarkTypeDef requiredMark);
	uint8_t CheckWin(PlayerMarkTypeDef markType);
	uint8_t IsFull();
	uint8_t IsLocationFree(int row, int column);
	friend CoordinateTypeDef GetBestMove(GameBoard gameBoard, PlayerMarkTypeDef currentTurn);
};