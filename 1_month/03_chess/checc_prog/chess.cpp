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
    _fen = getFENByState(&_board);
}

void clsChessBoard::resetBoard()
{
    _fen = "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR";
    _board = getStateByFEN(_fen);
}

int clsChessBoard::doMove(sctChessMove __move)
{
    sctChessmanState *cellFrom = &_board.field[__move.from.row][__move.from.col];
    sctChessmanState *cellTo = &_board.field[__move.to.row][__move.to.col];
    if(cellFrom->man.color == cellTo->man.color)
        return 1;
    if(!isChessmanValid(cellFrom->man.type))
        return 1;

    bool isPawn = (cellFrom->man.type == enmChM_pawn);
    bool isBitted = isChessmanValid(cellTo->man.type);

    // moving
    cellTo->man = cellFrom->man;
    cellFrom->man = {enmChM_empty, enmCC_unknown};
    cellTo->isNotMoved = false;

    // Изменение очерёдности хода
    _board.isWhiteStep ^= 1;

    // Приращение номера хода
    if(_board.isWhiteStep)
        _board.fullmoveNumber++;

    // Увеличение счётчика полуходов
    if(!isPawn && !isBitted)
        _board.halfmoveClock++;
    else
        _board.halfmoveClock = 0;

    return 0;
}

std::string clsChessBoard::getFENByState(sctChessBoard *b)
{    
    return generateFEN(b);
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

sctChessBoard * clsChessBoard::getBoard()
{
    return &_board;
}

std::string clsChessBoard::getFEN()
{
    return _fen;
}

void clsChessBoard::printBoard()
{
    printf("Board:\n");
    _fen = generateFEN(&_board);
    printf("FEN : %s\n", _fen.c_str());

    sctChessmanState *cell;
    printf("  +-----------------+\n");
    for(int i=7; i>=0; --i) {
        printf("%i | ",i+1);
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
    printf("fen = %s\n", generateFEN(&_board).c_str());
}
