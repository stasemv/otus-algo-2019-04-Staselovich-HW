#include "chess.h"

#include <cstring>

#include "fen_parcer.h"

clsChessBoard::clsChessBoard()
{
    memset(&board, 0, sizeof(board));
}

void clsChessBoard::resetBoard()
{
    fen = "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR";
    board = getStateByFEN(fen);
}

std::string clsChessBoard::getFENByState(sctChessBoard *b)
{

}

sctChessBoard clsChessBoard::getStateByFEN(std::string fen_)
{
    sctChessBoard brd;
    memset(&board, 0, sizeof(brd));

    return brd;
}
