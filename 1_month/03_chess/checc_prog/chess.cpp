#include "chess.h"

#include <cstring>
#include <stdio.h>

#include "fen_parcer.h"

clsChessBoard::clsChessBoard()
{
    memset(&_board, 0, sizeof(_board));
    resetBoard();
}

void clsChessBoard::move(std::string __move)
{
    printf("move: %s\n", __move.c_str());
    sctChessMove move = parceMove(__move);
    doMove(move);
}

void clsChessBoard::resetBoard()
{
    _fen = "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR";
    _board = getStateByFEN(_fen);
}

int clsChessBoard::doMove(sctChessMove __move)
{

    // Изменение очерёдности хода
    _board.isWhiteStep ^= 1;

    // Приращение номера хода
    if(_board.isWhiteStep)
        _board.fullmoveNumber++;

    return 0;
}

std::string clsChessBoard::getFENByState(sctChessBoard *b)
{    
    return generateFEN(*b);
}

sctChessBoard clsChessBoard::getStateByFEN(std::string __fen)
{
    sctChessBoard brd;
    memset(&brd, 0, sizeof(brd));
    _fen = __fen;
    brd = parceFEN(_fen);
    _board = brd;
    return brd;
}

sctChessBoard clsChessBoard::getBoard()
{
    return _board;
}

void clsChessBoard::printBoard()
{
    printf("Board:\n");
    _fen = generateFEN(_board);
    printf("FEN : %s\n", _fen.c_str());

    sctChessmanState *cell;
    printf("  +-----------------+\n");
    for(int i=7; i>=0; --i) {
        printf("%i | ",i);
        for(int j=0; j<8; ++j) {
            cell = &_board.field[i][j];
            printf("%c ", getChessmanName(cell->man));
        }
        printf("|\n");
    }
    printf("  +-----------------+\n");

    printf("    ");
    for(int i=0; i<8; ++i)
        printf("%c ", 'a' + i);
    printf("\n");

}

void clsChessBoard::printFEN()
{
    printf("FEN : %s\n", _fen.c_str());
}

void clsChessBoard::setFEN(std::string __fen)
{
    _fen = __fen;
    _board = parceFEN(_fen);
}
