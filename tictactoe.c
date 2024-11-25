#include <stdio.h>

#define SIZE 3

void initializeBoard(char board[SIZE][SIZE]) 
{
    int count = 1;
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            board[i][j] = count + '0';
            count++;
        }
    }
}


void printBoard(char board[SIZE][SIZE]) 
{
    printf("\n");
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) 
               printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) 
           printf("---|---|---\n");
    }
    printf("\n");
}


int checkWin(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) 
           return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) 
           return 1;
    }

    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
       return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
       return 1;

    return 0;
}


int checkDraw(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                return 0;
            }
        }
    }
    return 1;
}


int makeMove(char board[SIZE][SIZE], int move, char playerMark) 
{
    if (move < 1 || move > 9) 
    return 0;

    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;

    if (board[row][col] != 'X' && board[row][col] != 'O') 
    {
        board[row][col] = playerMark;
        return 1;
    }
    return 0;
}


int main() 
{
    char board[SIZE][SIZE];
    int move;
    int currentPlayer = 1;
    char playerMark;

    initializeBoard(board);

    while (1) 
    {
        printBoard(board);
        if(currentPlayer == 1)
           playerMark =  'X';
        else
           playerMark = 'O'; 

        printf("Player %d (%c), enter your move (1-9): ", currentPlayer, playerMark);
        scanf("%d", &move);

        if (makeMove(board, move, playerMark)) 
        {
            if (checkWin(board)) 
            {
                printBoard(board);
                printf("Player %d wins!\n", currentPlayer);
                break;
            }

            \
            if (checkDraw(board)) 
            {
                printBoard(board);
                printf("It's a draw!\n");
                break;
            }

            if(currentPlayer == 1) 
               currentPlayer = 2; 
            else
               currentPlayer = 1;
        } 
        else 
        {
            printf("Invalid move! Try again.\n");
        }
    }

    return 0;
}
