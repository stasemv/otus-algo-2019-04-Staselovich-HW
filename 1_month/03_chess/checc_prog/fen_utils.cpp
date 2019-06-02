#include "fen_utils.h"

#include <cstring>

enmChessman getChessmanType(char ch)
{
    switch (ch) {
    case 'k': return enmChM_king;
    case 'q': return enmChM_queen;
    case 'r': return enmChM_rook;
    case 'b': return enmChM_bishop;
    case 'n': return enmChM_knight;
    case 'p': return enmChM_pawn;
    default:
        return enmChM_unknown;
    }
    return enmChM_unknown;
}

char getChessmanName(sctChessman man)
{
    int shift = 0;
    if(man.color == enmCC_white)
        shift = 'A' - 'a';
    switch (man.type) {
    case enmChM_king  : return 'k' + shift;
    case enmChM_queen : return 'q' + shift;
    case enmChM_rook  : return 'r' + shift;
    case enmChM_bishop: return 'b' + shift;
    case enmChM_knight: return 'n' + shift;
    case enmChM_pawn  : return 'p' + shift;
    default:
        return '.';
    }
    return '.';
}

sctChessman getChessman(char ch)
{
    sctChessman man;
    man.color = enmCC_black;
    char _ch;
    if((ch >= 'A') && (ch <= 'Z')) {
        man.color = enmCC_white;
        _ch = 'a' + (ch - 'A');
    }
    else
        _ch = ch;
    man.type = getChessmanType(_ch);
    return man;
}

bool isChessmanValid(enmChessman __type) {
    return (__type != enmChM_empty)
            && (__type != enmChM_unknown)
            && (__type != enmChM_amount);
}

int getChessmanAsInt(enmChessman type, enmChessColor clr)
{
    return (type << 2) | clr;
}

void clearBoard(sctChessBoard *board)
{
    memset(board, 0, sizeof(sctChessBoard));
    for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            board->field[i][j].pos = {ul1 << (8*i + j), i, j};
    board->enPassant.col = board->enPassant.row = -1;
}
