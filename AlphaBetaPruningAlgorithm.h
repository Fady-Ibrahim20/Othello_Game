//
// Created by fady on 04/05/23.
//

#ifndef AI_ALPHABETAPRUNINGALGORITHM_H
#define AI_ALPHABETAPRUNINGALGORITHM_H


#include "MiniMaxAlgorithm.h"
#include "Game.h"

class AlphaBetaPruningAlgorithm : public MiniMaxAlgorithm{
protected:
    pair<int,pair<int,int>>
    recursiveAlphaBetaAlgorithm(Game &game, char (&board)[ROWS][COLUMNS], int depth,int alpha,int beta, char player, bool firstTime=true);

public:
    pair<int, pair<int, int>>
    doAlgorithm(Game &game, char (&board)[ROWS][COLUMNS], int depth, char player, bool firstTime=true) override;
};


#endif //AI_ALPHABETAPRUNINGALGORITHM_H
