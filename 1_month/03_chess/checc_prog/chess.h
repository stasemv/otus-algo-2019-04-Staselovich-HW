#ifndef CHESS_H
#define CHESS_H

#include <string>
#include "fen_utils.h"

class clsChessBoard
{
private:
    sctChessBoard _board;
    std::string _fen;

    void resetBoard();
    std::string getFENByState(sctChessBoard *b);
    sctChessBoard getStateByFEN(std::string __fen);
    int doMove(sctChessMove __move);
public:
    clsChessBoard();
    void move(std::string __move);

    sctChessBoard *getBoard();
    std::string getFEN();
    void printBoard();
    void printFEN();
    void setFEN(std::string __fen);

};

#endif // CHESS_H
