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
    _fen = "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR w KkQq - 0 0";
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

    // Фиксация битого поля
    int row_eP = -1;
    int col_eP = cellTo->pos.col;
    if(isPawn && (cellFrom->pos.col == cellTo->pos.col)) {
        if((cellFrom->man.color == enmCC_white)
                && (cellFrom->pos.row == 1)
                && (cellTo->pos.row == 3))
            row_eP = 2;
        else
            if((cellFrom->man.color == enmCC_black)
                    && (cellFrom->pos.row == 6)
                    && (cellTo->pos.row == 4))
                row_eP = 5;
    }
    bool is_eP = false;
    if(row_eP > -1) {
        sctChessman *enemy;
        if(col_eP > 0) {
            enemy = &_board.field[cellTo->pos.row][col_eP - 1].man;
            if((enemy->type == enmChM_pawn)
                    && (enemy->color != cellFrom->man.color))
                is_eP = true;
        }
        if(col_eP < 7) {
            enemy = &_board.field[cellTo->pos.row][col_eP + 1].man;
            if((enemy->type == enmChM_pawn)
                    && (enemy->color != cellFrom->man.color))
                is_eP = true;
        }
    }
    // Взятие на проходе
    if(_board.enPassant.col > -1)
        if()

    if(is_eP)
        _board.enPassant = {0, row_eP, col_eP};
    else
        _board.enPassant.col = _board.enPassant.row = -1;

    // Перемещение + взятие
    cellTo->man = cellFrom->man;
    cellFrom->man = {enmChM_empty, enmCC_unknown};
    cellTo->isNotMoved = false;

    // Превращение пешки
    if(isChessmanValid(__move.newMan.type))
        if(((cellTo->man.color == enmCC_white)
            &&(cellTo->pos.row == 7)) ||
                ((cellTo->man.color == enmCC_black)
                 &&(cellTo->pos.row == 0)))
            if(cellTo->man.color == __move.newMan.color)
                cellTo->man = __move.newMan;

    // Флаги рокировки
    {
        sctChessman *man = &_board.castl_K;
        int row, col;
        for(int i=0; i < 4; ++i, man++)
            if(isChessmanValid(man->type)) {
                row = (man->color == enmCC_white) ? 0 : 7;
                col = (man->type == enmChM_king) ? 7 : 0;
                sctChessmanState *king = &_board.field[row][3];
                sctChessmanState *rook = &_board.field[row][col];
                if(!king->isNotMoved || !rook->isNotMoved)
                    *man = emptyChessMan;
            }
    }

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
