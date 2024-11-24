
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>  // Include this header for FLT_MAX

#define ROW 5
#define COL 5

typedef struct {
    int parent_i, parent_j;
    double f, g, h;
} Cell;

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point point;
    double f;
} OpenListNode;

int isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

int isUnblocked(int grid[][COL], int row, int col) {
    return grid[row][col] == 1;
}

int isDestination(int row, int col, Point dest) {
    return row == dest.x && col == dest.y;
}

double calculateHValue(int row, int col, Point dest) {
    return (double)sqrt((row - dest.x) * (row - dest.x) + (col - dest.y) * (col - dest.y));
}

void tracePath(Cell cellDetails[][COL], Point dest) {
    printf("The path is: ");
    int row = dest.x;
    int col = dest.y;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        printf("-> (%d,%d) ", row, col);
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    printf("-> (%d,%d)\n", row, col);
}

void aStarSearch(int grid[][COL], Point src, Point dest) {
    if (!isValid(src.x, src.y) || !isValid(dest.x, dest.y)) {
        printf("Source or Destination is invalid\n");
        return;
    }
    if (!isUnblocked(grid, src.x, src.y) || !isUnblocked(grid, dest.x, dest.y)) {
        printf("Source or Destination is blocked\n");
        return;
    }
    if (isDestination(src.x, src.y, dest)) {
        printf("We are already at the destination\n");
        return;
    }

    int closedList[ROW][COL];
    memset(closedList, 0, sizeof(closedList));

    Cell cellDetails[ROW][COL];
    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.x, j = src.y;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    OpenListNode *openList = (OpenListNode *)malloc(sizeof(OpenListNode) * ROW * COL);
    int openListSize = 0;

    openList[openListSize].point.x = i;
    openList[openListSize].point.y = j;
    openList[openListSize].f = 0.0;
    openListSize++;

    int foundDest = 0;

    while (openListSize > 0) {
        double minF = FLT_MAX;
        int minIndex = -1;

        for (int index = 0; index < openListSize; index++) {
            if (openList[index].f < minF) {
                minF = openList[index].f;
                minIndex = index;
            }
        }

        Point current = openList[minIndex].point;
        i = current.x;
        j = current.y;

        openListSize--;
        for (int index = minIndex; index < openListSize; index++) {
            openList[index] = openList[index + 1];
        }

        closedList[i][j] = 1;

        int rowOffset[] = {-1, 0, 1, 0};
        int colOffset[] = {0, 1, 0, -1};

        for (int direction = 0; direction < 4; direction++) {
            int newRow = i + rowOffset[direction];
            int newCol = j + colOffset[direction];

            if (isValid(newRow, newCol)) {
                if (isDestination(newRow, newCol, dest)) {
                    cellDetails[newRow][newCol].parent_i = i;
                    cellDetails[newRow][newCol].parent_j = j;
                    printf("Destination found\n");
                    tracePath(cellDetails, dest);
                    foundDest = 1;
                    break;
                } else if (!closedList[newRow][newCol] && isUnblocked(grid, newRow, newCol)) {
                    double gNew = cellDetails[i][j].g + 1.0;
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;

                    if (cellDetails[newRow][newCol].f == FLT_MAX || cellDetails[newRow][newCol].f > fNew) {
                        openList[openListSize].point.x = newRow;
                        openList[openListSize].point.y = newCol;
                        openList[openListSize].f = fNew;
                        openListSize++;

                        cellDetails[newRow][newCol].f = fNew;
                        cellDetails[newRow][newCol].g = gNew;
                        cellDetails[newRow][newCol].h = hNew;
                        cellDetails[newRow][newCol].parent_i = i;
                        cellDetails[newRow][newCol].parent_j = j;
                    }
                }
            }
        }

        if (foundDest)
            break;
    }

    if (!foundDest)
        printf("Failed to find the Destination Cell\n");

    free(openList);
}

int main() {
    int grid[ROW][COL];
    printf("Enter the grid (5x5 matrix) where 1 is a valid cell and 0 is an obstacle:\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    Point src, dest;
    printf("Enter source coordinates (row and column): ");
    scanf("%d %d", &src.x, &src.y);

    printf("Enter destination coordinates (row and column): ");
    scanf("%d %d", &dest.x, &dest.y);

    aStarSearch(grid, src, dest);

    return 0;
}
