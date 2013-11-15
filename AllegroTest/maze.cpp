#include "Include.h"

int pac::direction(int y,int g, int h, float m[20][20])
{
	int turn = 1;
	float board[20][20];
	for (int row = 0; row < 20; row++) //display
			{
				for (int col = 0; col < 20; col++)
				{
					board[row][col] = m[row][col];
				}

			}

	// y is direction of ghost
	// g and h are coordinates of ghost	
	// 1 is up, 2 is right, 3 is down, 4 is left
	// if direction up or left and wall is up and left go right
	if((y == 1 || y == 4) && board[g-1][h] == false && board[g][h-1] == false) 
	{
		cout << "Right1" << endl;
		return 2;
	}
	// if direction up or right and wall is up and right go left
	if((y == 1 || y == 2) && board[g-1][h] == false && board[g][h+1] == false) 
	{
		cout << "Left1" << endl;
		return 4;
	}
	// if direction down or left and wall is down and left go right
	if((y == 3 || y == 4) && board[g+1][h] == false && board[g][h-1] == false) 
	{
		cout << "Right2" << endl;
		return 2;
	}
	// if direction down or right and wall is down and right go left
	if((y == 3 || y == 2) && board[g+1][h] == false && board[g][h+1] == false) 
	{
		cout << "Left2" << endl;
		return 4;
	}
	// if direction left or right and wall is left and right go up/down
	if((y == 4 || y == 2) && board[g][h-1] == false && board[g][h+1] == false)
	{
		if(turn == 1)
		{
			cout << "UP1" << endl;
			turn = 2;
			return 1;
		}
		if(turn == 2)
		{
			cout << "DOWN1" << endl;
			turn = 1;
			return 3;
		}
	}
	// if direction up or down and wall is up and down go left/right
	if((y == 1 || y == 3) && board[g-1][h] == false && board[g+1][h] == false)
	{
		if(turn == 1)
		{
			cout << "Left3" << endl;
			turn = 2;
			return 4;
		}
		if(turn == 2)
		{
			cout << "Right3" << endl;
			turn = 1;
			return 2;
		}
	}
	// if direction is up goes down
	if(y == 1 && board[g-1][h] == false)
	{
		cout << "D" << endl;
		return 3;
	}
	// if direction is right goes left
	if(y==2 && board[g][h+1] == false)
	{
		cout << "L" << endl;
		return 4;
	}
	// if direction is down goes up
	if(y==3 && board[g+1][h] == false)
	{
		cout << "U" << endl;
		return 1;
	}
	// if direction is left goes right
	if(y==4 && board[g][h-1] == false)
	{
		cout << "R" << endl;
		return 2;
	}
	
	
}
