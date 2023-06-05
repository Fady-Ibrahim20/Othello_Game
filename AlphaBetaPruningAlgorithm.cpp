//
// Created by fady on 04/05/23.
//

#include <iostream>
#include "AlphaBetaPruningAlgorithm.h"

pair<int, pair<int, int>>
AlphaBetaPruningAlgorithm::doAlgorithm(Game &game, char (&board)[ROWS][COLUMNS], int depth, char player, bool firstTime)
{
    int alpha=SMALLEST_VALUE;
    int beta=LARGEST_VALUE;
    return recursiveAlphaBetaAlgorithm(game,board,depth,alpha,beta,player,firstTime);
}

pair<int,pair<int,int>> AlphaBetaPruningAlgorithm::recursiveAlphaBetaAlgorithm(Game &game, char (&board)[ROWS][COLUMNS], int depth,int alpha,int beta, char player, bool firstTime)
{
    char oldBoard[ROWS][COLUMNS];
    if(depth==0)
    {
        //cout <<"result invoked from depth =0"<<endl;
        int result=game.clculateHeuristic(board);
        //cout <<"result " <<result;
        return pair<int,pair<int,int>> {result,{-1,-1}};
    }
    if(game.isTerminal(board))
    {
        //cout <<"result invoked from game is terminal in function of "<<player<<endl;
        int result=game.clculateHeuristic(board);
        //cout <<"result returend is "<<result;
        if(firstTime){
            cout << "the WINNER is "<< game.getWinner(board);
            return pair<int,pair<int,int>> {result,{-2,-2}};

        }
        return pair<int,pair<int,int>> {result,{-1,-1}};
    }
    bool isPruned=false;
    if(player==MAX_PLAYER)
    {
        vector<pair<int,int>> moves=game.listOfValidMoves(board,'X');
        if (moves.size() == 0) {
            return recursiveAlphaBetaAlgorithm(game, board, depth - 1,
                                               alpha, beta, game.reversePlayer(player), false);

        }else{
            int finalRow = moves.at(0).first;
            int finalColumn = moves.at(0).second;
            int finalValue = SMALLEST_VALUE;
            for (pair<int, int> &move: moves) {
                //if (firstTime) {
//                    for (pair<int, int> &move: moves) {
//                        cout << "move could be taken for x " << move.first << " " << move.second << endl;
//                    }
               // }
                game.saveBoard(oldBoard, board);
                game.makeMove(board, move.first, move.second, player);
//                if(firstTime){
//                    cout << "move taken for x first time "<< "row: "<<move.first <<" column: "<<move.second <<endl;
//
//                }else {
//                    cout << "move taken for x " << "row: " << move.first << " column: " << move.second << endl;
//                }
                int value = recursiveAlphaBetaAlgorithm(game, board, depth - 1, alpha, beta,
                                                        game.reversePlayer(player), false).first;
                game.undoMove(oldBoard, board);
                if (value > finalValue) {
                    finalValue = value;
                    finalRow = move.first;
                    finalColumn = move.second;
//                        std::cout << "for max final row : "  << finalRow <<std::endl;
//                        std::cout << "for max final column : "  << finalColumn <<endl;

                }
//TODO: to be considered if we didn't update the Alpha return it
                if (value > alpha) {
                    //cout << "value that larger than alpha "<<value;
                    alpha = value;
                }
                if (alpha >= beta) {
                    isPruned=true;
                    //cout << "at "<<player <<" alpha = " <<alpha <<"beta = "<<beta <<endl;
                    break;
                }
            }
            if(!isPruned){
                return pair<int, pair<int, int>>{finalValue, {finalRow, finalColumn}};

            }else{
                return pair<int, pair<int, int>>{LARGEST_VALUE, {finalRow, finalColumn}};

            }

        }
    }
    else if(player == MIN_PLAYER) {

        vector<pair<int, int>> moves = game.listOfValidMoves(board, 'N');
        if (moves.size() == 0) {
            return recursiveAlphaBetaAlgorithm(game, board, depth - 1,
                                                    alpha, beta, game.reversePlayer(player), false);

        } else {

            int finalRow = moves.at(0).first, finalColumn = moves.at(0).second;
            int finalValue = LARGEST_VALUE;
            for (pair<int, int> &move: moves) {
                //if (firstTime) {
//                    for (pair<int, int> &move: moves) {
//                        cout << "move could be taken for n " << move.first << " " << move.second << endl;
//                    }
                //}
                game.saveBoard(oldBoard, board);
                game.makeMove(board, move.first, move.second, player);
//                if (firstTime) {
//                    cout << "move taken for n first time " << "row: " << move.first << " column: " << move.second
//                         << endl;
//
//                } else {
//                    cout << "move taken for n " << "row: " << move.first << " column: " << move.second << endl;
//                }
                int value = recursiveAlphaBetaAlgorithm(game, board, depth - 1,
                                                        alpha, beta, game.reversePlayer(player), false).first;
                game.undoMove(oldBoard, board);
//                if (firstTime) {
//
//                    cout << "value in first time" << value;
//                }
                if (value < finalValue) {
                    finalValue = value;
                    finalRow = move.first;
                    finalColumn = move.second;
//                        cout << "row "<<finalRow <<endl;
//                        cout << "column "<<finalColumn <<endl;
                }
                if (value < beta) {
                    //cout << "value that smaller than beta " << value << endl;
                    beta = value;
                }
                if (alpha >= beta) {
                    isPruned=true;
                  //  cout << "at "<<player <<" alpha = " <<alpha <<"beta = "<<beta <<endl;
                    break;
                }
            }
            if(!isPruned){
                return pair<int, pair<int, int>>{finalValue, {finalRow, finalColumn}};
            }else{
                return pair<int, pair<int, int>>{SMALLEST_VALUE, {finalRow, finalColumn}};

            }


        }


    }
}





// debugging lines
