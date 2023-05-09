//
// Created by fady on 09/05/23.
//

#ifndef AI_ITERATIVEDEEPENINGOFALPHABETAPRUNINGALGORITHM_H
#define AI_ITERATIVEDEEPENINGOFALPHABETAPRUNINGALGORITHM_H


#include "AlphaBetaPruningAlgorithm.h"

class IterativeDeepeningOfAlphaBetaPruningAlgorithm : public AlphaBetaPruningAlgorithm{
public:
    pair<int, pair<int, int>>
    doAlgorithm(Game &game, char (&board)[8][8], int depth, char player, bool firstTime) override;
};


#endif //AI_ITERATIVEDEEPENINGOFALPHABETAPRUNINGALGORITHM_H
