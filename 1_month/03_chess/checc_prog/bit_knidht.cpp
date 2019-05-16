#include "bit_knidht.h"

#include <stdio.h>

unsigned long getKnightMoves(unsigned long pos)
{
    // -17, -15, -10, -6, 6, 10, 15, 17
    unsigned long noH = 0x7F7F7F7F7F7F7F7F;
    unsigned long noGH = 0x3F3F3F3F3F3F3F3F;
    unsigned long noA = 0xFEFEFEFEFEFEFEFE;
    unsigned long noAB = 0xFCFCFCFCFCFCFCFC;
    unsigned long poses =
              (((pos >> 10) | (pos << 6)) & noGH)
            | (((pos >> 17) | (pos << 15)) & noH)
            | (((pos >> 15) | (pos << 17)) & noA)
            | (((pos >> 6)  | (pos << 10)) & noAB);
    return poses;
}

int getBitsCount(unsigned long pos)
{
    int res = 0;
    while(pos > 0) {
        res++;
        pos &= pos-1;
    }
    return res;
}

void printBoard(unsigned long pos)
{
    printf("pos = %lx\n", pos);
    printf("bits = %i\n", getBitsCount(pos));
    unsigned long _pos = pos;
    printf("  -------------------\n");
    for(int i=7; i>=0; --i) {
        printf("%i | ",i);
        for(int j=0; j<8; ++j) {
            printf("%lu ", (_pos >> (i*8 + j)) & 1);
        }
        printf("|\n");
    }
    printf("  -------------------\n");

    printf("    ");
    for(int i=0; i<8; ++i)
        printf("%c ", 'a' + i);
    printf("\n");
}

void testBits()
{
//    double pos = 0;
//    unsigned long *pos1 = (unsigned long *)&pos;
//    unsigned long *pos2 = pos1 + 1;
//    *pos2 = 0x1 << 31;

    unsigned long ul1 = 0x1;
    unsigned long pos = ul1 << 32;

    printBoard(pos);
    printBoard(getKnightMoves(pos));
}
