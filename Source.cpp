#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#define BOMB '*'
#define uncoverdCell '+' 
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define UserPos '$'
#define pressCommand 'p'


using namespace std;

int rows = 9, columns = 9, bombs = 10, isGameFinished = 0;
char board[100][100],userBoard[100][100];
bool uncovered[100][100];
int userRow = 0;
int userCol = 0;

bool isInside(int row,int col)
{
	return(0 <= row && row < rows && 0 <= col && col < columns);
}
void placeBombs()
{
	vector<pair<int, int>>positions;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			positions.push_back(make_pair(row, col));
		}

	}
	random_shuffle(positions.begin(), positions.end());
	for(int i=0;i<bombs;i++)
	{
		board[positions[i].first][positions[i].second] = BOMB;
	}

}


int computeNeighbours(int row,int col)
{
	int numOfBomb=0;
	for(int rowOffset=-1;rowOffset<=1;rowOffset++)
	{
		for(int colOffset=-1;colOffset<=1;colOffset++)
		{
			int nextRow = row + rowOffset,nextCol=col+colOffset;
			if(isInside(nextRow,nextCol)&&board[nextRow][nextCol] == BOMB)
			{
				++numOfBomb;
			}
		}
	}
	return(numOfBomb);
	
}

void intializeBoard()
{
	for (int row = 0; row < rows; row++) 
	{
		for(int col=0;col<columns;col++)
		{
			board[row][col]=userBoard[row][col] = uncoverdCell ;
		}
	}
	placeBombs();
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			if (board[row][col] != BOMB)
			{
				board[row][col] = computeNeighbours(row, col) + '0';
			}
		}
	}
}

void printBoard()
{
	for(int row=0;row<rows;row++)
	{
		for(int col=0;col<columns;col++)
		{
			cout<<" " << userBoard[row][col];
		}
		cout << "\n";
	}
}

void triggerPress(int row,int col)
{
	if(uncovered[row][col])
	{
		return;
	}
	if(board[row][col]==BOMB)
	{
		isGameFinished = 1;
		cout << "GAME OVER!!!!!!\n";
		for(int row=0;row<rows;row++)
		{
			for(int col=0;col<columns;col++)
			{
				if(board[row][col]==BOMB)
				{
					cout<<" " << BOMB;
				}
				else
				{
					cout <<" " << userBoard[row][col];

				}
				
			}
			cout << "\n";
		}
		
		
		cout << "GAME OVER!!!!!!\n";
		cout << "\n\n"; 
		
	}
	else
	{
		uncovered[row][col] = 1;
		userBoard[row][col] = board[row][col];
		if(userBoard[row][col]=='0')
		{
			for(int rowOffset=-1;rowOffset<=1;rowOffset++)
			{
				for(int colOffset=-1;colOffset<=1;colOffset++)
				{
					int nextRow = row + rowOffset, nextCol = col + colOffset;
					if(isInside(nextRow,nextCol))
					{
						triggerPress(nextRow, nextCol);
					}
				}
			}
		}
	}
}

void processCommand(char command)
{
	int nextRow = userRow,nextCol=userCol;
	if(command==UP)
	{
		--nextRow;
	}
	else if(command==DOWN)
	{
		++nextRow;
	}
	else if(command==LEFT)
	{
		--nextCol;
	}
	else if(command==RIGHT)
	{
		++nextCol;
	}
	if(!isInside(nextRow,nextCol))
	{
		return;
	}
	if(!uncovered[userRow][userCol])
	{
		userBoard[userRow][userCol] = uncoverdCell;
	}
	else
	{
		userBoard[userRow][userCol] = board[userRow][userCol];
	}
	
	userRow = nextRow;
	userCol = nextCol;
	userBoard[userRow][userCol] = UserPos;

	if(command==pressCommand)
	{
		triggerPress(userRow, userCol);
	}
}

bool checkGameFinished()
{
	int covered = 0;
	for(int row=0;row<rows;row++)
	{
		for(int col=0;col<columns;col++)
		{
			covered += 1 - uncovered[row][col];
		}
	}
	if(covered==bombs)
	{
		cout << "CONGRATS!!!!!!\nYOU  WON THE GAME!!!!!!!!\n";
		isGameFinished = 1;
		return true;
	}
	return false;
}

void startGame()
{
	userRow = userCol = 0;
	isGameFinished = 0;
	intializeBoard();
	userBoard[userRow][userCol] = UserPos;
}
int main()
{
	srand(time(0));
	startGame();
	while (!isGameFinished)
	{
		printBoard();
		char command;
		cout << "Enter (W)UP (S)DOWN (A)LEFT (D)RIGHT (P)SELECT\n";
		cin >> command;
		processCommand(command);
		isGameFinished = checkGameFinished();
	}
	

	return 0;
}