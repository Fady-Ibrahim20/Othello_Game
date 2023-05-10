//
// Created by fady on 04/05/23.
//


#include "OthelloGame.h"

bool OthelloGame::isTerminal(char (*board)[ROWS])
{
    if(listOfValidMoves(board,MAX_PLAYER).size()==0 && listOfValidMoves(board,MIN_PLAYER).size()==0){
        return true;
    }
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            if (board[row][column] == EMPTY_SQUARE) {
                return false;
            }
        }
    }
    return true;
}

vector<pair<int, int>> OthelloGame::listOfValidMoves(char (*board)[ROWS], char player)
{
    vector<pair<int,int>> listOfValidMoves;
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            if (board[row][column] == EMPTY_SQUARE)
            {
                if(isValidMove(board,row,column,player))
                {
                    listOfValidMoves.push_back(make_pair(row,column));
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
    if(player==MAX_PLAYER)
    {
        return MIN_PLAYER;
    }
    else
    {
        return MAX_PLAYER;
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

int OthelloGame::clculateHeuristic(char (*board)[ROWS])
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

    // TODO: think of stability(count stable and unStable function)
    //threads.emplace_back([&](){ stabilityResult = stability(board); });
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
            if (board[i][j] == MAX_PLAYER)
            {
                ++maxPlayerCoins;
            }
            else if(board[i][j] == MIN_PLAYER)
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

    maxPlayerActualMobility = listOfValidMoves(board,MAX_PLAYER).size();
    minPlayerActualMobility = listOfValidMoves(board,MIN_PLAYER).size();

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
    if(board[0][0] != EMPTY_SQUARE){
        if(board[0][0] == MAX_PLAYER){
            firstCornerForMax=1;
        }else{
            firstCornerForMin=1;
        }
    }
    if(board[0][COLUMNS-1] != EMPTY_SQUARE){
        if(board[0][COLUMNS-1] == MAX_PLAYER){
            secondCornerForMax=1;
        }else{
            secondCornerForMin=1;
        }
    }
    if(board[ROWS-1][COLUMNS-1] != EMPTY_SQUARE){
        if(board[0][0] == MAX_PLAYER){
            thirdCornerForMax=1;
        }else{
            thirdCornerForMin=1;
        }
    }
    if(board[ROWS-1][0] != EMPTY_SQUARE){
        if(board[ROWS-1][0] == MAX_PLAYER){
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

    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {

            if (board[row][column] != EMPTY_SQUARE)
            {
                if(board[row][column] == MAX_PLAYER)
                {
                    if(isCorner(row,column))
                    {
                        maxStableCoins++;
                        continue;
                    }else
                    {
                        for (pair<int,int> move : listOfValidMoves(board,MIN_PLAYER))
                        {
                            maxUnStableCoins+= toBeFlankedCoins(board,move,MIN_PLAYER);
                        }

                    }

                }
                else
                {
                    if(isCorner(row,column))
                    {
                        ++minStableCoins;
                        continue;
                    }else
                    {
                        for (pair<int,int> move : listOfValidMoves(board,MAX_PLAYER))
                        {
                            minUnStableCoins+= toBeFlankedCoins(board,move,MIN_PLAYER);
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

            if (board[row][column] != EMPTY_SQUARE)
            {
                if(board[row][column] == MAX_PLAYER)
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
            if (board[row][column] == MAX_PLAYER)
            {
                ++maxPlayerCoins;
            }
            else if(board[row][column] == MIN_PLAYER)
            {
                ++minPlayerCoins;
            }
        }
    }
    if(maxPlayerCoins>minPlayerCoins){
        return MAX_PLAYER;
    }else{
        return MIN_PLAYER;
    }
}

pair<int,int> OthelloGame::getCurrentScore(char (*board)[8]) {
    int maxPlayerCoins=0;
    int minPlayerCoins=0;
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            if(board[row][column] != EMPTY_SQUARE){
            if (board[row][column] == MAX_PLAYER)
            {
                ++maxPlayerCoins;
            }
            else if(board[row][column] == MIN_PLAYER)
            {
                ++minPlayerCoins;
            }
            }
        }
    }
}
