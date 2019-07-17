#include "GameBoard.h"

GameBoard::GameBoard(PlayerMarkTypeDef firstTurn) :boardLayout{ {0,0,0},{0,0,0},{0,0,0} }, currentTurn(firstTurn)
{

}

uint8_t GameBoard::PlaceMark(int row, int column)
{
	uint8_t markPlaced = FALSE;
	if (boardLayout[row][column] == clearMark)
	{
		boardLayout[row][column] = currentTurn;
		currentTurn = (currentTurn == xMark) ? oMark : xMark;
		markPlaced = TRUE;
	}
	return markPlaced;
}

uint8_t GameBoard::PlaceSpecificMark(int row, int column, PlayerMarkTypeDef requiredMark)
{
	uint8_t markPlaced = FALSE;
	if (boardLayout[row][column] == clearMark)
	{
		boardLayout[row][column] = requiredMark;
		markPlaced = TRUE;
	}
	return markPlaced;
}

void GameBoard::DisplayBoard()
{
	cout << endl;
	for (int row = 0; row < GAMEBOARDSIZE; row++)
	{
		for (int column = 0; column < GAMEBOARDSIZE; column++)
		{
			if (boardLayout[row][column] == xMark)
			{
				cout << "X";
			}
			else if (boardLayout[row][column] == oMark)
			{
				cout << "O";
			}
			else
			{
				cout << " ";
			}

			if (column != (GAMEBOARDSIZE - 1))
			{
				cout << "|";
			}
		}

		if (row != (GAMEBOARDSIZE - 1))
		{
			cout << "\r\n-----\r\n";
		}
	}
}

uint8_t GameBoard::CheckWin(PlayerMarkTypeDef markType)
{
	uint8_t winAchieved = FALSE;

	for (int row = 0; row < GAMEBOARDSIZE; row++)
	{
		if ((boardLayout[row][0] == markType) && (boardLayout[row][1] == markType) && (boardLayout[row][2] == markType))
		{
			winAchieved = TRUE;
		}
		else if ((boardLayout[0][row] == markType) && (boardLayout[1][row] == markType) && (boardLayout[2][row] == markType))
		{
			winAchieved = TRUE;
		}
	}

	if (winAchieved != TRUE)
	{
		if (((boardLayout[0][0] == markType) && (boardLayout[1][1] == markType) && (boardLayout[2][2] == markType)))
		{
			winAchieved = TRUE;
		}
		else if (((boardLayout[0][2] == markType) && (boardLayout[1][1] == markType) && (boardLayout[2][0] == markType)))
		{
			winAchieved = TRUE;
		}
	}

	return winAchieved;
}

uint8_t GameBoard::IsFull()
{
	uint8_t isFull = TRUE;

	for (int row = 0; row < GAMEBOARDSIZE; row++)
	{
		for (int column = 0; column < GAMEBOARDSIZE; column++)
		{
			if (boardLayout[row][column] == clearMark)
			{
				isFull = FALSE;
				break;
			}
		}

		if (isFull == FALSE)
		{
			break;
		}
	}

	return isFull;
}

uint8_t GameBoard::IsLocationFree(int row, int column)
{
	uint8_t isLocationFree = FALSE;

	if (boardLayout[row][column] == clearMark)
	{
		isLocationFree = TRUE;
	}
	else
	{
		isLocationFree = FALSE;
	}

	return isLocationFree;
}

int MinMax(GameBoard gb, PlayerMarkTypeDef currentTurn)
{
	if (gb.CheckWin(xMark) == TRUE)
	{
		return +10;
	}
	else if (gb.CheckWin(oMark) == TRUE)
	{
		return -10;
	}
	else if (gb.IsFull() == TRUE)
	{
		return 0;
	}

	PlayerMarkTypeDef nextTurn = (currentTurn == xMark) ? oMark : xMark;
	int heuristicValue[GAMEBOARDSIZE][GAMEBOARDSIZE];

	for (int row = 0; row < GAMEBOARDSIZE; row++)
	{
		for (int column = 0; column < GAMEBOARDSIZE; column++)
		{
			if (gb.IsLocationFree(row, column))
			{
				GameBoard copyBoard(gb);
				copyBoard.PlaceSpecificMark(row, column, currentTurn);
				heuristicValue[row][column] = MinMax(copyBoard, nextTurn);
			}
		}
	}

	int minVal = 0, maxVal = 0, firstTurn = TRUE;
	for (int row = 0; row < GAMEBOARDSIZE; row++)
	{
		for (int column = 0; column < GAMEBOARDSIZE; column++)
		{
			if (gb.IsLocationFree(row, column))
			{
				if (firstTurn == TRUE)
				{
					minVal = maxVal = heuristicValue[row][column];
					firstTurn = FALSE;
				}
				else
				{
					if (heuristicValue[row][column] > maxVal)
					{
						maxVal = heuristicValue[row][column];
					}

					if (heuristicValue[row][column] < minVal)
					{
						minVal = heuristicValue[row][column];
					}
				}
					
			}
		}
	}

	if (currentTurn == xMark)
	{
		return maxVal;
	}
	else
	{
		return minVal;
	}

}

CoordinateTypeDef GetBestMove(GameBoard gameBoard, PlayerMarkTypeDef currentTurn)
{
	CoordinateTypeDef pMin, pMax;
	int firstTurn = TRUE, min, max;
	
	PlayerMarkTypeDef nextTurn = (currentTurn == xMark) ? oMark : xMark;
	int heuristicValue[GAMEBOARDSIZE][GAMEBOARDSIZE];

	for (int row = 0; row < GAMEBOARDSIZE; row++)
	{
		for (int column = 0; column < GAMEBOARDSIZE; column++)
		{
			if (gameBoard.IsLocationFree(row, column))
			{
				GameBoard localCopy(gameBoard);
				localCopy.PlaceSpecificMark(row, column, currentTurn);
				heuristicValue[row][column] = MinMax(localCopy, nextTurn);
				if (firstTurn == TRUE)
				{
					firstTurn = FALSE;
					pMin.row = pMax.row = row;
					pMin.column = pMax.column = column;
					min = max = heuristicValue[row][column];
				}
				else
				{
				
					if (heuristicValue[row][column] > max)
					{
						max = heuristicValue[row][column];
						pMax.row = row;
						pMax.column = column;
					}

					if (heuristicValue[row][column] < min)
					{
						min = heuristicValue[row][column];
						pMin.row = row;
						pMin.column = column;
					}
				}
			}
		}
	}
	if (currentTurn == xMark)
	{
		return pMax;
	}
	else
	{
		return pMin;
	}
}