//
// 
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool inPlay = true;

int max(int a, int b){
    if (a > b){
        return a;
    } else if (a == b){
        return a;
    } else{
        return b;
    }
}

int min(int a, int b){
    if (a < b){
        return a;
    } else if (a == b){
        return a;
    } else{
        return b;
    }
}

char oppositeColour(char colour)
{
    if (colour == 'W')
    {
        return 'B';
    }
    else if (colour == 'B')
    {
        return 'W';
    }
    else
    {
        return 'U';
    }
}
void printBoard(char board[][26], int n)
{
    printf("  ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", 'a' + i);
    }
    for (int row = 0; row < n; row++)
    {
        printf("\n%c ", 'a' + row);
        for (int col = 0; col < n; col++)
        {
            printf("%c", board[row][col]);
        }
    }
}

bool positionInBounds(int n, int row, int col)
{
    return row < n && col < n && row >= 0 && col >= 0;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    if (deltaRow == 0 && deltaCol == 0)
    {
        return false;
    }
    int length = 0;
    if (board[row][col] == 'U')
    {
        row += deltaRow;
        col += deltaCol;
        while (positionInBounds(n, row, col) && board[row][col] == oppositeColour(colour))
        {
            length++;
            row += deltaRow;
            col += deltaCol;
        }
    }
    else
    {
        return false;
    }
    if (positionInBounds(n, row, col) && length > 0 && board[row][col] == colour)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// int legalMoveLength(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
// {
//     if (deltaRow == 0 && deltaCol == 0)
//     {
//         return 0;
//     }
//     int length = 0;
//     if (board[row][col] == 'U')
//     {
//         row += deltaRow;
//         col += deltaCol;
//         while (positionInBounds(n, row, col) && board[row][col] == oppositeColour(colour))
//         {
//             length++;
//             row += deltaRow;
//             col += deltaCol;
//         }
//     }
//     if (positionInBounds(n, row, col) && length > 0 && board[row][col] == colour)
//     {
//         return length;
//     }
//     return 0;
// }

bool isLegal(char board[][26], int n, int row, int col, char colour)
{
    for (int drow = -1; drow < 2; drow++)
    {
        for (int dcol = -1; dcol < 2; dcol++)
        {
            // find legal moves in each location while looping through entire board
            if (checkLegalInDirection(board, n, row, col, colour, drow, dcol))
            {
                return true;
            }
        }
    }
    return false;
}

bool availableMoves(char board[][26], int n, char colour)
{
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (isLegal(board, n, row, col, colour))
            {
                return true;
            }
        }
    }
    return false;
}

// int availableMovesCount(char board[][26], int n, char colour){
//     int count = 0;
//     for (int row = 0; row < n; row++)
//     {
//         for (int col = 0; col < n; col++)
//         {
//             if (isLegal(board, n, row, col, colour))
//             {
//                 count++;
//             }
//         }
//     }
//     return count;
// }

void checkGame(char board[][26], int n)
{
    int bCount = 0;
    int wCount = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (board[row][col] == 'B')
            {
                bCount++;
            }
            else if (board[row][col] == 'W')
            {
                wCount++;
            }
        }
    }
    if (bCount > wCount)
    {
        printf("B player wins.\n");
    }
    else if (wCount > bCount)
    {
        printf("W player wins.\n");
    }
    else
    {
        printf("Draw!\n");
    }
}

int colourValue(char board[][26], int n, char colour)
{
    int count = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (board[row][col] == colour)
            {
                count++;
            }
        }
    }
    return count;
}

void flipTiles(char board[][26], int n, int move[3])
{
    if (isLegal(board, n, move[1], move[2], move[0]))
    {
        // Update board and flip tiles
        for (int drow = -1; drow < 2; drow++)
        {
            for (int dcol = -1; dcol < 2; dcol++)
            {
                int row = move[1];
                int col = move[2];
                char colour = move[0];
                // find legal moves in each location while looping through entire board
                if (checkLegalInDirection(board, n, row, col, colour, drow, dcol))
                {
                    while (true)
                    {
                        row += drow;
                        col += dcol;
                        board[row][col] = colour;
                        if (board[row + drow][col + dcol] == colour)
                        {
                            break;
                        }
                    }
                }
            }
        }
        board[move[1]][move[2]] = move[0];
    }
    else
    {
        printf("Invalid move.\n");
        // check who wins and end game
        checkGame(board, n);
        inPlay = false;
    }
}

// void copyBoard(char board[][26], char board_copy[][26], int n){
//     for (int i = 0; i < n; i++){
//         for (int j = 0; j < n; j++){
//             board_copy[i][j] = board[i][j];
//         }
//     }
//     return 0;
// }

// should just play a legal move and then minimax checks if its the best one
// int playMove(char board[][26], int n, char colour, int row, int col)
// {
//     // play the move at the current gamestate to determine the value of the move and return it to minimax
//     board[row][col] = colour;
//     return colourValue(board, n, colour) - colourValue(board, n, colourValue);
// }

void compMove(char board[][26], int n, char colour)
{
    // find available moves
    // Calculate score
    int highestScore = 0;
    int bestMove[3];
    bestMove[0] = colour;
    makeMove(board, n, bestMove[0], bestMove + 1, bestMove + 2);
    // Play best move
    printf("\nComputer places %c at %c%c.\n", colour, bestMove[1] + 'a', bestMove[2] + 'a');
    flipTiles(board, n, bestMove);
}

void printBoardP(char *board, int n)
{
    printf("  ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", 'a' + i);
    }
    for (int row = 0; row < n; row++)
    {
        printf("\n%c ", 'a' + row);
        for (int col = 0; col < n; col++)
        {
            printf("%c", *(board+row*26+col));
        }
    }
}

bool checkLegalInDirectionP(char *board, int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    if (deltaRow == 0 && deltaCol == 0)
    {
        return false;
    }
    int length = 0;
    if (*(board+row*26+col) == 'U')
    {
        row += deltaRow;
        col += deltaCol;
        while (positionInBounds(n, row, col) && *(board+row*26+col) == oppositeColour(colour))
        {
            length++;
            row += deltaRow;
            col += deltaCol;
        }
    }
    else
    {
        return false;
    }
    if (positionInBounds(n, row, col) && length > 0 && *(board+row*26+col) == colour)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int legalMoveLengthP(char *board, int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    if (deltaRow == 0 && deltaCol == 0)
    {
        return 0;
    }
    int length = 0;
    if (*(board+row*26+col) == 'U')
    {
        row += deltaRow;
        col += deltaCol;
        while (positionInBounds(n, row, col) && *(board+row*26+col) == oppositeColour(colour))
        {
            length++;
            row += deltaRow;
            col += deltaCol;
        }
    }
    if (positionInBounds(n, row, col) && length > 0 && *(board+row*26+col) == colour)
    {
        return length;
    }
    return 0;
}

bool isLegalP(char *board, int n, int row, int col, char colour)
{
    for (int drow = -1; drow < 2; drow++)
    {
        for (int dcol = -1; dcol < 2; dcol++)
        {
            // find legal moves in each location while looping through entire board
            if (checkLegalInDirectionP(board, n, row, col, colour, drow, dcol))
            {
                return true;
            }
        }
    }
    return false;
}

bool availableMovesP(char *board, int n, char colour)
{
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (isLegalP(board, n, row, col, colour))
            {
                return true;
            }
        }
    }
    return false;
}

int colourValueP(char *board, int n, char colour)
{
    int count = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (*(board+row*26+col) == colour)
            {
                count++;
            }
        }
    }
    return count;
}

void checkGameP(char *board, int n)
{
    int bCount = 0;
    int wCount = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (*(board+row*26+col) == 'B')
            {
                bCount++;
            }
            else if (*(board+row*26+col) == 'W')
            {
                wCount++;
            }
        }
    }
    if (bCount > wCount)
    {
        printf("B player wins.\n");
    }
    else if (wCount > bCount)
    {
        printf("W player wins.\n");
    }
    else
    {
        printf("Draw!\n");
    }
}

void flipTilesP(char *board, int n, int move[3])
{
    if (isLegalP(board, n, move[1], move[2], move[0]))
    {
        // Update board and flip tiles
        for (int drow = -1; drow < 2; drow++)
        {
            for (int dcol = -1; dcol < 2; dcol++)
            {
                int row = move[1];
                int col = move[2];
                char colour = move[0];
                // find legal moves in each location while looping through entire board
                if (checkLegalInDirectionP(board, n, row, col, colour, drow, dcol))
                {
                    while (true)
                    {
                        row += drow;
                        col += dcol;
                        *(board+row*26+col) = colour;
                        if (*(board+(row+drow)*26+(col+dcol)) == colour)
                        {
                            break;
                        }
                    }
                }
            }
        }
        *(board+move[1]*26+move[2]) = move[0];
    }
    else
    {
        printf("Invalid move.\n");
        // check who wins and end game
        checkGameP(board, n);
        inPlay = false;
    }
}

const int pointMatrix[8][8] = {
    {16, -3, 1, 0, 0, 1, -3, 16},
    {-4, -2, 0, -2, -2, 0, -2, -4},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, -2, 0, 0, 0, 0, -2, 0},
    {0, -2, 0, 0, 0, 0, -2, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {-4, -2, 0, -2, -2, 0, -2, -4},
    {16, -3, 1, 0, 0, 1, -3, 16}
};

int miniMax(char *board, int n, int row, int col, int depth, int alpha, int beta, bool maxPlayer, char colour)
{
    int maxEval = -99999;
    int minEval = 99999;
    int temp;
    bool endLoop = false;
    if (maxPlayer){
        temp = -999999;
    } else{
        temp = 999999;
    }

    if (depth <= 0)
    {
        return colourValueP(board, n, colour) - colourValueP(board, n, oppositeColour(colour)) - pointMatrix[row][col]; // value move
    }
    
    // iterate through each index of board
    for (int curRow = 0; curRow < n; curRow++){
        for (int curCol = 0; curCol < n; curCol++){
            // make a copy of the board
            char *board_copy = malloc(26*26); 
    
            // copy board
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    *(board_copy+i*26+j) = *(board+i*26+j);
                }
            }
            if (isLegalP(board_copy, n, curRow, curCol, colour)){
                int move[3] = {colour, curRow, curCol};
                flipTilesP(board_copy, n, move);
                if (maxPlayer)
                {
                    int eval = miniMax(board_copy, n, curRow, curCol, depth - 1, alpha, beta, false, colour);
                    maxEval = max(maxEval, eval);           
                    if (temp < eval){
                        temp = eval;
                    }
                    if (temp > beta){
                        bool endLoop = true;
                        break;
                    }
                    if (temp > alpha){
                        alpha = temp;
                    }
                }
                else
                {
                    int eval = miniMax(board_copy, n, curRow, curCol, depth - 1, alpha, beta, true, oppositeColour(colour));
                    minEval = min(minEval, eval);      
                    if (temp > eval){
                        temp = eval;
                    }
                    if (temp < alpha){
                        bool endLoop = true;
                        break;
                    }      
                    if (temp < beta){
                        beta = temp;
                    }
                }
            }
            free(board_copy);
        }
        if (endLoop){
            break;
        }
    }
    if (maxPlayer){
        return maxEval;
    } else{
        return minEval;
    }
    // based on highest value move adjust *row and *col
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col)
{
    // call minimax function
    int bestScore = -9999999;
    int bestRow = -1;
    int bestCol = -1;
    for (int curRow = 0; curRow < n; curRow++){
        for (int curCol = 0; curCol < n; curCol++){
            // make a copy of the board
            if (isLegal(board, n, curRow, curCol, turn)){
                char *board_copy = malloc(26*26); 
                // copy board
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++){
                        *(board_copy+i*26+j) = board[i][j];
                    }
                }
                int move[3] = {turn, curRow, curCol};
                flipTilesP(board_copy, n, move);
                int curScore = miniMax(board_copy, n, curRow, curCol, 3, -9999, 9999, false, turn);
                if (bestScore < curScore){
                    bestScore = curScore;
                    bestRow = curRow;
                    bestCol = curCol;
                }
                free(board_copy);
            }
        }
    }
    *row = bestRow;
    *col = bestCol;
    return 0;
}

void playerMove(char board[][26], int n, char colour)
{
    int move[3];
    move[0] = colour;
    int row;
    int col;
    findSmarterMove(board, n, colour, &row, &col);
    printf("\nTesting AI move (row, col): %c%c\n", move[1] + 'a', move[2] + 'a');
    move[1] = row;
    move[2] = col;
    // Play move
    flipTiles(board, n, move);
}

int main(void)
{
    // Create board
    int n;
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    char board[26][26];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 'U';
        }
    }
    board[n / 2][n / 2] = 'W';
    board[n / 2 - 1][n / 2 - 1] = 'W';
    board[n / 2 - 1][n / 2] = 'B';
    board[n / 2][n / 2 - 1] = 'B';
    // Choose black or white
    char c_colour;
    printf("\nComputer plays (B/W) : ");
    scanf("\n%c", &c_colour);
    printBoard(board, n);
    char p_colour = oppositeColour(c_colour);
    bool isCompMove, isPlayerMove;
    if (c_colour == 'B')
    {
        isCompMove = true;
        isPlayerMove = false;
    }
    while (inPlay)
    {
        // Play moves
        if (isCompMove)
        {
            if (availableMoves(board, n, c_colour))
            {
                compMove(board, n, c_colour);
                isCompMove = false;
                isPlayerMove = true;
                if (inPlay)
                {
                    printBoard(board, n);
                    printf("\n");
                }
            }
            else
            {
                printf("%c player has no valid move.\n", c_colour);
                isCompMove = false;
                isPlayerMove = true;
            }
        }
        else
        {
            if (availableMoves(board, n, p_colour))
            {
                playerMove(board, n, p_colour);
                isPlayerMove = false;
                isCompMove = true;
                if (inPlay)
                {
                    printBoard(board, n);
                    printf("\n");
                }
            }
            else
            {
                printf("%c player has no valid move.\n", p_colour);
                isPlayerMove = false;
                isCompMove = true;
            }
        }
        // Check score and if game is over
        // No available moves left
        if (availableMoves(board, n, 'B') == false && availableMoves(board, n, 'W') == false)
        {
            inPlay = false;
            checkGame(board, n);
        }
    }
    return 0;
}
