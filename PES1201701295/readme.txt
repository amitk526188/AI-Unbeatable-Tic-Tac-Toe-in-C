MINIMAX ALGORITHM WITH ALPHA BETA PRUNING  (IMPLEMENTATION OF AN UNBEATABLE TIC-TAC-TOE GAME)

NAME : AMIT KUMAR
SRN : PES1201701295

SECTION : B 
SEMESTER : 4
PROJECT NUMBER : 30
YEAR : 2019



REQUIRED HEADER FILES:

1. stdio.h
2. stdlib.h
3. stdbool.h
4. limits.h


COMPONENTS:

1. Struct Result : It holds the score and move to be played for a particular state of the state space tree. 
2. Alpha : It's a lower bound on the value that the maximiser is willing to accept in the worst case. Initially, it's set to INT_MIN.
3. Beta :  It's a upper bound on the value that the minimiser is willing to accept in the worst case. Initially, it's set to INT_MAX.
4. Depth : It at any instance specifies the depth of the game state from the initial state in the state space tree.
5. X : Maximiser player [Human]
6. O : Minimiser player [Computer]
7. E : Signifies an empty cell.


UTILITY FUNCTIONS:

1. void printGame(int **game , int N) : Prints out the current state of the game in the form of a 3x3 box with Xs and Os.

2. bool hasGameEnded(int** game , int N) : Checks whether the game has ended yet or not. A game ends when all the cells have been played
                                           in and there are no empty cells left to play.

3. int score(int** game, int depth , int N) : Score function is a static evaluater for the leaf nodes.
                    It computes the score attained by the player based on the depth of the tree ie 
                        the number of chances it took him to win the game.
                    Score for a draw game or otherwise is 0.
                    Score for the minimiser player is negative , 10 - Depth.
                    Score for the maximiser player is postive , Depth - 10.10 is an arbitrary chosen value which
                        is greater than the possible depth of the tree.

4. bool hasPlayerWon(int** game, int player , int N) : Function checks if the "player" has played a winning move and won the game.
                    Winning is equivalent to getting same symbols along any row, any column or along 
                        one of the diagonals.

5. bool isTerminalState(int** game , int N) : Checks if the game has reached a Terminal state.
                    Terminal state happens when either one of the players has won the game or the game has ended
                       (no cells left to play further).

6. void computeAndPlayBestMove(int** game, int player , int N) : Minimax algorithm entry method. Uses minTurn() and maxTurn() to compute
                    the best move for the current player and plays that move.
                    Once the structure(score,move) is returned by the called functions , the current state of the game is updated.
                    -1 is fail safe value used in the minTurn() and maxTurn() function when no possible is available i.e we've reached the leaf
                        of that particular path of the tree.

7. Result* minTurn(int** game, int depth, int alpha, int beta, int N) : Method to compute best move for player O (minimising player)
                        Recursively calls maxTurn() to compute the opponent's future move based on the current temporary move made.
                        Pruning happens when alpha becomes greater than or equal to the static value from one branch. Since, alpha can take a value greater 
                        than equal to the current value but if the beta of the parent is less than this alpha , then it will never choose the other path,
                        therefore the other branch is pruned.
                        move (r  or  c) is set to -1 when no further move is possible => End condition. It's a fail safe value.

8. Result* maxTurn(int** game, int depth, int alpha, int beta, int N) : Method to compute best move for player O (maximising player)
                        Recursively calls maxTurn() to compute the opponent's future move based on the current temporary move made.
                        Pruning happens when beta becomes lesser than or equal to the static value from one branch. Since, beta can take a value 
                        lesser than equal to the current value but if the alpha of the parent is greater than this beta , then it will never choose
                        the other path,therefore the other branch is pruned.
                        move (r  or  c) is set to -1 when no further move is possible => End condition. It's a fail safe value.