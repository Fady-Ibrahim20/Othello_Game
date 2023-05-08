//
// Created by fady on 04/05/23.
//

#include <iostream>
#include "MiniMaxAlgorithm.h"

pair<int, pair<int, int>> MiniMaxAlgorithm::doAlgorithm(Game &game,char (&board)[ROWS][COLUMNS],int depth, char player,bool firstTime) {

    char oldBoard[ROWS][COLUMNS];
    if(depth==0)
    {
        int result=game.clculateHeuristic(board);
        return pair<int,pair<int,int>> {result,{-1,-1}};
    }
    if(game.isTerminal(board))
    {
        int result=game.clculateHeuristic(board);
        cout <<"game terminated";
        if(firstTime){
            cout << "the WINNER is "<< game.getWinner(board);
        }
        return pair<int,pair<int,int>> {result,{-2,-2}};
    }

    if(player=='X')
    {
        vector<pair<int,int>> moves =game.listOfValidMoves(board,player);
        if(moves.size()==0) {
        return doAlgorithm(game,board,depth-1,game.reversePlayer(player),false);
        }else{
        int finalRow=moves.at(0).first;
        int finalColumn=moves.at(0).second;
        int finalValue=SMALLEST_VALUE;
        for(pair<int,int>& move:moves){


                    game.saveBoard(oldBoard, board);
                    game.makeMove(board,move.first,move.second,player);
                    int value = doAlgorithm(game,board,depth-1,game.reversePlayer(player),false).first;
                    game.undoMove(oldBoard, board);
                    if(value>finalValue)
                    {
                        finalValue=value;
                        finalRow=move.first;
                        finalColumn=move.second;
//                        std::cout << "for max final row : "  << finalRow <<std::endl;
//                        std::cout << "for max final column : "  << finalColumn <<endl;

                    }
        }
        //if(firstTime){
            return pair<int,pair<int,int>> {finalValue,{finalRow,finalColumn}};
        //}
        }
    }
    else if(player == 'N')
    {
        vector<pair<int,int>> moves =game.listOfValidMoves(board,player);

        if(moves.size()==0) {
        return doAlgorithm(game,board,depth-1, game.reversePlayer(player),false);

        }else {

            int finalRow=moves.at(0).first;
            int finalColumn=moves.at(0).second;
        int finalValue=LARGEST_VALUE;
        for(pair<int,int>& move:moves){
                    game.saveBoard(oldBoard, board);
                    game.makeMove(board,move.first,move.second,player);
                    int value = doAlgorithm(game,board,depth-1, game.reversePlayer(player),false).first;
                    game.undoMove(oldBoard, board);
                    if(value<finalValue)
                    {
                        finalValue=value;
                        finalRow=move.first;
                        finalColumn=move.second;
//                        cout << "row "<<finalRow <<endl;
//                        cout << "column "<<finalColumn <<endl;

                    }
                }
            return pair<int,pair<int,int>> {finalValue,{finalRow,finalColumn}};
        //if(firstTime){
        //}

        }
    }
}
