#include <iostream>
#include <vector>
#include <unordered_map>
#include "OthelloGame.h"
#include "MiniMaxAlgorithm.h"
#include "AlphaBetaPruningAlgorithm.h"

using namespace std;

//pair<int,pair<int,int>> MinimaxAlgorithm(char (&board)[8][8],int depth,char player,bool firstTime= true);
//
//bool isTerminal(char board[8][8]);
//
//vector<pair<int,int>> listOfValidMoves(char board[8][8],char player);
//bool isValidMove(char board[8][8],int row,int column,char player);
//bool checkDiagonals(char board[8][8],int row,int column,char player);
//bool checkRows(char board[8][8],int row,int column,char player);
//bool checkColumns(char board[8][8],int row,int column,char player);
//
//void makeMove(char board[8][8],int row,int column,char player);
//void flankInColumns(char board[8][8],int row,int column,char player);
//void flankInDiagonals(char board[8][8],int row,int column,char player);
//void flankInRows(char board[8][8],int row,int column,char player);
//void flankInAllDirections(char board[8][8],int row,int column,char player);
//
//void undoMove(char (&oldBoard)[8][8],char (&board)[8][8]);
//void saveBoard(char (&oldBoard)[8][8],char (&board)[8][8]);

//void undoMove(char board[8][8],int row,int column,char player);
//void undoFlankInColumns(char board[8][8],int row,int column,char player);
//void undoFlankInDiagonals(char board[8][8],int row,int column,char player);
//void undoFlankInRows(char board[8][8],int row,int column,char player);
//void undoFlankInAllDirections(char board[8][8],int row,int column,char player);

char reversePlayer(char player);

bool isCorner(int row,int column);

int clculateHeuristic(char board[8][8]);
int coinParity(char board[8][8]);
int mobility(char board[8][8]);
int cornersCaptured(char board[8][8]);
pair<int,int> checkCorners(char board[8][8]);

int stability(char board[8][8]);


int toBeFlankedCoins(char board[8][8],pair<int,int> move,char player);
pair<int,int> countStableAndUnStableCoins(char board[8][8]);
int countToBeFlankedCoinsInRows(char board[8][8],int row,int column,char player);
int countToBeFlankedCoinsInColumns(char board[8][8],int row,int column,char player);
int countToBeFlankedCoinsInDiagonals(char board[8][8],int row,int column,char player);







void drawBoardForDebug(char board[8][8]) {
    // Draw the board with row and column indices
    cout << "  ";
    for (int i = 0; i < 8; i++) {
        cout << i  << " ";
    }
    cout << endl;
    for (int i = 0; i < 8; i++) {
        cout << i  << " ";
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
char board[8][8];

    // Initialize the board with all cells set to '-'
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = '-';
        }
    }

    // Place initial pieces in the center of the board
    board[3][3] = 'N';
    board[4][4] = 'N';
    board[3][4] = 'X';
    board[4][3] = 'X';

    drawBoardForDebug(board);
    OthelloGame othelloGame;

 AlphaBetaPruningAlgorithm alpgaBetaAlgorithm;

////max depth 5 to 6
     MiniMaxAlgorithm miniMaxalgo;
    while (true) {
        bool flag = true;
        int row, col;
        char player;
        while (flag) {
            pair<int,pair<int,int>> res=alpgaBetaAlgorithm.doAlgorithm(othelloGame,board,4,MAX_PLAYER);
            int val= res.first ;
            cout << "val for max " << val <<endl;
            cout << " row for max : " << res.second.first <<endl;
            cout << " column for max: " << res.second.second <<endl;
            row=res.second.first;
            col=res.second.second;
            if(row==-2 && col ==-2){
                cout << "the winner "<<othelloGame.getWinner(board)<<endl;
                return 0;
            }
//            cout << "Player X, enter row and column to place your piece: ";
//            cin >> row >> col;
            player = MAX_PLAYER;

            if (othelloGame.listOfValidMoves(board, player).size() > 0) {

                if (othelloGame.isValidMove(board, row, col, player)) {
                    othelloGame.makeMove(board, row, col, player);
                    drawBoardForDebug(board);

                    flag = false;

                } else {
                    cout << "Invalid move. Try again." << endl;
                }

            }else{
                cout <<"no available moves";
                flag=false;
            }
        }

        flag=true;
        while(flag)
        {
           // pair<int,pair<int,int>> res=MiniMaxAlgorithm(board,2,'N'); 42 13 60 24
            pair<int,pair<int,int>> res=miniMaxalgo.doAlgorithm(othelloGame,board,4,MIN_PLAYER);
            int val= res.first ;
            cout << "val for min " << val <<endl;
            cout << " row for min : " << res.second.first <<endl;
            cout << " column for min: " << res.second.second <<endl;
            row=res.second.first;
            col=res.second.second;
//
        //    cout << "Player N, enter row and column to place your piece: " ;
      //  cin >> row >> col;
        player = MIN_PLAYER;
            if(row==-2 && col ==-2){
cout << "the winner "<<othelloGame.getWinner(board)<<endl;
                return 0;

            }

            if(othelloGame.listOfValidMoves(board, player).size()>0){

        if (othelloGame.isValidMove(board, row , col , player)) {
            othelloGame.makeMove(board,row,col,player);

            // Draw the updated board
            drawBoardForDebug(board);

            flag=false;
        } else {

            cout << "Invalid move. Try again." << endl;
        }
                }else{
                cout <<"no available moves";
                flag=false;
            }
        }
    }


    return 0;
}

//pair<int,pair<int,int>> MinimaxAlgorithm(char (&board)[8][8],int depth,char player,bool firstTime)
//{
//    char oldBoard[8][8];
//    int result=clculateHeuristic(board);
//    if(depth==0)
//    {
//         return pair<int,pair<int,int>> {result,{-1,-1}};
//    }
//    if(isTerminal(board))
//    {
//        return pair<int,pair<int,int>> {result,{-1,-1}};
//    }
//
//    if(player=='X')
//    {
//        int finalRow;
//        int finalColumn;
//        int finalValue=SMALLEST_VALUE;
//        for (int row = 0; row < 8; ++row)
//        {
//            for (int column = 0; column < 8; ++column)
//            {
//
//                if(isValidMove(board,row,column,player))
//                {
//                    saveBoard(oldBoard, board);
//                    makeMove(board,row,column,player);
//                    int value = MinimaxAlgorithm(board,depth-1, reversePlayer(player),false).first;
//                    undoMove(oldBoard, board);
//                    if(value>finalValue)
//                    {
//                        finalValue=value;
//                        finalRow=row;
//                        finalColumn=column;
////                        cout << "for max final row : "  << finalRow <<endl;
////                        cout << "for max final column : "  << finalColumn <<endl;
//
//                    }
//                }
//
//
//            }
//        }
//        if(firstTime){
//            return pair<int,pair<int,int>> {finalValue,{finalRow,finalColumn}};
//        }
//    }
//    else if(player == 'N')
//    {
//        int finalRow=0,finalColumn=0;
//        int finalValue=LARGEST_VALUE;
//        for (int row = 0; row < 8; ++row)
//        {
//            for (int column = 0; column < 8; ++column)
//            {
//
//                if(isValidMove(board,row,column,player))
//                {
//                    saveBoard(oldBoard, board);
//                    makeMove(board,row,column,player);
//                    int value = MinimaxAlgorithm(board,depth-1, reversePlayer(player),false).first;
//                    undoMove(oldBoard, board);
//                    if(value<finalValue)
//                    {
//                        finalValue=value;
//                        finalRow=row;
//                        finalColumn=column;
////                        cout << "for min final row : "  << finalRow <<endl;
////                        cout << "for min final column : "  << finalColumn <<endl;
//                    }
//                }
//            }
//
//        }
//
//        if(firstTime){
////            cout <<"here in first time of min " <<endl;
//            return pair<int,pair<int,int>> {finalValue,{finalRow,finalColumn}};
//        }
//
//    }
//
//}
//
//
//int clculateHeuristic(char board[8][8])
//{
//    return coinParity(board) + mobility(board) + stability(board) + cornersCaptured(board);
//}
//int coinParity(char board[8][8])
//{
//    int maxPlayerCoins=0;
//    int minPlayerCoins=0;
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board[i][j] == 'X')
//            {
//               ++maxPlayerCoins;
//            }
//            else if(board[i][j] == 'N')
//            {
//                ++minPlayerCoins;
//            }
//        }
//    }
//   return (100 * (maxPlayerCoins - minPlayerCoins ) / (maxPlayerCoins + minPlayerCoins ));
//}
//int mobility(char board[8][8])
//{
//    int maxPlayerActualMobility=0;
//    int minPlayerActualMobility=0;
//    int actualMobilityValue=0;
//
//    maxPlayerActualMobility = listOfValidMoves(board,'X').size();
//    minPlayerActualMobility = listOfValidMoves(board,'N').size();
//
//    if((minPlayerActualMobility + minPlayerActualMobility) !=0)
//    {
//    actualMobilityValue =
//            (100* (maxPlayerActualMobility - minPlayerActualMobility )/
//            (maxPlayerActualMobility + minPlayerActualMobility ));
//    }
//    else
//    {
//        actualMobilityValue = 0;
//    }
//    return actualMobilityValue;
//}
//int cornersCaptured(char board[8][8])
//{
//    int cornerHeuriticValue;
//    pair<int,int> playerCornerValues= checkCorners(board);
//
//    if( (playerCornerValues.first + playerCornerValues.second) !=0){
//
//        cornerHeuriticValue =
//    100* (playerCornerValues.first - playerCornerValues.second)/
//    (playerCornerValues.first + playerCornerValues.second );
//    }else
//    {
//        cornerHeuriticValue = 0;
//    }
//    return cornerHeuriticValue;
//}
//pair<int,int> checkCorners(char board[8][8])
//{
//    int firstCornerForMax=0,secondCornerForMax=0,thirdCornerForMax=0,fourthCornerForMax=0,
//            firstCornerForMin=0,secondCornerForMin=0,thirdCornerForMin=0,fourthCornerForMin=0;
//    if(board[0][0] !='-'){
//        if(board[0][0] == 'X'){
//            firstCornerForMax=1;
//        }else{
//            firstCornerForMin=1;
//        }
//    }
//    if(board[0][7] !='-'){
//        if(board[0][7] == 'X'){
//            secondCornerForMax=1;
//        }else{
//            secondCornerForMin=1;
//        }
//    }
//    if(board[7][7] !='-'){
//        if(board[0][0] == 'X'){
//            thirdCornerForMax=1;
//        }else{
//            thirdCornerForMin=1;
//        }
//    }
//    if(board[7][0] !='-'){
//        if(board[7][0] == 'X'){
//            fourthCornerForMax=1;
//        }else{
//            fourthCornerForMin=1;
//        }
//    }
//    return {firstCornerForMax + secondCornerForMax + thirdCornerForMax + fourthCornerForMax,
//            firstCornerForMin + secondCornerForMin + thirdCornerForMin + fourthCornerForMin};
//}
//int stability(char board[8][8])
//{
//    int stabilityValue;
//    // max stability value then min stability value
//    pair<int,int> playerStabilityValues= countStableAndUnStableCoins(board);
//    if((playerStabilityValues.first + playerStabilityValues.second ) !=0){
//    stabilityValue =
//            (100* (playerStabilityValues.first - playerStabilityValues.second )/
//    (playerStabilityValues.first + playerStabilityValues.second));
//
//    }
//    else
//    {
//        stabilityValue = 0;
//    }
//    return stabilityValue;
//}
////TODO: count Stable and Unstable Coins still not completed
//pair<int,int> countStableAndUnStableCoins(char board[8][8])
//{
//    int maxStableCoins=0;
//    int maxUnStableCoins=0;
//    int maxStabilityValue=0;
//
//    int minStableCoins=0;
//    int minUnStableCoins=0;
//    int minStabilityValue=0;
//
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//
//            if (board[i][j] != '-')
//            {
//                if(board[i][j] == 'X')
//                {
//                    if(isCorner(i,j))
//                    {
//                        maxStableCoins++;
//                        continue;
//                    }else
//                    {
//                        for (pair<int,int> move : listOfValidMoves(board,'X'))
//                        {
//                            maxUnStableCoins+= toBeFlankedCoins(board,move,'X');
//                        }
//
//                    }
//
//                }
//                else
//                {
//                    if(isCorner(i,j))
//                    {
//                        minStableCoins++;
//                        continue;
//                    }else
//                    {
//                        for (pair<int,int> move : listOfValidMoves(board,'N'))
//                        {
//                            minUnStableCoins+= toBeFlankedCoins(board,move,'N');
//                        }
//
//                    }
//                }
//
//            }
//
//        }
//    }
//    maxStabilityValue=maxStableCoins-maxUnStableCoins;
//    minStabilityValue=minStableCoins-minUnStableCoins;
//    return {maxStabilityValue,minStabilityValue};
//}
//
//int toBeFlankedCoins(char board[8][8],pair<int,int> move,char player)
//{
//    return countToBeFlankedCoinsInColumns(board,move.first,move.second,player) +
//            countToBeFlankedCoinsInRows(board,move.first,move.second,player) +
//            countToBeFlankedCoinsInDiagonals(board,move.first,move.second,player);
//}
//
//int countToBeFlankedCoinsInRows(char board[8][8],int row,int column,char player)
//{
//    int numberOfFlankedCoins=0;
//    if(row>1)
//    {
//        int flankEndRow=row;
//        int i=1;
//        while(board[row-i][column] == reversePlayer(player))
//        {
//            --i;
//            --flankEndRow;
//            if(board[row-i][column] == player)
//            {
//                while(flankEndRow<row)
//                {
//                    ++numberOfFlankedCoins;
//                    ++flankEndRow;
//                }
//            }
//        }
//    }
//    if((row+2)<8)
//    {
//        int flankEndRow=row;
//        int i=1;
//        while(board[row+i][column] == reversePlayer(player))
//        {
//            ++i;
//            ++flankEndRow;
//            if(board[row+i][column] == player)
//            {
//                while(flankEndRow>row)
//                {
//                    ++numberOfFlankedCoins;
//                    --flankEndRow;
//                }
//
//            }
//        }
//    }
//    return numberOfFlankedCoins;
//}
//int countToBeFlankedCoinsInColumns(char board[8][8],int row,int column,char player)
//{
//    int toBeFlankedCoins=0;
//    if(column>1)
//    {
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row][column-i] == reversePlayer(player))
//        {
//            ++i;
//            --flankEndColumn;
//            if(board[row][column-i] == player)
//            {
//                while(flankEndColumn<column)
//                {
//                    ++toBeFlankedCoins;
//                    ++flankEndColumn;
//                }
//            }
//        }
//    }
//    if((column+2)<8)
//    {
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row][column+i] == reversePlayer(player))
//        {
//            ++i;
//            ++flankEndColumn;
//            if(board[row][column+i] == player)
//            {
//                while(flankEndColumn>column)
//                {
//                    ++toBeFlankedCoins;
//                    --flankEndColumn;
//                }
//            }
//        }
//    }
//    return toBeFlankedCoins;
//}
//int countToBeFlankedCoinsInDiagonals(char board[8][8],int row,int column,char player)
//{
//    int toBeFlankedCoins=0;
//    if(column>1 && row >1)
//    {
//        int flankEndRow=row;
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row-i][column-i] == reversePlayer(player))
//        {
//            ++i;
//            --flankEndRow;
//            --flankEndColumn;
//            if(board[row-i][column-i] == player)
//            {
//                while(flankEndRow < row && flankEndColumn < column)
//                {
//                    ++toBeFlankedCoins;
//                    ++flankEndRow;
//                    ++flankEndColumn;
//                }
//            }
//        }
//    }
//    if( ((column+2)<8) && ((row+2)<8) )
//    {
//        int flankEndRow=row;
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row+i][column+i] == reversePlayer(player))
//        {
//            --flankEndRow;
//            --flankEndColumn;
//            ++i;
//            if(board[row+i][column+i] == player)
//            {
//                while(flankEndRow > row && flankEndColumn > column)
//                {
//                    ++toBeFlankedCoins;
//                    --flankEndRow;
//                    --flankEndColumn;
//                }
//            }
//        }
//    }
//    if(column>1 && ((row+2)<8) )
//    {
//        int i=1;
//        int flankEndRow=row;
//        int flankEndColumn=column;
//        while(board[row+i][column-i] == reversePlayer(player))
//        {
//            ++i;
//            ++flankEndRow;
//            --flankEndColumn;
//            if(board[row+i][column-i] == player)
//            {
//                while(flankEndRow > row && flankEndColumn < column)
//                {
//                    ++toBeFlankedCoins;
//                    --flankEndRow;
//                    ++flankEndColumn;
//                }
//            }
//        }
//    }
//    if((column+2) < 1 && row > 1)
//    {
//        int flankEndRow=row;
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row-i][column+i] == reversePlayer(player))
//        {
//            --flankEndRow;
//            ++flankEndColumn;
//            if(board[row-i][column+i] == player)
//            {
//                while(flankEndRow > row && flankEndColumn < column)
//                {
//                    ++toBeFlankedCoins;
//                    ++flankEndRow;
//                    --flankEndColumn;
//                }
//            }
//        }
//    }
//    return toBeFlankedCoins;
//}
//
//
//bool isCorner(int row,int column)
//{
//    if((row==7 && column==7) || (row==0 && column==0) || (row==7 && column==0) || (row==0 && column==7) )
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
//bool isTerminal(char board[8][8])
//{
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board[i][j] == '-') {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//bool isValidMove(char board[8][8],int row,int column,char player)
//{
//    if((checkColumns(board,row,column,player) || checkRows(board,row,column,player) || checkDiagonals(board,row,column,player)) && board[row][column] == '-')
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
//vector<pair<int,int>> listOfValidMoves(char board[8][8],char player)
//{
//    vector<pair<int,int>> listOfValidMoves;
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board[i][j] == '-')
//            {
//                if(isValidMove(board,i,j,player))
//                {
//                    listOfValidMoves.push_back(make_pair(i,j));
//                }
//            }
//        }
//    }
//    return listOfValidMoves;
//}
//
//void makeMove(char board[8][8],int row,int column,char player)
//{
//    board[row][column]=player;
//    flankInAllDirections(board,row,column,player);
//}
//
//
//void undoMove(char (&oldBoard)[8][8],char (&board)[8][8])
//{
//    copy(&oldBoard[0][0], &oldBoard[0][0] + 64, &board[0][0]);
//}
//void saveBoard(char (&oldBoard)[8][8],char (&board)[8][8])
//{
//    copy(&board[0][0], &board[0][0] + 64, &oldBoard[0][0]);
//}
//char reversePlayer(char player)
//{
//    if(player=='X')
//    {
//        return 'N';
//    }
//    else
//    {
//        return 'X';
//    }
//}
//
//bool checkRows(char board[8][8],int row,int column,char player)
//{
//    if(column>1)
//    {
//        int i=1;
//        while(board[row][column-i] == reversePlayer(player) && (column-i)>0 )
//        {
//            ++i;
//            if(board[row][column-i] == player){
//                return true;
//            }
//        }
//    }
//    if((column+2)<8)
//    {
//        int i=1;
//        while(board[row][column+i] == reversePlayer(player) && (column+i)<8)
//        {
//            ++i;
//            if(board[row][column+i] == player){
//                return true;
//            }
//        }
//    }
//    return false;
//}
//bool checkColumns(char board[8][8],int row,int column,char player)
//{
//    if(row>1)
//    {
//        int i=1;
//        while(board[row-i][column] == reversePlayer(player) && (row-i) >0 )
//        {
//            ++i;
//            if(board[row-i][column] == player){
//                return true;
//            }
//        }
//    }
//    if((row+2)<8)
//    {
//        int i=1;
//        while(board[row+i][column] == reversePlayer(player) && (row+i)<8)
//        {
//            ++i;
//            if(board[row+i][column] == player){
//                return true;
//            }
//        }
//    }
//    return false;
//}
//bool checkDiagonals(char board[8][8],int row,int column,char player)
//{
//    if(column>1 && row >1)//6,2
//    {
//        int i=1;
//        while(board[row-i][column-i] == reversePlayer(player) && (row-i) > 0 && (column-i) > 0)
//        {
//            ++i;
//            if(board[row-i][column-i] == player){
//                return true;
//            }
//        }
//    }
//    if( ((column+2)<8) && ((row+2)<8) )
//    {
//        int i=1;
//        while(board[row+i][column+i] == reversePlayer(player) && (row+i)<8 && (column+i)<8)
//        {
//            ++i;
//            if(board[row+i][column+i] == player){
//                return true;
//            }
//        }
//    }
//    if(column > 1 && (row+2)<8)
//    {
//        int i=1;
//        while(board[row+i][column-i] == reversePlayer(player) && (row+i)< 8 && (column-i) >0)
//        {
//            ++i;
//            if(board[row+i][column-i] == player){
//                return true;
//            }
//        }
//    }
//    if((column+2) < 8 && row > 1)
//    {//5 3
//        int i=1;
//        while(board[row-i][column+i] == reversePlayer(player) && (row-i) >0 && (column+i)<8)
//        {
//            ++i;
//            if(board[row-i][column+i] == player){
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//
//void flankInRows(char board[8][8],int row,int column,char player)
//{
//    if(row>1)
//    {
//        int flankEndRow=row;
//        int i=1;
//        while(board[row-i][column] == reversePlayer(player) && (row-i) >0 )
//        {
//            ++i;
//            --flankEndRow;
//            if(board[row-i][column] == player)
//            {
//               while(flankEndRow<row)
//               {
//                   board[flankEndRow][column]=player;
//                   ++flankEndRow;
//               }
//            }
//        }
//    }
//    if((row+2)<8)
//    {
//        int flankEndRow=row;
//        int i=1;
//        while(board[row+i][column] == reversePlayer(player) && (row+i)<8)
//        {
//            ++i;
//            ++flankEndRow;
//            if(board[row+i][column] == player)
//            {
//                while(flankEndRow>row)
//                {
//                    board[flankEndRow][column]=player;
//                    --flankEndRow;
//                }
//
//            }
//        }
//    }
//}
//void flankInColumns(char board[8][8],int row,int column,char player)
//{
//    if(column>1)
//    {
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row][column-i] == reversePlayer(player) && (column-i) >0 )
//        {
//            ++i;
//            --flankEndColumn;
//            if(board[row][column-i] == player)
//            {
//                while(flankEndColumn<column)
//                {
//                    board[row][flankEndColumn]=player;
//                    ++flankEndColumn;
//                }
//            }
//        }
//    }
//    if((column+2)<8)
//    {
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row][column+i] == reversePlayer(player) && (column+i)<8 )
//        {
//            ++i;
//            ++flankEndColumn;
//            if(board[row][column+i] == player)
//            {
//                while(flankEndColumn>column)
//                {
//                    board[row][flankEndColumn]=player;
//                    --flankEndColumn;
//                }
//            }
//        }
//    }
//}
//void flankInDiagonals(char board[8][8],int row,int column,char player)
//{
//    if(column>1 && row >1)
//    {
//        int flankEndRow=row;
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row-i][column-i] == reversePlayer(player) && (row-i) >0 && (column-i) >0 )
//        {
//            ++i;
//            --flankEndRow;
//            --flankEndColumn;
//            if(board[row-i][column-i] == player)
//            {
//                while(flankEndRow < row && flankEndColumn < column)
//                {
//                    board[flankEndRow][flankEndColumn]=player;
//                    ++flankEndRow;
//                    ++flankEndColumn;
//                }
//            }
//        }
//    }
//    if( ((column+2)<8) && ((row+2)<8) )
//    {
//        int flankEndRow=row;
//        int flankEndColumn=column;
//        int i=1;
//        while(board[row+i][column+i] == reversePlayer(player) && (column+i)<8 && (row+i)<8)
//        {
//            ++flankEndRow;
//            ++flankEndColumn;
//            ++i;
//            if(board[row+i][column+i] == player)
//            {
//                while(flankEndRow > row && flankEndColumn > column)
//                {
//                    board[flankEndRow][flankEndColumn]=player;
//                    --flankEndRow;
//                    --flankEndColumn;
//                }
//            }
//        }
//    }
//    if(column>1 && ((row+2)<8) )
//    {
//        int i=1;
//        int flankEndRow=row;
//        int flankEndColumn=column;
//        while(board[row+i][column-i] == reversePlayer(player) && (row+i)<8 && (column-i) >0 )
//        {
//            ++i;
//            ++flankEndRow;
//            --flankEndColumn;
//            if(board[row+i][column-i] == player)
//            {
//                while(flankEndRow > row && flankEndColumn < column)
//                {
//                    board[flankEndRow][flankEndColumn]=player;
//                    --flankEndRow;
//                    ++flankEndColumn;
//                }
//            }
//        }
//    }
//    if( row > 1 && ((column+2) < 8 ))
//    {// 6 2
//        int flankEndRow=row;// 6
//        int flankEndColumn=column;//2
//        int i=1;
//        while(board[row-i][column+i] == reversePlayer(player) && (row-i) >0 && (column+i)<8)
//        {
//            --flankEndRow;// 5
//            ++flankEndColumn;// 3
//            ++i;
//            if(board[row-i][column+i] == player)
//            {
//                while(flankEndRow < row && flankEndColumn > column)
//                {
//                    board[flankEndRow][flankEndColumn]=player;
//                    ++flankEndRow;
//                    --flankEndColumn;
//                }
//            }
//        }
//    }
//}
//void flankInAllDirections(char board[8][8],int row,int column,char player)
//{
//    flankInColumns(board,row,column,player);
//    flankInRows(board,row,column,player);
//    flankInDiagonals(board,row,column,player);
//}

/*
void undoMove(char board[8][8],int row,int column,char player)
{
    board[row][column]= '-';
    undoFlankInAllDirections(board,row,column, player);
}

void undoFlankInColumns(char board[8][8],int row,int column,char player){
    if(column>1)
    {
        int flankEndColumn=column;
        int i=1;
        while(board[row][column-i] == player)
        {
            ++i;
            --flankEndColumn;
            if(board[row][column-i] == player && board[row][column-i] != '-')
            {
                    board[row][flankEndColumn]= reversePlayer(player);
            }
        }
    }
    if((column+2)<8)
    {
        int flankEndColumn=column;
        int i=1;
        while(board[row][column+i] == player )
        {
            ++i;
            ++flankEndColumn;
            if(board[row][column+i] == player && board[row][column+i] != '-')
            {
                    board[row][flankEndColumn]= reversePlayer(player);
            }
        }
    }
}
void undoFlankInDiagonals(char board[8][8],int row,int column,char player)
{
    if(column>1 && row >1)
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row-i][column-i] == player)
        {
            ++i;
            --flankEndRow;
            --flankEndColumn;
            if(board[row-i][column-i] == player && board[row-i][column-i] != '-')
            {
                    board[flankEndRow][flankEndColumn]= reversePlayer(player);
            }
        }
    }
    if( ((column+2)<8) && ((row+2)<8) )
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row+i][column+i] == player)
        {
            ++flankEndRow;
            ++flankEndColumn;
            ++i;
            if(board[row+i][column+i] == player && board[row+i][column+i] != '-')
            {
                    board[flankEndRow][flankEndColumn]= reversePlayer(player);
            }
        }
    }
    if(column>1 && ((row+2)<8) )
    {
        int i=1;
        int flankEndRow=row;//1
        int flankEndColumn=column;//6
        while(board[row+i][column-i] == player)
        {//2 5   3 4
            ++i;
            ++flankEndRow;
            --flankEndColumn;
            if(board[row+i][column-i] == player && board[row+i][column-i] != '-')
            {
                    board[flankEndRow][flankEndColumn]= reversePlayer(player);
            }
        }
    }
    if((column+2) < 8 && row > 1)
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row-i][column+i] == player)
        {
            --flankEndRow;
            ++flankEndColumn;
            if(board[row-i][column+i] == player && board[row-i][column+i] != '-')
            {
                    board[flankEndRow][flankEndColumn]= reversePlayer(player);
            }
        }
    }
}
void undoFlankInRows(char board[8][8],int row,int column,char player)
{
    if(row>1)
    {//5 3
        int flankEndRow=row;
        int i=1;
        while(board[row-i][column] == player)
        {
            ++i;
            --flankEndRow;
            if(board[row-i][column] == player && board[row-i][column] != '-')
            {
                    board[flankEndRow][column]= reversePlayer(player);
            }
        }
    }
    if((row+2)<8)
    {
        int flankEndRow=row;
        int i=1;
        while(board[row+i][column] == player)
        {
            ++i;
            ++flankEndRow;
            if(board[row+i][column] == player && board[row+i][column] != '-')
            {
                    board[flankEndRow][column]= reversePlayer(player);
            }
        }
    }
}
void undoFlankInAllDirections(char board[8][8],int row,int column,char player)
{
    undoFlankInColumns(board,row,column,player);
    undoFlankInDiagonals(board,row,column,player);
    undoFlankInRows(board,row,column,player);
}

 */