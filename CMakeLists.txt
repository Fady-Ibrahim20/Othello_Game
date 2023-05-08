cmake_minimum_required(VERSION 3.25)
project(AI)

set(CMAKE_CXX_STANDARD 17)

add_executable(AI main.cpp SearchAlgorithm.h Game.h OthelloGame.cpp OthelloGame.h MiniMaxAlgorithm.cpp MiniMaxAlgorithm.h Constants.h AlphaBetaPruningAlgorithm.cpp AlphaBetaPruningAlgorithm.h)
