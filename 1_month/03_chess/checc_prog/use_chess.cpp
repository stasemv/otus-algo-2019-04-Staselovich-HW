#include "use_chess.h"

#include <stdio.h>

#include "chess.h"
#include "fen_parcer.h"

bool checkFENResult(std::string __fen, clsChessBoard *__board);
bool testFEN(std::string start,
             std::string move,
             std::string finish,
             clsChessBoard *game);
void test_chess()
{
    clsChessBoard game;

////    Тема: Изменение очерёдности и номера хода
//    game.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KkQq - 0 1");
//    game.move("e2e2");
//    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());
//    game.move("e7e7");
//    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());


////    Тема: Увеличение счётчика полуходов без хода пешкой и взятий
//    game.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//    game.move("b1f3");
//    checkFENResult("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 1 1", &game);

//    game.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//    game.move("e2e4");
//    checkFENResult("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1", &game);

//    game.setFEN("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
//    game.move("e5g4");
//    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());
//    checkFENResult("rnbqkb1r/pppppppp/8/8/6N1/8/PPPPPPPP/RNBQKB1R b KQkq - 0 3", &game);

//    game.setFEN("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
//    game.printBoard();
//    game.move("b1c3");
//    game.printBoard();
//    printf("fen = %s\n", generateFEN(game.getBoard()).c_str());
//    checkFENResult("rnbqkb1r/pppppppp/8/4N3/6n1/2N5/PPPPPPPP/R1BQKB1R b KQkq - 5 3", &game);


////    ПЕРЕМЕЩЕНИЕ

////    Тема: Ход без взятия
//    game.setFEN("k7/r7/b7/q7/N7/B7/R7/K7 w - - 15 48");
//    game.printBoard();
//    game.move("a2h2");
//    game.printBoard();
//    checkFENResult("k7/r7/b7/q7/N7/B7/7R/K7 b - - 16 48", &game);

//    testFEN("k7/r7/b7/q7/N7/B7/7R/K7 b - - 16 48",
//            "a5e1",
//            "k7/r7/b7/8/N7/B7/7R/K3q3 w - - 17 49",
//            &game);

////    Тема: Ход со взятием
//    testFEN("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2",
//            "e4d5",
//            "rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2",
//            &game);
//    testFEN("rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2",
//            "d8d5",
//            "rnb1kbnr/ppp1pppp/8/3q4/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3",
//            &game);


////    Тема: Превращение пешки
//        testFEN("rnbqkbnr/pppp1ppp/4P3/8/8/8/Pp3PPP/RNBQKBNR b KQkq - 0 5",
//                "b2a1q",
//                "rnbqkbnr/pppp1ppp/4P3/8/8/8/P4PPP/qNBQKBNR w Kkq - 0 6",
//                &game);
//        testFEN("rnbqkbnr/pppp1ppp/4P3/8/8/8/Pp3PPP/RNBQKBNR b KQkq - 0 5",
//                "b2a1b",
//                "rnbqkbnr/pppp1ppp/4P3/8/8/8/P4PPP/bNBQKBNR w Kkq - 0 6",
//                &game);
//        testFEN("rnbqkbnr/pppP1ppp/4p3/8/8/8/P4PPP/qNBQKBNR w Kkq - 0 6",
//                "d7c8R",
//                "rnRqkbnr/ppp2ppp/4p3/8/8/8/P4PPP/qNBQKBNR b Kkq - 0 6",
//                &game);
//        testFEN("rnbqkbnr/pppP1ppp/4p3/8/8/8/P4PPP/qNBQKBNR w Kkq - 0 6",
//                "d7c8N",
//                "rnNqkbnr/ppp2ppp/4p3/8/8/8/P4PPP/qNBQKBNR b Kkq - 0 6",
//                &game);


////    Тема: Фиксация битого поля
//        testFEN("rnbqkbnr/ppp1pppp/8/4P3/3p4/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3",
//                "c2c4",
//                "rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3",
//                &game);
//        testFEN("rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3",
//                "f7f5",
//                "rnbqkbnr/ppp1p1pp/8/4Pp2/2Pp4/8/PP1P1PPP/RNBQKBNR w KQkq f6 0 4",
//                &game);
//        testFEN("rnbqkbnr/ppp1pppp/8/8/3p4/N6N/PPPPPPPP/R1BQKB1R w KQkq - 0 3",
//                "b2b4",
//                "rnbqkbnr/ppp1pppp/8/8/1P1p4/N6N/P1PPPPPP/R1BQKB1R b KQkq - 0 3",
//                &game);

//    //    Тема: Взятие на проходе
//    testFEN("rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3",
//            "d4c3",
//            "rnbqkbnr/ppp1pppp/8/4P3/8/2p5/PP1P1PPP/RNBQKBNR w KQkq - 0 4",
//            &game);
//    testFEN("r1bqkbnr/ppp1p1pp/2n5/4PpP1/8/2p5/PP1P1P1P/RNBQKBNR w KQkq f6 0 6",
//            "g5f6",
//            "r1bqkbnr/ppp1p1pp/2n2P2/4P3/8/2p5/PP1P1P1P/RNBQKBNR b KQkq - 0 6",
//            &game);
//    testFEN("r1bqkbnr/ppp1p1pp/2n5/4PpP1/8/2p5/PP1P1P1P/RNBQKBNR w KQkq f6 0 6",
//            "e5f6",
//            "r1bqkbnr/ppp1p1pp/2n2P2/6P1/8/2p5/PP1P1P1P/RNBQKBNR b KQkq - 0 6",
//            &game);
//    testFEN("r2qkbnr/pppbp2p/2n2p2/4PpP1/8/2p2N2/PP1P1P1P/RNBQK2R w KQkq - 0 9",
//            "e5f6",
//            "r2qkbnr/pppbp2p/2n2P2/5pP1/8/2p2N2/PP1P1P1P/RNBQK2R b KQkq - 0 9",
//            &game);

////    Тема: Убирание флага рокировки при ходе королём
//    testFEN("r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16",
//            "e8d8",
//            "r2k3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
//            &game);
//    testFEN("r2k3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
//            "e1d1",
//            "r2k3r/pppppppp/8/N7/8/8/PPPPPPPP/R2K3R b - - 2 17",
//            &game);
//    testFEN("r3k2r/pppppppp/8/n7/2N5/8/PPPPPPPP/R3K2R w KQkq - 4 16",
//            "e1d1",
//            "r3k2r/pppppppp/8/n7/2N5/8/PPPPPPPP/R2K3R b kq - 5 16",
//            &game);
//    testFEN("r3k2r/pppppppp/8/n7/2N5/8/PPPPPPPP/R3K2R w KQkq - 4 16",
//            "e1f1",
//            "r3k2r/pppppppp/8/n7/2N5/8/PPPPPPPP/R4K1R b kq - 5 16",
//            &game);

////    Тема: Убирание флага рокировки при ходе ладьёй
//    testFEN("r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16",
//            "a8b8",
//            "1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQk - 1 17",
//            &game);
//    testFEN("1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQk - 1 17",
//            "h1g1",
//            "1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 b Qk - 2 17",
//            &game);
//    testFEN("1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 b Qk - 2 17",
//            "h8g8",
//            "1r2k1r1/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 w Q - 3 18",
//            &game);
//    testFEN("1r2k1r1/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 w Q - 3 18",
//            "a1c1",
//            "1r2k1r1/pppppppp/8/N7/8/8/PPPPPPPP/2R1K1R1 b - - 4 18",
//            &game);

//    Тема: Рокировка в короткую сторону
    testFEN("r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16",
            "e8g8",
            "r4rk1/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
            &game);
    testFEN("r4rk1/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
            "e1g1",
            "r4rk1/pppppppp/8/N7/8/8/PPPPPPPP/R4RK1 b - - 2 17",
            &game);

    //    Тема: Рокировка в длинную сторону
    testFEN("r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16",
            "e8c8",
            "2kr3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
            &game);
    testFEN("2kr3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
            "e1c1",
            "2kr3r/pppppppp/8/N7/8/8/PPPPPPPP/2KR3R b - - 2 17",
            &game);

    if(0)
    testFEN("",
            "",
            "",
            &game);
//    game.printBoard();
}

bool testFEN(std::string start,
             std::string move,
             std::string finish,
             clsChessBoard *game)
{
    game->setFEN(start);
    game->printBoard();
    game->move(move);
    game->printBoard();
    return checkFENResult(finish, game);
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
