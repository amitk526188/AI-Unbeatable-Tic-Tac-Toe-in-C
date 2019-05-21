/*****************************************************************************************
DAA Project
Amit Kumar 
PES1201701295
Section : B

                Minimax algorithm with Alpha-Beta Pruning
                            Tic-Tac-Toe
******************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

// Structure that keep a record of the score and move for a particular state of the state space tree.
typedef struct result{
    int r_move;
    int c_move;
    int score;
} Result;

//Function declarations.
void printGame(int **game , int N);
bool hasGameEnded(int** game , int N);
int score(int** game, int depth , int N);
bool hasPlayerWon(int** game, int player , int N);
bool isTerminalState(int** game , int N);
void computeAndPlayBestMove(int** game, int player , int N);
Result* minTurn(int** game, int depth, int alpha, int beta, int N);
Result* maxTurn(int** game, int depth, int alpha, int beta, int N);

static int X = 1;   // The maximiser player (The player)
static int O = -1;  // The minimiser player (The computer)
static int E = 0;   // Value denoting an unplayed cell 
int main(){
    // Game starts off with a current state of the board
    int N = 3; //size of the board
    int** game = (int**)malloc(sizeof(int*)* N);
    int choose;
    // Either start a fresh game or with some other state of the game.
    printf("Enter 0 to start a new game , 1 to start with your chosen state: \n");
    scanf("%d",&choose);
    if(!choose){
        for(int i=0;i<N;i++){
            game[i] = (int*)malloc(sizeof(int)*N); 
            for(int j=0;j<N;j++){
                game[i][j]=0;
            }
        }
    }
    else if(choose){
        printf("Enter a VALID current state of the board such next turn is yours:\n");
        for(int i=0;i<N;i++){
            game[i] = (int*)malloc(sizeof(int)*N); 
            for(int j=0;j<N;j++){
                scanf("%d",&game[i][j]);
            }
        }
    }
    
    // First player chance will be given to the person playing against computer 
    int currentPlayer = X;
    int row,col;

    printf("Continue the game, You are player X\n");
    while (true) {
        printGame(game,N);
        if (currentPlayer == X) {
            printf("It is X's turn. Enter row and column (1 indexed) -");
            scanf("%d %d",&row,&col);
            row = row - 1;
            col = col - 1;
            if (game[row][col] == E) {  //Allowed to play only is the cell was initially empty
                game[row][col] = X;
                currentPlayer = O;
            } 
            else {
                printf("\nEntered row and column is already played!\n");
            }
        } 
        else {    // Player O's turn(computer)
            printf("It is O's turn.\n");
            computeAndPlayBestMove(game, O, N);
            currentPlayer = X;
            }
        if (isTerminalState(game, N)) {
            break;
        }
    }

    // Checking the final result of the game.
    if (hasPlayerWon(game, X, N)) {
        printf("Player X has won!\n");
    } 
    else if (hasPlayerWon(game, O, N)) {
        printf("Player O has won!\n");
    } 
    else {
        printf("It is a draw!\n");
    }
    printGame(game,N);
}

//prints out the current state of the game.
void printGame(int **game , int N){
    printf("State of the game:\n");
    for (int i = 0; i < N ; i++) {
            for (int j = 0; j < N; j++) {
                if (game[i][j] == X) {
                    printf("X ");
                } 
                else if (game[i][j] == O) {
                    printf("O ");
                } 
                else {
                    printf("_ ");
                }
            }
            printf("\n");
        }
}

//checks whether the game has ended or not. A game ends when all the cells have been played in.
bool hasGameEnded(int** game , int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (game[i][j] == E) {
                return false;
            }
        }
    }
    return true;
}

// Score function is a static evaluater for the leaf nodes.
// It computes the score attained by the player based on the depth of the tree ie 
// the number of chances it took him to win the game.
// Score for a draw game or otherwise is 0.
// Score for the minimiser player is negative , 10 - Depth
// Score for the maximiser player is postive , Depth - 10 
// 10 is an arbitrary chosen value which is greater than the possible depth of the tree.
int score(int** game, int depth , int N) {
    if (hasPlayerWon(game, X , N)) {
        return 10 - depth;
    } 
    else if (hasPlayerWon(game, O , N)) {
            return depth - 10;
    }
        
    return 0;
}

// Function checks if the "player" has played a winning move and won the game.
// Winning is equivalent to getting same symbols along any row, any column or along one of the diagonals.
bool hasPlayerWon(int** game, int player , int N) {
    for (int i = 0; i < N; ++i) {
        bool isRowEqual = true, isColumnEqual = true;
        for (int j = 0; j < N; ++j) {
            if (game[i][j] != player) {
                isRowEqual = false;
            }
            if (game[j][i] != player) {
                isColumnEqual = false;
            }
        }
        if (isRowEqual || isColumnEqual) {
            return true;
        }
    }
    bool isDiagonalEqual = true, isAntiDiagonalEqual = true;
    for (int i = 0; i < N; ++i) {
        if (game[i][i] != player) {
            isDiagonalEqual = false;
        }
        if (game[N - 1 - i][i] != player) {
            isAntiDiagonalEqual = false;
        }
    }
        return isDiagonalEqual || isAntiDiagonalEqual;
}

// Checks if the game has reached a Terminal state.
// Terminal state happens when either one of the players has won the game or the game has ended(no cells left to play)
bool isTerminalState(int** game , int N) {
        return hasPlayerWon(game, X, N) || hasPlayerWon(game, O , N) || hasGameEnded(game,N);
    }




// Minimax algorithm entry method. Uses minTurn() and maxTurn() to compute the best move for the current player and plays that move.
// Once the structure(score,move) is returned by the called functions , the current state of the game is updated.
// -1 is fail safe value used in the minTurn() and maxTurn() function.
void computeAndPlayBestMove(int** game, int player , int N) {
    Result *result;
    if (player == X) {
            result = maxTurn(game, 0, INT_MIN, INT_MAX, N);
    }
    else {
            result = minTurn(game, 0, INT_MIN, INT_MAX , N);
    }
    if(result->c_move != -1 && result->r_move != -1){
            game[result->r_move][result->c_move] = player;
    }
    else{
        return;
    }
}
    


// Method to compute best move for player O (minimising player)
// Recursively calls maxTurn()
// move (r  or  c) is set to -1 when no further move is possible => End condition. It's a fail safe value.
Result* minTurn(int** game, int depth, int alpha, int beta, int N) {
        if (isTerminalState(game,N)) {
            //Thus no move is possible, leaf node reached or the player won.
            Result *res = (Result*)malloc(sizeof(Result));
            res->score = score(game,depth,N);
            res->r_move = -1;
            res->c_move = -1;
            return res;
        }
        Result* currentMove;
        Result *min = (Result*)malloc(sizeof(Result));
        min->score = INT_MAX;
        min->r_move = -1;
        min->c_move = -1;
        
        //iterating through each of the cells and looking for a cell that is empty 
        // Furthur computer makes a temporary move and check the outcome based on the move  maxplayer(The player) can make.  
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (game[i][j] == E) {
                    game[i][j] = O;
                    
                    // Recurse for other moves
                    currentMove = maxTurn(game, depth + 1, alpha, beta,N);
                    
                    game[i][j] = E; // revert the move
                    
                    if (currentMove->score < min->score) {
                        min->score = currentMove->score;
                        min->r_move = i;
                        min->c_move = j;
                    }
                    
                    if (currentMove->score <= alpha) {
                        return min;
                    }
                    
                    if (currentMove->score < beta) {
                        beta = currentMove->score;
                    }
                }
            }
        }
        
        return min;
    }
    
    // Method to compute best move for player X (maximising player)
    // Recursively calls minTurn()
    Result* maxTurn(int** game, int depth, int alpha, int beta, int N) {
        if (isTerminalState(game,N)) {
            Result *res = (Result*)malloc(sizeof(Result));
            res->score = score(game,depth,N);
            res->r_move = -1;
            res->c_move = -1;
            return res;
        }

        Result* currentMove;
        Result *max = (Result*)malloc(sizeof(Result));
        max->score = INT_MIN;
        max->r_move = -1;
        max->c_move = -1;


        //iterating through each of the cells and looking for a cell that is empty 
        // Furthur we make a temporary move and check the outcome based on the move  minplayer(The computer ) can make. 
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (game[i][j] == E) {
                    game[i][j] = X;
                    
                    // Recurse for other moves
                    currentMove = minTurn(game, depth + 1, alpha, beta,N);
                    
                    game[i][j] = E; // revert the move
                    
                    if (currentMove->score > max->score) {
                        max->score = currentMove->score;
                        max->r_move = i;
                        max->c_move = j;
                    }
                    
                    if (currentMove->score >= beta) {
                        return max;
                    }
                    
                    if (currentMove->score > alpha) {
                        alpha = currentMove->score;
                    }
                }
            }
        }
        
        return max;
    }