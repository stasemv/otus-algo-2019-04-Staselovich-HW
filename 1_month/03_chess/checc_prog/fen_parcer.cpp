#include "fen_parcer.h"

unsigned long ul1 = 0x1;

enmCharType getCharType(char ch)
{
    if(((ch >= 'a') && (ch <= 'z'))
            || ((ch >= 'A') && (ch <= 'Z')))
        return enmCT_letter;
    else if((ch >= '1') && (ch <= '9'))
        return enmCT_digit;
    else if(ch == '/')
        return enmCT_slash;
    else if(ch == ' ')
        return enmCT_space;
    else if(ch == '-')
        return enmCT_dash;
    return enmCT_unknown;
}

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

sctChessman getChessman(char ch)
{
    sctChessman man;
    man.color = enmCC_black;
    if((ch >= 'A') && (ch <= 'Z')) {
        man.color = enmCC_white;
        ch = 'a' + 'A' - ch;
    }
    man.type = getChessmanType(ch);
    return man;
}

void pushFENParcerLetter(sctFENParcerState *parcer, char ch)
{
    sctChessBoard *brd = &parcer->board;
    switch (parcer->state) {
    case enmFENPS_mans:
        if(parcer->col < 8) {
            sctChessman man = getChessman(ch);
            if(man.type != enmChM_unknown) {
                sctChessmanPosition pos =
                {ul1 << (8*parcer->row + parcer->col),
                 parcer->row, parcer->col};
                brd->chessmans[brd->chessmansCount] =
                {man, pos, 1};
                brd->chessmansCount++;
            }
            else
                parcer->state = enmFENPS_error;
        }
        else
            parcer->state = enmFENPS_error;
        break;
    case enmFENPS_color:
        enmChessColor clr;
        switch (ch) {
        case 'w': clr = enmCC_white; break;
        case 'b': clr = enmCC_black; break;
        default: clr = enmCC_unknown; break;
        }
        if(clr != enmCC_unknown) {
            brd->isWhiteStep = (clr == enmCC_white);
            parcer->col = (char)clr;
        }
        else
            parcer->state = enmFENPS_error;
        break;
    case enmFENPS_castling:
        if(brd->castlingCount < 4) {
            sctChessman man = getChessman(ch);
            brd->castling[(int)brd->castlingCount] = man;
            brd->castlingCount++;
        }
        else
            parcer->state = enmFENPS_error;
        break;
    case enmFENPS_enPassant:
        if(brd->enPassant.col < 0)
            brd->enPassant.col = ch - 'a';
        else
            parcer->state = enmFENPS_error;
        break;
    case enmFENPS_halfmove:
    case enmFENPS_fullmove:
    default:
        parcer->state = enmFENPS_error; break;
    }
}

void pushFENParcerDigit(sctFENParcerState *parcer, int num)
{
    switch (parcer->state) {
    case enmFENPS_mans:
        parcer->col += num;
        break;
    case enmFENPS_enPassant:
        if(parcer->board.enPassant.row < 0) {
            parcer->board.enPassant.row = num;
            parcer->board.enPassant.num =
                    ul1 << (8*parcer->board.enPassant.row + num);
        }
        else
            parcer->state = enmFENPS_error;
        break;
    case enmFENPS_halfmove:
        parcer->board.halfmoveClock = num;
        break;
    case enmFENPS_fullmove:
        parcer->board.fullmoveNumber = num;
        break;
    case enmFENPS_color:
    case enmFENPS_castling:
    default:
        parcer->state = enmFENPS_error; break;
    }
}

void pushFENParcerSlash(sctFENParcerState *parcer)
{
    switch (parcer->state) {
    case enmFENPS_mans:
        if(parcer->row > 0) {
            parcer->row--;
            parcer->col = 0;
        }
        else
            parcer->state = enmFENPS_error;
        break;
    case enmFENPS_color:
    case enmFENPS_castling:
    case enmFENPS_enPassant:
    case enmFENPS_halfmove:
    case enmFENPS_fullmove:
    default:
        parcer->state = enmFENPS_error; break;
    }
}

void pushFENParcerSpace(sctFENParcerState *parcer)
{
    switch (parcer->state) {
    case enmFENPS_mans:
        if(parcer->row == 0) {
            parcer->state = enmFENPS_color;
            parcer->col = 0;
        }
        else
            parcer->state = enmFENPS_error;
        break;
    case enmFENPS_color:
        if(parcer->clr != 0)
            parcer->state = enmFENPS_castling;
        else
            parcer->state = enmFENPS_error;
        break;
    case enmFENPS_castling:
        parcer->state = enmFENPS_enPassant;
        break;
    case enmFENPS_enPassant:
        parcer->state = enmFENPS_halfmove;
        break;
    case enmFENPS_halfmove:
        parcer->state = enmFENPS_fullmove;
        break;
    case enmFENPS_fullmove:
        break;
    default:
        parcer->state = enmFENPS_error; break;
    }
}

void pushFENParcerDash(sctFENParcerState *parcer)
{
    switch (parcer->state) {
    case enmFENPS_castling:
        parcer->board.castlingCount = 0;
        break;
    case enmFENPS_enPassant:
        parcer->board.enPassant.row =
                parcer->board.enPassant.col = -1;
        break;
    case enmFENPS_mans:
    case enmFENPS_color:
    case enmFENPS_halfmove:
    case enmFENPS_fullmove:
    default:
        parcer->state = enmFENPS_error; break;
    }
}

sctChessBoard parceFEN(std::string fen)
{
    // parser
    sctFENParcerState parcer;
    for(size_t i=0; i < fen.length(); ++i) {
        char ch = fen[i];
        enmCharType chType = getCharType(ch);
        switch (chType) {
        case enmCT_letter: pushFENParcerLetter(&parcer, ch); break;
        case enmCT_digit: pushFENParcerDigit(&parcer, ch - '0'); break;
        case enmCT_slash: pushFENParcerSlash(&parcer); break;
        case enmCT_space: pushFENParcerSpace(&parcer); break;
        case enmCT_dash: pushFENParcerDash(&parcer); break;
        case enmCT_unknown:
        default :
            parcer.state = enmFENPS_error;
            break;
        }
        if(parcer.state == enmFENPS_error) {
            printf("Cannot to parce FEN-string. Error on %lu char\n", i);
            break;
        }
        }
    return parcer.board;
}
