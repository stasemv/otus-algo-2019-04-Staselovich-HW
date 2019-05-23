#include "fen_utils.h"

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

