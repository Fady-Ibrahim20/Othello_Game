//
// Created by fady on 04/05/23.
//

#ifndef AI_OTHELLOGAME_H
#define AI_OTHELLOGAME_H


#include "Game.h"
#include <iostream>
#include <thread>
#include <functional>


class OthelloGame : public Game {
public:

    bool isTerminal(char board[ROWS][COLUMNS]) override;

    vector<pair<int, int>> listOfValidMoves(char board[ROWS][COLUMNS], char player) override;



    void makeMove(char board[ROWS][COLUMNS], int row, int column, char player) override;

    void undoMove(char (&oldBoard)[ROWS][COLUMNS], char (&board)[ROWS][COLUMNS]) override;

    void saveBoard(char (&oldBoard)[ROWS][COLUMNS], char (&board)[ROWS][COLUMNS]) override;

    pair<int,int> getCurrentScore(char (*board)[8]) override;

    char reversePlayer(char player) override;

    int clculateHeuristic(char board[ROWS][COLUMNS]) override;

    char getWinner(char (*board)[ROWS]) override;


private:
    inline bool isValidMove(char board[ROWS][COLUMNS], int row, int column, char player) ;
    bool checkDiagonals(char board[ROWS][COLUMNS],int row,int column,char player);
    bool checkRows(char board[ROWS][COLUMNS],int row,int column,char player);
    bool checkColumns(char board[ROWS][COLUMNS],int row,int column,char player);

    void flankInColumns(char board[ROWS][COLUMNS],int row,int column,char player);
    void flankInDiagonals(char board[ROWS][COLUMNS],int row,int column,char player);
    void flankInRows(char board[ROWS][COLUMNS],int row,int column,char player);
    void flankInAllDirections(char board[ROWS][COLUMNS],int row,int column,char player);

    inline int coinParity(char board[ROWS][COLUMNS]);
    inline int mobility(char board[ROWS][COLUMNS]);
    inline int cornersCaptured(char board[ROWS][COLUMNS]);
    inline pair<int,int> checkCorners(char board[ROWS][COLUMNS]);
    inline bool isCorner(int row,int column);

    inline int stability(char board[ROWS][COLUMNS]);


    inline int toBeFlankedCoins(char board[ROWS][COLUMNS],pair<int,int> move,char player);
    pair<int,int> countStableAndUnStableCoins(char board[ROWS][COLUMNS]);
    int countToBeFlankedCoinsInRows(char board[ROWS][COLUMNS],int row,int column,char player);
    int countToBeFlankedCoinsInColumns(char board[ROWS][COLUMNS],int row,int column,char player);
    int countToBeFlankedCoinsInDiagonals(char board[ROWS][COLUMNS],int row,int column,char player);

    int occupiedEdgeCoins(char board[ROWS][COLUMNS]);
    pair<int,int> countEdgeCoins(char board[ROWS][COLUMNS]);

};


#endif //AI_OTHELLOGAME_H
