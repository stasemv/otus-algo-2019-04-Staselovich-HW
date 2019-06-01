#ifndef FEN_UTILS_H
#define FEN_UTILS_H

typedef enum enmChessman {
    enmChM_empty = 0,   // ������ ������
    enmChM_king,    // ������
    enmChM_queen,   // �����
    enmChM_rook,    // �����
    enmChM_bishop,  // ����
    enmChM_knight,  // ����
    enmChM_pawn,    // �����
    enmChM_unknown,
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
    int  row;
    int  col;
} sctChessmanPosition;

typedef struct sctChessmanState {
    sctChessman man;
    sctChessmanPosition pos;
    bool isNotMoved;
} sctChessmanState;

typedef struct sctChessBoard {
    sctChessmanState *chessmans[64]; // ��������� �����
    int chessmansCount; // ���-�� ����� �� �����
    sctChessmanState field[8][8];

    bool isWhiteStep;   // ��� �����

    // ��������� ���������
    sctChessman castl_K;
    sctChessman castl_Q;
    sctChessman castl_k;
    sctChessman castl_q;

    sctChessmanPosition enPassant;  // ������ �� �������

    int halfmoveClock;  // halfmove clock

    int fullmoveNumber; // fullmove number
} sctChessBoard;

typedef struct sctChessMove {
    sctChessmanPosition from;
    sctChessmanPosition to;
    sctChessman newMan;
} sctChessMove;

typedef enum enmCharType {
    enmCT_unknown = 0,
    enmCT_letter,
    enmCT_digit,
    enmCT_slash,
    enmCT_space,
    enmCT_dash,
    enmCT_amount
} enmCharType;

const sctChessman emptyChessMan = {enmChM_empty, enmCC_unknown};
const unsigned long ul1 = 0x1;

enmChessman getChessmanType(char ch);
char getChessmanName(sctChessman man);
sctChessman getChessman(char ch);
bool isChessmanValid(enmChessman __type);
int getChessmanAsInt(enmChessman type, enmChessColor clr);
void clearBoard(sctChessBoard *board);

#endif // FEN_UTILS_H
