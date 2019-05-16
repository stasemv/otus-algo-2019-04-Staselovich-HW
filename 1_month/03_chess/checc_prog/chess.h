#ifndef CHESS_H
#define CHESS_H

#include <string>
#include "fen_utils.h"

class clsChessBoard
{
private:
    sctChessBoard board;
    std::string fen;

    void resetBoard();
    std::string getFENByState(sctChessBoard *b);
    sctChessBoard getStateByFEN(std::string fen);
public:
    clsChessBoard();


};

#endif // CHESS_H
