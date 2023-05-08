//
// Created by fady on 04/05/23.
//

#ifndef AI_MINIMAXALGORITHM_H
#define AI_MINIMAXALGORITHM_H


#include "SearchAlgorithm.h"

class MiniMaxAlgorithm : public SearchAlgorithm{
private:
    char getWinner(char board[ROWS][COLUMNS]);
public:
    pair<int,pair<int,int>>  doAlgorithm(Game& game,char (&board)[ROWS][COLUMNS],int depth, char player ,bool firstTime=true) override;
};


#endif //AI_MINIMAXALGORITHM_H
