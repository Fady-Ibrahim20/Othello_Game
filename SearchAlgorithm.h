//
// Created by fady on 04/05/23.
//

#ifndef AI_SEARCHALGORITHM_H
#define AI_SEARCHALGORITHM_H


#include "Game.h"

class SearchAlgorithm {
public:
    virtual pair<int,pair<int,int>>  doAlgorithm(Game& game,char (&board)[ROWS][COLUMNS],int depth, char player ,bool firstTime=true) = 0;
};


#endif //AI_SEARCHALGORITHM_H
