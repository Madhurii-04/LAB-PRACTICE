#include <stdio.h>
#include <limits.h>

#define SIZE 3
char board[SIZE][SIZE];

void printBoard();
int isMovesLeft();
int evaluate();
int minimax(int depth, int isMax);
void makeMove(int move, char player);
int findBestMove();
int checkWin();

void initializeBoard() {
    int count = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '1' + (count - 1);
            count++;
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
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

int isMovesLeft() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 1; 
        }
    }
    return 0;
}

int evaluate() {
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'O')
                return +10;
            else if (board[row][0] == 'X')
                return -10;
        }
    }

    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'O')
                return +10;
            else if (board[0][col] == 'X')
                return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'O')
            return +10;
        else if (board[0][0] == 'X')
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'O')
            return +10;
        else if (board[0][2] == 'X')
            return -10;
    }

    return 0;
}

int minimax(int depth, int isMax) {
    int score = evaluate();

    if (score == 10)
        return score;
    if (score == -10)
        return score;

    if (!isMovesLeft())
        return 0;

    if (isMax) {
        int best = INT_MIN;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = 'O';

                    best = (best > minimax(depth + 1, 0)) ? best : minimax(depth + 1, 0);
                    board[i][j] = backup; 
                }
            }
        }
        return best;
    } 
    else {
        int best = INT_MAX;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = 'X';

                    best = (best < minimax(depth + 1, 1)) ? best : minimax(depth + 1, 1);
                    board[i][j] = backup;
                }
            }
        }
        return best;
    }
}

int findBestMove() {
    int bestVal = INT_MIN;
    int bestMove = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];
                board[i][j] = 'O';

                int moveVal = minimax(0, 0);
                board[i][j] = backup;
                
                if (moveVal > bestVal) {
                    bestMove = i * SIZE + j + 1;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void makeMove(int move, char player) {
    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;
    board[row][col] = player;
}

int main() {
    int playerMove, aiMove;
    initializeBoard();
    printBoard();

    while (isMovesLeft() && evaluate() == 0) {
        printf("Enter your move (1-9): ");
        scanf("%d", &playerMove);

        makeMove(playerMove, 'X');
        printBoard();

        if (!isMovesLeft() || evaluate() != 0) break;

        aiMove = findBestMove();
        printf("AI chooses move: %d\n", aiMove);
        makeMove(aiMove, 'O');
        printBoard();
    }

    int result = evaluate();
    if (result == 10) 
        printf("AI wins!\n");
    else if (result == -10)
        printf("You win!\n");
    else
        printf("It's a draw!\n");

    return 0;
}
