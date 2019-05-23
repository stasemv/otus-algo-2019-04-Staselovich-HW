#include "use_chess.h"

#include <stdio.h>

#include "chess.h"
#include "fen_parcer.h"

void test_chess()
{

    clsChessBoard game;
    game.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KkQq - 0 1");
    std::string fen = generateFEN(game.getBoard());
    printf("fen = %s\n", fen.c_str());
    game.move("e2e2");
    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());
    game.move("e7e7");
    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());


    game.printBoard();
}
