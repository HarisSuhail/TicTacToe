// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameBoard.h"


CoordinateTypeDef GetCoordinates(GameBoard gb);

int main()
{
	GameBoard gb(xMark); //Frst Turn
	uint8_t gameComplete = FALSE;
	PlayerMarkTypeDef currentTurn = xMark;

	while (gameComplete == FALSE)
	{
		gb.DisplayBoard();
		if (gb.CheckWin(xMark) == TRUE)
		{
			cout << endl << "X WINS!";
			gameComplete = TRUE;
		}
		else if (gb.CheckWin(oMark) == TRUE)
		{
			cout << endl << "O WINS!";
			gameComplete = TRUE;
		}
		else if (gb.IsFull() == TRUE)
		{
			cout << endl << "IT'S A DRAW!";
			gameComplete = TRUE;
		}

		if (gameComplete == TRUE)
		{
			break;
		}


		if (currentTurn == xMark)
		{
			cout << endl << endl << "X's Turn" << endl;

			CoordinateTypeDef points = GetCoordinates(gb);

			gb.PlaceSpecificMark(points.row, points.column, xMark);

			currentTurn = oMark;
		}
		else
		{
			cout << endl << endl << "O's Turn" << endl;

			CoordinateTypeDef points = GetBestMove(gb, oMark);

			gb.PlaceSpecificMark(points.row, points.column, oMark);

			currentTurn = xMark;
		}

	}
}


CoordinateTypeDef GetCoordinates(GameBoard gb)
{
	uint8_t acquisitionComplete = FALSE;
	CoordinateTypeDef localPoints;
	localPoints.row = localPoints.column = -1;

	do {
		cout << endl << "Enter coordinates: ";
		cin >> localPoints.row >> localPoints.column;
		if (((localPoints.row >= 0) && (localPoints.row < GAMEBOARDSIZE)) && ((localPoints.column >= 0) && (localPoints.column < GAMEBOARDSIZE)) && gb.IsLocationFree(localPoints.row, localPoints.column))
		{
			acquisitionComplete = TRUE;
		}
		else
		{
			cout << endl << "INVALID";
		}
	} while (acquisitionComplete == FALSE);

	return localPoints;

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
