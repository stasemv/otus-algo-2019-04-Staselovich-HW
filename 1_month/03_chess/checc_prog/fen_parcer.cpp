#include "fen_parcer.h"

unsigned long ul1 = 0x1;

enmCharType getCharType(char ch)
{
    if(((ch >= 'a') && (ch <= 'z'))
            || ((ch >= 'A') && (ch <= 'Z')))
        return enmCT_letter;
    else if((ch >= '0') && (ch <= '9'))
        return enmCT_digit;
    else if(ch == '/')
        return enmCT_slash;
    else if(ch == ' ')
        return enmCT_space;
    else if(ch == '-')
        return enmCT_dash;
    return enmCT_unknown;
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
                sctChessmanState cell = {man, pos, 1};
                brd->field[pos.row][pos.col] = cell;
                brd->chessmans[brd->chessmansCount] = &brd->field[pos.row][pos.col];
                brd->chessmansCount++;
            }
            else
                parcer->state = enmFENPS_error;
        }
        else
            parcer->state = enmFENPS_error;
        parcer->col++;
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
            parcer->clr = (char)clr;
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

std::string generateFEN(sctChessBoard board)
{
    std::string fen;
    char ch;
    for(int i=7; i>=0; --i) {
        int emptyFields = 0;
        for(int j=0; j<8; ++j) {
            sctChessmanState *cell = &board.field[i][j];
            if(cell->man.type == enmChM_empty)
                emptyFields++;
            else {
                if(emptyFields) {
                    ch = emptyFields + '0';
                    fen += ch;
                }
                ch = getChessmanName(cell->man);
                fen += ch;
            }
            if((j >= 7) && emptyFields){
                ch = emptyFields + '0';
                fen += ch;
            }
        }
        if(i != 0)
            fen += '/';
    }

    fen += " ";
    if(board.isWhiteStep)
        fen += "w";
    else
        fen += "b";

    fen += " ";
    if(board.castlingCount)
    for(int i=0; i < board.castlingCount; ++i)
        fen += getChessmanName(board.castling[i]);
    else
        fen += "-";

    fen += " ";
    if((board.enPassant.row == 2) || (board.enPassant.row == 5)) {
        fen += 'a' + board.enPassant.col;
        fen += '0' + board.enPassant.row;
    }
    else
        fen += '-';

    fen += " ";
    char semiSteps[8];
    sprintf(semiSteps, "%i", board.halfmoveClock);
    fen += semiSteps;

    fen += " ";
    char fullSteps[8];
    sprintf(fullSteps, "%i", board.fullmoveNumber);
    fen += fullSteps;

    return fen;
}

sctChessMove parceMove(std::string __move)
{
    sctChessMove move;
    memset(&move, 0, sizeof(move));
    enmMoveParcerState moveParcer = enmMPS_from_col;
    for(size_t i=0; i < __move.length(); ++i) {
        char ch = __move[i];
        switch (moveParcer) {
        case enmMPS_from_col :
            move.from.col = ch - 'a';
            break;
        case enmMPS_from_row :
            move.from.row = ch - '0';
            break;
        case enmMPS_to_col :
            move.to.col = ch - 'a';
            break;
        case enmMPS_to_row :
            move.to.row = ch - '0';
            break;
        case enmMPS_newMan :
            move.newMan = getChessman(ch);
            break;
        default :
            moveParcer = enmMPS_error;
        }
        if(moveParcer >= enmMPS_error) {
            printf("Cannot to parce FEN-string. Error on %lu char\n", i);
            break;
        }
        moveParcer = (enmMoveParcerState)((int)moveParcer + 1);
    }
    return move;
}
