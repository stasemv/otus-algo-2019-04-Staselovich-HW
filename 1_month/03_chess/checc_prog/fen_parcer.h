#ifndef FEN_PARCER_H
#define FEN_PARCER_H

#include <string>
#include <cstring>

#include "fen_utils.h"

typedef enum enmFENParcerState {
    enmFENPS_error = 0,
    enmFENPS_mans,
    enmFENPS_color,
    enmFENPS_castling,
    enmFENPS_enPassant,
    enmFENPS_halfmove,
    enmFENPS_fullmove,
    enmFENPS_amount
} enmFENParcerState;

typedef struct sctFENParcerState {
    sctChessBoard board;
    enmFENParcerState state;
    char row;
    char col;
    char clr;

    void reset() {
        memset(this, 0, sizeof(sctFENParcerState));
        this->state = enmFENPS_mans;
        row = 7;
        col = 0;
        clr = 0;
    }

    sctFENParcerState() {
        this->reset();
    }
} sctFENParcerState;

sctChessBoard parceFEN(std::string fen);
std::string generateFEN(sctChessBoard board);

typedef enum enmMoveParcerState {
    enmMPS_from_col = 0,
    enmMPS_from_row,
    enmMPS_to_col,
    enmMPS_to_row,
    enmMPS_newMan,
    enmMPS_error,
    enmMPS_amount
} enmMoveParcerState;

sctChessMove parceMove(std::string __move);

#endif // FEN_PARCER_H
