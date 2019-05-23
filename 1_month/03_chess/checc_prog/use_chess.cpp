#include "use_chess.h"

#include <stdio.h>

#include "chess.h"
#include "fen_parcer.h"

bool checkFENResult(std::string __fen, clsChessBoard *__board);

void test_chess()
{

    clsChessBoard game;
    game.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KkQq - 0 1");
    game.move("e2e2");
    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());
    game.move("e7e7");
    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());

    //
//    game.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//    game.move("b1f3");
//    checkFENResult("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 1 1", &game);

//    game.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//    game.move("e2e4");
//    checkFENResult("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1", &game);

    game.setFEN("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
    game.move("e5g4");
    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());
    checkFENResult("rnbqkb1r/pppppppp/8/8/6N1/8/PPPPPPPP/RNBQKB1R b KQkq - 0 3", &game);

    game.setFEN("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
    game.printBoard();
    game.move("b1c3");
    game.printBoard();
    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());
    checkFENResult("rnbqkb1r/pppppppp/8/4N3/6n1/2N5/PPPPPPPP/R1BQKB1R b KQkq - 5 3", &game);


    game.printBoard();
}

bool checkFENResult(std::string __fen, clsChessBoard *__board)
{
    bool res = !__fen.compare(__board->getFEN());
    if(res)
        printf("fen is valid\n");
    else
        fprintf(stderr, "fen is NOT valid\n");
    return res;
}
