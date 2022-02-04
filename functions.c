/*********************************************************
INSTRUCTIONS ON HOW TO COMPILE AND RUN THE PROGRAM:
Compiling: gcc givenA2.c functions.c -std=c99 -Wall
Running:   ./a.out
*********************************************************/

#include "givenA2.h"

//1. createInitialBoard - This function creates the initial 3 X 3 board that the user is shown along with the instructions on what character;X/O the user is assigned for the game. It features a '?' in each cell as an indication of an empty cell.
void createInitialBoard(char board[N][N])
{
    int i;
    int j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            board[i][j] = '?';
            if(j == 2)
            {
                printf(" %c\n", board[i][j]); //This checks whether the column for which the board layout is being printed is the 3rd column so that it does not print the vertical bar on the right-hand side of the cells in the 3rd column
            }

            else
            {
                printf(" %c |", board[i][j]);
            }
        }
        
        if(i != 2)
        {
            printf("-----------\n");
        }
    }
}


//2. isBoardFull - This function checks to see whether there is an empty cell in the board, whenever it is called in the main. It returns 1 if there is no empty cell on the board and 0 otherwise.
int isBoardFull(char board[N][N])
{
    int i;
    int j;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            if(board[i][j] == '?')
            {
                return 0;
            }
        }
    }

    return 1;
}


//3. isInputValid - This function checks to see if the row and column numbers entered by the user are between and including the minimum value; 1 and the maximum value; 3.
int isInputValid(int entered, int minimum, int maximum)
{
    if((entered >= minimum) && (entered <= maximum))
    {
        return 1;
    }

    return 0;
}


//4. readUserMove - This function prompts the user to enter their desired row and column numbers between 1 and 3.
//                  This function also updates the number of steps/turns that the user plays in case the user wins, so that it can output the number of steps the user took to win against the computer in single game.
void readUserMove(int *userRow, int *userCol, int *stepsWon)
{
    printf("\nYour move - enter numbers between 1 and 3\n\n");

    printf("Enter row number: ");
    scanf("%d", userRow);
    //printf("\n");


    printf("Enter column number: ");
    scanf("%d", userCol);
    printf("\n");

    *stepsWon = *stepsWon + 1; //Used to check the number of steps taken by the user to win against the computer in a game.
}


//5. all_sums - This function calculates the sum of scores across each row, column, left diagonal, right diagonal.
//              It does so by taking into account that the player's symbol 'X' is assigned a score of 1, the computer's symbol 'O' is assigned a score of 4, the empty cell's symbol '?' is assigned a score of 0.
//              It is also called by the functions, computerPlaysToWin, computerPlaysToBlock and gameWon. 
void all_sums(char board[N][N], int sumR[N], int sumC[N], int *sumLD, int *sumRD)
{
    int boardCount[N][N];
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 'X') 
            {
                boardCount[i][j] = 1;
            }
            
            if (board[i][j] == 'O') 
            {
                boardCount[i][j] = 4;
            }
            
            if (board[i][j] == '?') 
            {
                boardCount[i][j] = 0;
            }
        }
    }

    sumR[0] = boardCount[0][0] + boardCount[0][1] + boardCount[0][2];
    sumR[1] = boardCount[1][0] + boardCount[1][1] + boardCount[1][2];
    sumR[2] = boardCount[2][0] + boardCount[2][1] + boardCount[2][2];

    sumC[0] = boardCount[0][0] + boardCount[1][0] + boardCount[2][0];
    sumC[1] = boardCount[0][1] + boardCount[1][1] + boardCount[2][1];
    sumC[2] = boardCount[0][2] + boardCount[1][2] + boardCount[2][2];

    *sumLD = boardCount[0][0] + boardCount[1][1] + boardCount[2][2];
    *sumRD = boardCount[0][2] + boardCount[1][1] + boardCount[2][0];
}



//6. computerPlaysToWin - This function checks whether there are 2 'O's in any row, column or diagonal by calling the all_sums function to see if the score in any of the rows, columns, diagonals is equal to 8.
//                        If so, it checks the cell not occupied by a 'O' in either row, colum or diagonal, and if the cell is occupied by a '?', the cell is assigned with the computer's symbol 'O' and the computer wins. 
int computerPlaysToWin(char board[N][N], int *cRow, int *cCol)
{
    int i;
	  int j;
	  int sumR[N];
    int sumC[N];
    int sumLD;
    int sumRD;

    all_sums(board, sumR, sumC, &sumLD, &sumRD);

    //For Rows:
    for(i = 0; i < N; i++)
    {
    	if(sumR[i] == 8)
    	{
    		for(j = 0; j < N; j++)
    		{
    			if(board[i][j] == '?')
    			{
    				board[i][j] = 'O';
    				*cRow = i;
                    *cCol = j;
                    return 1;
    			}
    		}
    	}
    }

    //For Columns:
    for(i = 0; i < N; i++)
    {
    	if(sumC[i] == 8)
    	{
    		for(j = 0; j < N; j++)
    		{
    			if(board[j][i] == '?')
    			{
    				board[j][i] = 'O';
    				*cRow = j;
                    *cCol = i; 
                    return 1;
    			}
    		}
    	}
    }

    //For Left Diagonal:
    for(i = 0; i < N; i++)
    {
    	if(sumLD == 8)
    	{
    		if(board[i][i] == '?')
    		{
    			board[i][i] = 'O';
    			*cRow = i;
                *cCol = i;
                return 1;
    		}
    	}
    }

    //For Right Diagonal:  
    for(i = 0; i < N; i++)
    {
    	if(sumRD == 8)
    	{
    		if(board[i][2 - i] == '?')
    		{
    			board[i][2 - i] = 'O';
    			*cRow = i;
                *cCol = 2 - i;
                return 1;
    		}
    	}
    }

    return 0;
}

    

//7. computerPlaysRandom - Randomly sets the computer's move if the computer cannot win.
void computerPlaysRandom(int *cRow , int *cCol)
{
    *cRow = (rand() % 3) + 0;
    *cCol = (rand() % 3) + 0;
}


//8. computerPlaysToBlock - This function checks to see if there are 2 'X's already within any row/column/diagonal and then checks to see if there is an empty cell assigned with a '?' in that particular row/column/diagonal.
//                          If so, this function then assigns that empty cell with the computer's symbol 'O' therefore, blocking the user's move/chance to win the game. 
int computerPlaysToBlock(char board[N][N], int *cRow , int *cCol)
{
	  int i;
    int j;
    int sumR[N];
    int sumC[N];
    int sumLD;
    int sumRD;

    all_sums(board, sumR, sumC, &sumLD, &sumRD);

    //For Rows:
    for(i = 0; i < N; i++)
    {
        if(sumR[i] == 2)
        {
            for(j = 0; j < N; j++)
            {
                if(board[i][j] == '?')
                {
                    board[i][j] = 'O';
                    *cRow = i;
                    *cCol = j;
                    return 1;
                }
            }
        }
    }

    //For Columns:
    for(i = 0; i < N; i++)
    {
        if(sumC[i] == 2)
        {
            for(j = 0; j < N; j++)
            {
                if(board[j][i] == '?')
                {
                    board[j][i] = 'O';
                    *cRow = j;
                    *cCol = i; 
                    return 1;
                }
            }
        }
    }

    //For Left Diagonal:
    for(i = 0; i < N; i++)
    {
        if(sumLD == 2)
        {
            if(board[i][i] == '?')
            {
                board[i][i] = 'O';
                *cRow = i;
                *cCol = i;
                return 1;
            }
        }
    }

    //For Right Diagonal:  
    for(i = 0; i < N; i++)
    {
        if(sumRD == 2)
        {
            if(board[i][2 - i] == '?')
            {
                board[i][2 - i] = 'O';
                *cRow = i;
                *cCol = 2 - i;
                return 1;
            }
        }
    }

    return 0;
}




//9. gameWon - This function checks to see whether there is a winner at some point in the game by checking if the score in any row/column/diagonal = 3(the user won) or 12(the computer won) and then returning 1.
//             Else if there is no winner, the function returns 0.
int gameWon(char board[N][N], char symbol)
{
    int sumR[N];
    int sumC[N];
    int sumLD;
    int sumRD;

    all_sums(board, sumR, sumC, &sumLD, &sumRD);
    
    if((sumR[0] == 3) || (sumR[1] == 3) || (sumR[2] == 3) || (sumC[0] == 3) || (sumC[1] == 3) || (sumC[2] == 3) || (sumLD == 3) || (sumRD == 3))
    {
        symbol = 'X'; //Symbol assigned with X if user wins.
        return 1;
    }

    else if((sumR[0] == 12) || (sumR[1] == 12) || (sumR[2] == 12) || (sumC[0] == 12) || (sumC[1] == 12) || (sumC[2] == 12) || (sumLD == 12) || (sumRD == 12))
    {
        symbol = 'O';  //Symbol assigned with O if computer wins.
        return 1;
    }

    return 0;
}


//10. printCurrentBoard - This function prints the updated 3 X 3 board after every turn the user and computer have in the game.
void printCurrentBoard(char board[N][N])
{
    int i;
    int j;

    printf("\nCurrent board now is: \n\n");
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(j == 2)
            {
                printf(" %c\n", board[i][j]); //This checks whether the column for which the board layout is being printed is the 3rd column so that it does not print the vertical bar on the right-hand side of the cells in the 3rd column.
            }

            else
            {
                printf(" %c |", board[i][j]);
            }
        }
        
        if(i != 2)
        {
            printf("-----------\n");
        }
    }
}



//11. This function returns 1 if a value exists in an array else the function returns 0.
int memberOf(int value, int someArray[N])
{
    int i;

    for(i = 0; i < N; i++)
    {
        if(someArray[i] == value)
        {
            return 1;
        }
    }

    return 0;
}
