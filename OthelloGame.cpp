//
// Created by fady on 04/05/23.
//


#include <future>
#include "OthelloGame.h"

bool OthelloGame::isTerminal(char (*board)[ROWS])
{
    if(listOfValidMoves(board,'X').size()==0 && listOfValidMoves(board,'N').size()==0){
        return true;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}

vector<pair<int, int>> OthelloGame::listOfValidMoves(char (*board)[ROWS], char player)
{
    vector<pair<int,int>> listOfValidMoves;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == '-')
            {
                if(isValidMove(board,i,j,player))
                {
                    listOfValidMoves.push_back(make_pair(i,j));
                }
            }
        }
    }
    return listOfValidMoves;
}

bool OthelloGame::isValidMove(char (*board)[ROWS], int row, int column, char player)
{
    if((checkColumns(board,row,column,player) || checkRows(board,row,column,player) || checkDiagonals(board,row,column,player)) && board[row][column] == '-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void OthelloGame::makeMove(char (*board)[ROWS], int row, int column, char player)
{
    board[row][column]=player;
    flankInAllDirections(board,row,column,player);
}

void OthelloGame::undoMove(char (&oldBoard)[ROWS][COLUMNS], char (&board)[ROWS][COLUMNS])
{
    copy(&oldBoard[0][0], &oldBoard[0][0] + (ROWS*COLUMNS), &board[0][0]);
}

void OthelloGame::saveBoard(char (&oldBoard)[ROWS][COLUMNS], char (&board)[ROWS][COLUMNS])
{
    copy(&board[0][0], &board[0][0] + (ROWS*COLUMNS), &oldBoard[0][0]);
}

char OthelloGame::reversePlayer(char player)
{
    if(player=='X')
    {
        return 'N';
    }
    else
    {
        return 'X';
    }
}



bool OthelloGame::checkDiagonals(char board[ROWS][COLUMNS],int row,int column,char player)
{
    if(column>1 && row >1)
    {
        int i=1;
        while(board[row-i][column-i] == reversePlayer(player) && (row-i) > 0 && (column-i) > 0)
        {
            ++i;
            if(board[row-i][column-i] == player){
                return true;
            }
        }
    }
    if( ((column+2)<(COLUMNS)) && ((row+2)<(ROWS)) )
    {
        int i=1;
        while(board[row+i][column+i] == reversePlayer(player) && (row+i)<8 && (column+i)<8)
        {
            ++i;
            if(board[row+i][column+i] == player){
                return true;
            }
        }
    }
    if(column > 1 && (row+2)<(ROWS))
    {
        int i=1;
        while(board[row+i][column-i] == reversePlayer(player) && (row+i)< 8 && (column-i) >0)
        {
            ++i;
            if(board[row+i][column-i] == player){
                return true;
            }
        }
    }
    if((column+2) < (COLUMNS) && row > 1)
    {
        int i=1;
        while(board[row-i][column+i] == reversePlayer(player) && (row-i) >0 && (column+i)<8)
        {
            ++i;
            if(board[row-i][column+i] == player){
                return true;
            }
        }
    }
    return false;
}
bool OthelloGame::checkRows(char board[ROWS][COLUMNS],int row,int column,char player)
{
    if(column>1)
    {
        int i=1;
        while(board[row][column-i] == reversePlayer(player) && (column-i)>0 )
        {
            ++i;
            if(board[row][column-i] == player){
                return true;
            }
        }
    }
    if((column+2)<(COLUMNS))
    {
        int i=1;
        while(board[row][column+i] == reversePlayer(player) && (column+i)<8)
        {
            ++i;
            if(board[row][column+i] == player){
                return true;
            }
        }
    }
    return false;
}
bool OthelloGame::checkColumns(char board[ROWS][COLUMNS],int row,int column,char player)
{
    if(row>1)
    {
        int i=1;
        while(board[row-i][column] == reversePlayer(player) && (row-i) >0 )
        {
            ++i;
            if(board[row-i][column] == player){
                return true;
            }
        }
    }
    if((row+2)<(ROWS))
    {
        int i=1;
        while(board[row+i][column] == reversePlayer(player) && (row+i)<8)
        {
            ++i;
            if(board[row+i][column] == player){
                return true;
            }
        }
    }
    return false;
}

void OthelloGame::flankInColumns(char board[ROWS][COLUMNS],int row,int column,char player)
{
    if(column>1)
    {
        int flankEndColumn=column;
        int i=1;
        while(board[row][column-i] == reversePlayer(player) && (column-i) >0 )
        {
            ++i;
            --flankEndColumn;
            if(board[row][column-i] == player)
            {
                while(flankEndColumn<column)
                {
                    board[row][flankEndColumn]=player;
                    ++flankEndColumn;
                }
            }
        }
    }
    if((column+2)<(COLUMNS))
    {
        int flankEndColumn=column;
        int i=1;
        while(board[row][column+i] == reversePlayer(player) && (column+i)<(COLUMNS) )
        {
            ++i;
            ++flankEndColumn;
            if(board[row][column+i] == player)
            {
                while(flankEndColumn>column)
                {
                    board[row][flankEndColumn]=player;
                    --flankEndColumn;
                }
            }
        }
    }
}
void OthelloGame::flankInDiagonals(char board[ROWS][COLUMNS],int row,int column,char player)
{
    if(column>1 && row >1)
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row-i][column-i] == reversePlayer(player) && (row-i) >0 && (column-i) >0 )
        {
            ++i;
            --flankEndRow;
            --flankEndColumn;
            if(board[row-i][column-i] == player)
            {
                while(flankEndRow < row && flankEndColumn < column)
                {
                    board[flankEndRow][flankEndColumn]=player;
                    ++flankEndRow;
                    ++flankEndColumn;
                }
            }
        }
    }
    if( ((column+2)<(COLUMNS)) && ((row+2)<(ROWS)) )
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row+i][column+i] == reversePlayer(player) && (column+i)<(COLUMNS) && (row+i)<(ROWS))
        {
            ++flankEndRow;
            ++flankEndColumn;
            ++i;
            if(board[row+i][column+i] == player)
            {
                while(flankEndRow > row && flankEndColumn > column)
                {
                    board[flankEndRow][flankEndColumn]=player;
                    --flankEndRow;
                    --flankEndColumn;
                }
            }
        }
    }
    if(column>1 && ((row+2)<(ROWS)) )
    {
        int i=1;
        int flankEndRow=row;
        int flankEndColumn=column;
        while(board[row+i][column-i] == reversePlayer(player) && (row+i)<(ROWS) && (column-i) >0 )
        {
            ++i;
            ++flankEndRow;
            --flankEndColumn;
            if(board[row+i][column-i] == player)
            {
                while(flankEndRow > row && flankEndColumn < column)
                {
                    board[flankEndRow][flankEndColumn]=player;
                    --flankEndRow;
                    ++flankEndColumn;
                }
            }
        }
    }
    if( row > 1 && ((column+2) < (COLUMNS) ))
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row-i][column+i] == reversePlayer(player) && (row-i) >0 && (column+i)<(COLUMNS))
        {
            --flankEndRow;
            ++flankEndColumn;
            ++i;
            if(board[row-i][column+i] == player)
            {
                while(flankEndRow < row && flankEndColumn > column)
                {
                    board[flankEndRow][flankEndColumn]=player;
                    ++flankEndRow;
                    --flankEndColumn;
                }
            }
        }
    }
}
void OthelloGame::flankInRows(char board[ROWS][COLUMNS],int row,int column,char player)
{
    if(row>1)
    {
        int flankEndRow=row;
        int i=1;
        while(board[row-i][column] == reversePlayer(player) && (row-i) >0 )
        {
            ++i;
            --flankEndRow;
            if(board[row-i][column] == player)
            {
                while(flankEndRow<row)
                {
                    board[flankEndRow][column]=player;
                    ++flankEndRow;
                }
            }
        }
    }
    if((row+2)<(ROWS))
    {
        int flankEndRow=row;
        int i=1;
        while(board[row+i][column] == reversePlayer(player) && (row+i)<(ROWS))
        {
            ++i;
            ++flankEndRow;
            if(board[row+i][column] == player)
            {
                while(flankEndRow>row)
                {
                    board[flankEndRow][column]=player;
                    --flankEndRow;
                }

            }
        }
    }
}
void OthelloGame::flankInAllDirections(char board[ROWS][COLUMNS],int row,int column,char player)
{
    flankInColumns(board,row,column,player);
    flankInRows(board,row,column,player);
    flankInDiagonals(board,row,column,player);
}

int OthelloGame::clculateHeuristic(char (*board)[8])
{
    std::vector<std::thread> threads;
    auto parityResult=0;
    auto mobilityResult=0;
    auto cornersResult=0;
    auto stabilityResult=0;
    //auto occupliedEdgesResult=0;

    threads.emplace_back([&](){ parityResult = coinParity(board); });
    threads.emplace_back([&](){ mobilityResult = mobility(board); });
    threads.emplace_back([&](){ cornersResult = cornersCaptured(board); });
    threads.emplace_back([&](){ stabilityResult = stability(board); });
   // threads.emplace_back([&](){ occupliedEdgesResult = occupiedEdgeCoins(board); });


    for (auto& thread : threads) {
        thread.join();
    }

    return parityResult + mobilityResult + cornersResult + stabilityResult;

}
int OthelloGame::coinParity(char board[ROWS][COLUMNS])
{
    int maxPlayerCoins=0;
    int minPlayerCoins=0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == 'X')
            {
                ++maxPlayerCoins;
            }
            else if(board[i][j] == 'N')
            {
                ++minPlayerCoins;
            }
        }
    }

//    cout << "maxPlayer coins "<< maxPlayerCoins << endl << "min player coins "<<minPlayerCoins <<endl;
//    cout <<"returned value " << (maxPlayerCoins-minPlayerCoins) <<endl;
    //return (maxPlayerCoins-minPlayerCoins);
    return( (100*(maxPlayerCoins - minPlayerCoins )) / (maxPlayerCoins + minPlayerCoins )) ;
}
int OthelloGame::mobility(char board[ROWS][COLUMNS])
{
    int maxPlayerActualMobility=0;
    int minPlayerActualMobility=0;
    int actualMobilityValue=0;

    maxPlayerActualMobility = listOfValidMoves(board,'X').size();
    minPlayerActualMobility = listOfValidMoves(board,'N').size();

    if((minPlayerActualMobility + minPlayerActualMobility) !=0)
    {
        actualMobilityValue =
                ( (100 *(maxPlayerActualMobility - minPlayerActualMobility ))/
                 (maxPlayerActualMobility + minPlayerActualMobility ));
    }
    else
    {
        actualMobilityValue = 0;
    }
    return actualMobilityValue;
}

///        Corners Captured calculations
int OthelloGame::cornersCaptured(char board[ROWS][COLUMNS])
{
    int cornerHeuriticValue;
    pair<int,int> playerCornerValues= checkCorners(board);

    if( (playerCornerValues.first + playerCornerValues.second) !=0){

        cornerHeuriticValue =
                ((100*(playerCornerValues.first - playerCornerValues.second))/
                (playerCornerValues.first + playerCornerValues.second ));
    }else
    {
        cornerHeuriticValue = 0;
    }
    return cornerHeuriticValue;
}
pair<int,int> OthelloGame::checkCorners(char board[ROWS][COLUMNS])
{
    int firstCornerForMax=0,secondCornerForMax=0,thirdCornerForMax=0,fourthCornerForMax=0,
            firstCornerForMin=0,secondCornerForMin=0,thirdCornerForMin=0,fourthCornerForMin=0;
    if(board[0][0] !='-'){
        if(board[0][0] == 'X'){
            firstCornerForMax=1;
        }else{
            firstCornerForMin=1;
        }
    }
    if(board[0][7] !='-'){
        if(board[0][7] == 'X'){
            secondCornerForMax=1;
        }else{
            secondCornerForMin=1;
        }
    }
    if(board[7][7] !='-'){
        if(board[0][0] == 'X'){
            thirdCornerForMax=1;
        }else{
            thirdCornerForMin=1;
        }
    }
    if(board[7][0] !='-'){
        if(board[7][0] == 'X'){
            fourthCornerForMax=1;
        }else{
            fourthCornerForMin=1;
        }
    }
    return {firstCornerForMax + secondCornerForMax + thirdCornerForMax + fourthCornerForMax,
            firstCornerForMin + secondCornerForMin + thirdCornerForMin + fourthCornerForMin};
}
bool OthelloGame::isCorner(int row,int column)
{
    if((row==(ROWS-1) && column==(COLUMNS-1)) || (row==0 && column==0) || (row==(ROWS-1) && column==0) || (row==0 && column==(COLUMNS-1)) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

///      Stability calculations
int OthelloGame::stability(char board[ROWS][COLUMNS])
{
    int stabilityValue;
    // max stability value then min stability value
    pair<int,int> playerStabilityValues= countStableAndUnStableCoins(board);
    if((playerStabilityValues.first + playerStabilityValues.second ) !=0){
        stabilityValue =
                ( (100*(playerStabilityValues.first - playerStabilityValues.second ))/
                 (playerStabilityValues.first + playerStabilityValues.second));

    }
    else
    {
        stabilityValue = 0;
    }
    return stabilityValue;
}
pair<int,int> OthelloGame::countStableAndUnStableCoins(char board[ROWS][COLUMNS])
{
    int maxStableCoins=0;
    int maxUnStableCoins=0;
    int maxStabilityValue=0;

    int minStableCoins=0;
    int minUnStableCoins=0;
    int minStabilityValue=0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {

            if (board[i][j] != '-')
            {
                if(board[i][j] == 'X')
                {
                    if(isCorner(i,j))
                    {
                        maxStableCoins++;
                        continue;
                    }else
                    {
                        for (pair<int,int> move : listOfValidMoves(board,'N'))
                        {
                            maxUnStableCoins+= toBeFlankedCoins(board,move,'N');
                        }

                    }

                }
                else
                {
                    if(isCorner(i,j))
                    {
                        ++minStableCoins;
                        continue;
                    }else
                    {
                        for (pair<int,int> move : listOfValidMoves(board,'X'))
                        {
                            minUnStableCoins+= toBeFlankedCoins(board,move,'X');
                        }

                    }
                }

            }

        }
    }
    maxStabilityValue=maxStableCoins-maxUnStableCoins;
    minStabilityValue=minStableCoins-minUnStableCoins;
    return {maxStabilityValue,minStabilityValue};
}
int OthelloGame::toBeFlankedCoins(char board[ROWS][COLUMNS],pair<int,int> move,char player)
{
    return countToBeFlankedCoinsInColumns(board,move.first,move.second,player) +
           countToBeFlankedCoinsInRows(board,move.first,move.second,player) +
           countToBeFlankedCoinsInDiagonals(board,move.first,move.second,player);
}


/// TODO: think of the condition
int OthelloGame::countToBeFlankedCoinsInRows(char board[ROWS][COLUMNS],int row,int column,char player)
{
    int numberOfFlankedCoins=0;
    if(row>1)
    {
        int flankEndRow=row;
        int i=1;
        while(board[row-i][column] == reversePlayer(player)  )
        {
            --i;
            --flankEndRow;
            if(board[row-i][column] == player && (row-i) >0)
            {
                while(flankEndRow<row)
                {
                    ++numberOfFlankedCoins;
                    ++flankEndRow;
                }
            }
        }
    }
    if((row+2)<(ROWS))
    {
        int flankEndRow=row;
        int i=1;
        while(board[row+i][column] == reversePlayer(player) && (row+i)<(ROWS))
        {
            ++i;
            ++flankEndRow;
            if(board[row+i][column] == player)
            {
                while(flankEndRow>row)
                {
                    ++numberOfFlankedCoins;
                    --flankEndRow;
                }

            }
        }
    }
    return numberOfFlankedCoins;
}
int OthelloGame::countToBeFlankedCoinsInColumns(char board[ROWS][COLUMNS],int row,int column,char player)
{
    int toBeFlankedCoins=0;
    if(column>1)
    {
        int flankEndColumn=column;
        int i=1;
        while(board[row][column-i] == reversePlayer(player) && (column-i) >0 )
        {
            ++i;
            --flankEndColumn;
            if(board[row][column-i] == player)
            {
                while(flankEndColumn<column)
                {
                    ++toBeFlankedCoins;
                    ++flankEndColumn;
                }
            }
        }
    }
    if((column+2)<(COLUMNS))
    {
        int flankEndColumn=column;
        int i=1;
        while(board[row][column+i] == reversePlayer(player) && (column+i)<(COLUMNS))
        {
            ++i;
            ++flankEndColumn;
            if(board[row][column+i] == player)
            {
                while(flankEndColumn>column)
                {
                    ++toBeFlankedCoins;
                    --flankEndColumn;
                }
            }
        }
    }
    return toBeFlankedCoins;
}
int OthelloGame::countToBeFlankedCoinsInDiagonals(char board[ROWS][COLUMNS],int row,int column,char player)
{
    int toBeFlankedCoins=0;
    if(column>1 && row >1)
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row-i][column-i] == reversePlayer(player) && (row-i) >0 && (column-i) >0)
        {
            ++i;
            --flankEndRow;
            --flankEndColumn;
            if(board[row-i][column-i] == player)
            {
                while(flankEndRow < row && flankEndColumn < column)
                {
                    ++toBeFlankedCoins;
                    ++flankEndRow;
                    ++flankEndColumn;
                }
            }
        }
    }
    if( ((column+2)<(COLUMNS)) && ((row+2)<(ROWS)) )
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row+i][column+i] == reversePlayer(player) && (column+i)<(COLUMNS) && (row+i)<(ROWS))
        {
            ++flankEndRow;
            ++flankEndColumn;
            ++i;
            if(board[row+i][column+i] == player)
            {
                while(flankEndRow > row && flankEndColumn > column)
                {
                    ++toBeFlankedCoins;
                    --flankEndRow;
                    --flankEndColumn;
                }
            }
        }
    }
    if(column>1 && ((row+2)<(ROWS)) )
    {
        int i=1;
        int flankEndRow=row;
        int flankEndColumn=column;
        while(board[row+i][column-i] == reversePlayer(player) && (row+i)<(ROWS) && (column-i) >0 )
        {
            ++i;
            ++flankEndRow;
            --flankEndColumn;
            if(board[row+i][column-i] == player)
            {
                while(flankEndRow > row && flankEndColumn < column)
                {
                    ++toBeFlankedCoins;
                    --flankEndRow;
                    ++flankEndColumn;
                }
            }
        }
    }
    if((column+2) < (COLUMNS) && row > 1)
    {
        int flankEndRow=row;
        int flankEndColumn=column;
        int i=1;
        while(board[row-i][column+i] == reversePlayer(player) && (row-i) >0 && (column+i)<(COLUMNS))
        {
            ++i;
            --flankEndRow;
            ++flankEndColumn;
            if(board[row-i][column+i] == player)
            {
                while(flankEndRow > row && flankEndColumn < column)
                {
                    ++toBeFlankedCoins;
                    ++flankEndRow;
                    --flankEndColumn;
                }
            }
        }
    }
    return toBeFlankedCoins;
}

int OthelloGame::occupiedEdgeCoins(char board[ROWS][COLUMNS])
{
    int occupiedEdgeValue;
    // max stability value then min stability value
    pair<int,int> playerOccupiedEdges= countEdgeCoins(board);
    if((playerOccupiedEdges.first + playerOccupiedEdges.second ) !=0){
        occupiedEdgeValue =
                ( (100*(playerOccupiedEdges.first - playerOccupiedEdges.second ))/
                  (playerOccupiedEdges.first + playerOccupiedEdges.second));

    }
    else
    {
        occupiedEdgeValue = 0;
    }
    return occupiedEdgeValue;
}
pair<int,int> OthelloGame::countEdgeCoins(char board[ROWS][COLUMNS])
{
    int numberOfEdgesOccupiedByMax=0;
    int numberOfEdgesOccupiedByMin=0;
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {

            if(row == 0 || column == 0  || row == (ROWS-1) || column ==(COLUMNS-1)){

            if (board[row][column] != '-')
            {
                if(board[row][column] == 'X')
                {
                    ++numberOfEdgesOccupiedByMax;
                }
                else
                {
                    ++numberOfEdgesOccupiedByMin;
                }
              }
            }
        }
    }
}

char OthelloGame::getWinner(char (*board)[ROWS])
{
    int maxPlayerCoins=0;
    int minPlayerCoins=0;
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            if (board[row][column] == 'X')
            {
                ++maxPlayerCoins;
            }
            else if(board[row][column] == 'N')
            {
                ++minPlayerCoins;
            }
        }
    }
    if(maxPlayerCoins>minPlayerCoins){
        return 'X';
    }else{
        return 'N';
    }
}

pair<int,int> OthelloGame::getCurrentScore(char (*board)[8]) {
    int maxPlayerCoins=0;
    int minPlayerCoins=0;
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            if(board[row][column])
            if (board[row][column] == 'X')
            {
                ++maxPlayerCoins;
            }
            else if(board[row][column] == 'N')
            {
                ++minPlayerCoins;
            }
        }
    }
}
