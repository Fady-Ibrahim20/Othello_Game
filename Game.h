//
// Created by fady on 04/05/23.
//

#ifndef AI_GAME_H
#define AI_GAME_H

#include <utility>
#include <vector>
#include "Constants.h"
using namespace std;

class Game {
public:
    virtual bool isTerminal(char board[ROWS][COLUMNS])=0;

    virtual vector<pair<int,int>> listOfValidMoves(char board[ROWS][COLUMNS],char player)=0;
    virtual bool isValidMove(char board[ROWS][COLUMNS],int row,int column,char player)=0;


    virtual void makeMove(char board[ROWS][COLUMNS],int row,int column,char player)=0;


    virtual void undoMove(char (&oldBoard)[ROWS][COLUMNS],char (&board)[8][8])=0;
    virtual void saveBoard(char (&oldBoard)[ROWS][COLUMNS],char (&board)[8][8])=0;

    virtual char reversePlayer(char player)=0;


    virtual int clculateHeuristic(char board[ROWS][COLUMNS])=0;

    virtual char getWinner(char (*board)[ROWS])=0;



};


#endif //AI_GAME_H
