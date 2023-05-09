//
// Created by fady on 09/05/23.
//

#include "IterativeDeepeningOfAlphaBetaPruningAlgorithm.h"

pair<int, pair<int, int>>
IterativeDeepeningOfAlphaBetaPruningAlgorithm::doAlgorithm(Game &game, char (&board)[8][8], int depth, char player,bool firstTime)
{
    pair<int,pair<int,int>> alphaBetaPruningReturn;
    pair<int,pair<int,int>> finalResult;
    int highestValue;
    if(player=='X'){highestValue=SMALLEST_VALUE;}else{highestValue=LARGEST_VALUE;}
    int alpha=SMALLEST_VALUE;
    int beta=LARGEST_VALUE;
    for(int i=0;i<=depth;i++)
{
    alphaBetaPruningReturn=recursiveAlphaBetaAlgorithm(game,board,i,alpha,beta,player,firstTime);
    if(player=='X')
    {
        if(alphaBetaPruningReturn.first >= highestValue){
            finalResult=alphaBetaPruningReturn;
        }

    }
    else
    {
        if(alphaBetaPruningReturn.first <= highestValue){
            finalResult=alphaBetaPruningReturn;
        }
    }
}
return finalResult;
}
