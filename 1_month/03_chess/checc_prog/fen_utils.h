#ifndef FEN_UTILS_H
#define FEN_UTILS_H

typedef enum enmChessman {
    enmChM_unknown = 0,
    enmChM_king,    // король
    enmChM_queen,   // ферзь
    enmChM_rook,    // ладья
    enmChM_bishop,  // слон
    enmChM_knight,  // конь
    enmChM_pawn,    // пешка
    enmChM_amount
} enmChessman;

typedef enum enmChessColor {
    enmCC_unknown = 0,
    enmCC_white,
    enmCC_black,
    enmCC_amount
} enmChessColor;

typedef struct sctChessman {
    enmChessman type;
    enmChessColor color;
} sctChessman;

typedef struct sctChessmanPosition {
    unsigned long num;
    char row;
    char col;
} sctChessmanPosition;

typedef struct sctChessmanState {
    sctChessman man;
    sctChessmanPosition pos;
    bool isNotMoved;
} sctChessmanState;

typedef struct sctChessBoard {
    sctChessmanState chessmans[64]; // состояния фигур
    int chessmansCount; // кол-во фигур на доске

    bool isWhiteStep;   // ход белых

    char castlingCount; // кол-во возможных рокировок
    sctChessman castling[4]; // возможные рокировки

    sctChessmanPosition enPassant;  // взятие на проходе

    int halfmoveClock;  // halfmove clock

    int fullmoveNumber; // fullmove number
} sctChessBoard;

typedef enum enmCharType {
    enmCT_unknown = 0,
    enmCT_letter,
    enmCT_digit,
    enmCT_slash,
    enmCT_space,
    enmCT_dash,
    enmCT_amount
} enmCharType;

#endif // FEN_UTILS_H
