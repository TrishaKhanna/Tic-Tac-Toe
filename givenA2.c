#include "givenA2.h"

int main(){
    
    int userRow, userCol, computerRow, computerCol;
    int taken;
    int count = 1;
    int stepsWon = 0;
    
    char board[N][N];
    char winner = 'N';
    
    srand((int) time(0));
    
    printf ("This tic-tac-toe board is of size %d by %d\n", N, N);
    
    printf ("You are using symbol X and the computer program is using symbol O\n");
    
    printf ("Here is the board - spaces are indicated by a ?\n");
    
    createInitialBoard (board);
    
    while ((winner != 'Y') && !(isBoardFull(board)))
    {
        taken = 0;
        
        while (!(taken))
        {
            readUserMove(&userRow, &userCol, &stepsWon);
            printf("You chose row %d and column %d \n", userRow, userCol);
            
            while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))
            {
                printf("That's is an invalid row or column number - try again\n");
                readUserMove(&userRow, &userCol, &stepsWon);
                printf("You chose row %d and column %d \n", userRow, userCol);
            }
            
            if (board[userRow-1][userCol-1] == '?')
            {
                board[userRow-1][userCol-1] = 'X';
                taken = 1;
                count++;
                
            }
            else
            {
                taken = 0;
                printf("That spot is taken - please try another one\n");
            }
        }
        
        if (gameWon(board, 'X'))   //user won
        {
            printf("Congrats - you won against the computer :) in %d steps\n", stepsWon);
            winner = 'Y';
        }
        
        else  if (!(isBoardFull(board)))            //check computer's move if the board is not yet full
        {
            taken = 0;
            
            while (!(taken))
            {
                taken = getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1);
                
                if (taken) {
                    break;
                }
                
                getchar();
                
                if (board[computerRow][computerCol] == '?')
                {
                    board[computerRow][computerCol] = 'O';
                    taken = 1;
                    
                }
                else
                {
                    taken = 0;
                    //printf("That spot is taken - computer - try another one\n");
                }
            }
            printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
            if (gameWon(board, 'O'))
            {
                printf("Oh the computer won this time :(( think hard next time\n");
                winner = 'Y';
            }
        }
        
        printCurrentBoard (board);
        
        if (winner != 'Y') {
           printf("Enter to continue \n");
        }
        getchar();
        
    } //end of while
    
    if (winner != 'Y') {
       printf("Game was a tie - no winner!\n\n");
    }
    return 0;
}

/* In function getComputerMove , the computer tries to win the game first; if it cannot win, then
 
 1. for those who are not attempting the 10% additional functionality
     - the computer then decides to play randomly
 2. for those who are attempting the 10% additional functionality
     - the computer then tries to block the user's game
     - if it does not succeed in blocking, then it makes a random move
 */

int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
    
    int winningSpot = 0;
    
    winningSpot = computerPlaysToWin(board, computerRow, computerCol);
    
    /*
     if the computer does not find a winning spot, then it either play randomly or blocks
     */
    
    if (!winningSpot)
    {
        // comment the next line if you are attempting the 2% functionality
        computerPlaysRandom(computerRow, computerCol);
        
        /* uncomment the next few  lines if you are attempting the 2% functionality
        int blocked = 0;
         
         blocked = computerPlaysToBlock(board, computerRow, computerCol);
         if (blocked == 0) {
            computerPlaysRandom(computerRow, computerCol);
         }
         
         return blocked;
         */
    }
    
    return winningSpot;
}
