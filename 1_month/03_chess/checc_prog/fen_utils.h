#ifndef FEN_UTILS_H
#define FEN_UTILS_H

typedef enum enmChessman {
    enmChM_unknown = 0,
    enmChM_king,    // ������
    enmChM_queen,   // �����
    enmChM_rook,    // �����
    enmChM_bishop,  // ����
    enmChM_knight,  // ����
    enmChM_pawn,    // �����
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
    sctChessmanState chessmans[64]; // ��������� �����
    int chessmansCount; // ���-�� ����� �� �����

    bool isWhiteStep;   // ��� �����

    char castlingCount; // ���-�� ��������� ���������
    sctChessman castling[4]; // ��������� ���������

    sctChessmanPosition enPassant;  // ������ �� �������

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
