#include <QtTest/QtTest>
#include "../../chessboard.h"
#include "../../game.h"
#include "test_context.h"

class MovementSteps : public QObject
{
    Q_OBJECT

private:
    ChessBoard* board;

    bool containsMove(const QVector<Area>& moves, int row, int col) {
        for (const Area& area : moves) {
            if (area.row == row && area.col == col) {
                return true;
            }
        }
        return false;
    }

    bool containsMoveWithStatus(const QVector<Area>& moves, int row, int col, status expectedStatus) {
        for (const Area& area : moves) {
            if (area.row == row && area.col == col && area.state == expectedStatus) {
                return true;
            }
        }
        return false;
    }

private slots:
    void init() {
        board = new ChessBoard(nullptr);
    }

    void cleanup() {
        delete board;
    }

    // PAWN TESTS
    void test_white_pawn_one_square_forward() {
        board->loadRes(":/board.txt");
        QVector<Area> moves = board->getTurnArea(board->boardMap[6][4]);
        QVERIFY(containsMove(moves, 5, 4));
    }

    void test_white_pawn_two_squares_first_move() {
        board->loadRes(":/board.txt");
        QVector<Area> moves = board->getTurnArea(board->boardMap[6][4]);
        QVERIFY(containsMove(moves, 4, 4));
    }

    void test_black_pawn_one_square_forward() {
        board->loadRes(":/board.txt");
        QVector<Area> moves = board->getTurnArea(board->boardMap[1][4]);
        QVERIFY(containsMove(moves, 2, 4));
    }

    void test_black_pawn_two_squares_first_move() {
        board->loadRes(":/board.txt");
        QVector<Area> moves = board->getTurnArea(board->boardMap[1][4]);
        QVERIFY(containsMove(moves, 3, 4));
    }

    void test_pawn_blocked_by_piece() {
        // Create custom board with blocking piece
        ChessPiece* whitePawn = new ChessPiece(board, WHITE, PAWN, 5, 4);
        ChessPiece* whiteKnight = new ChessPiece(board, WHITE, KNIGHT, 4, 4);
        board->boardMap[5][4] = whitePawn;
        board->boardMap[4][4] = whiteKnight;

        QVector<Area> moves = board->getTurnArea(whitePawn);
        QVERIFY(!containsMove(moves, 4, 4));
    }

    void test_white_pawn_capture_diagonal_left() {
        ChessPiece* whitePawn = new ChessPiece(board, WHITE, PAWN, 5, 4);
        ChessPiece* blackPawn = new ChessPiece(board, BLACK, PAWN, 4, 3);
        board->boardMap[5][4] = whitePawn;
        board->boardMap[4][3] = blackPawn;

        QVector<Area> moves = board->getTurnArea(whitePawn);
        QVERIFY(containsMoveWithStatus(moves, 4, 3, ATTACK));
    }

    void test_white_pawn_capture_diagonal_right() {
        ChessPiece* whitePawn = new ChessPiece(board, WHITE, PAWN, 5, 4);
        ChessPiece* blackPawn = new ChessPiece(board, BLACK, PAWN, 4, 5);
        board->boardMap[5][4] = whitePawn;
        board->boardMap[4][5] = blackPawn;

        QVector<Area> moves = board->getTurnArea(whitePawn);
        QVERIFY(containsMoveWithStatus(moves, 4, 5, ATTACK));
    }

    // ROOK TESTS
    void test_rook_moves_horizontal() {
        ChessPiece* whiteRook = new ChessPiece(board, WHITE, ROOK, 4, 2);
        board->boardMap[4][2] = whiteRook;

        QVector<Area> moves = board->getTurnArea(whiteRook);

        QVERIFY(containsMove(moves, 4, 3));
        QVERIFY(containsMove(moves, 4, 4));
        QVERIFY(containsMove(moves, 4, 1));
        QVERIFY(containsMove(moves, 4, 0));
    }

    void test_rook_moves_vertical() {
        ChessPiece* whiteRook = new ChessPiece(board, WHITE, ROOK, 4, 3);
        board->boardMap[4][3] = whiteRook;

        QVector<Area> moves = board->getTurnArea(whiteRook);

        QVERIFY(containsMove(moves, 3, 3));
        QVERIFY(containsMove(moves, 5, 3));
        QVERIFY(containsMove(moves, 0, 3));
        QVERIFY(containsMove(moves, 7, 3));
    }

    void test_rook_blocked_by_own_piece() {
        ChessPiece* whiteRook = new ChessPiece(board, WHITE, ROOK, 4, 2);
        ChessPiece* whiteKnight = new ChessPiece(board, WHITE, KNIGHT, 4, 5);
        board->boardMap[4][2] = whiteRook;
        board->boardMap[4][5] = whiteKnight;

        QVector<Area> moves = board->getTurnArea(whiteRook);

        QVERIFY(!containsMove(moves, 4, 5));
        QVERIFY(!containsMove(moves, 4, 6));
    }

    void test_rook_can_capture_opponent() {
        ChessPiece* whiteRook = new ChessPiece(board, WHITE, ROOK, 4, 2);
        ChessPiece* blackKnight = new ChessPiece(board, BLACK, KNIGHT, 4, 5);
        board->boardMap[4][2] = whiteRook;
        board->boardMap[4][5] = blackKnight;

        QVector<Area> moves = board->getTurnArea(whiteRook);

        QVERIFY(containsMoveWithStatus(moves, 4, 5, ATTACK));
        QVERIFY(!containsMove(moves, 4, 6));
    }

    // KNIGHT TESTS
    void test_knight_l_shaped_moves() {
        ChessPiece* whiteKnight = new ChessPiece(board, WHITE, KNIGHT, 4, 4);
        board->boardMap[4][4] = whiteKnight;

        QVector<Area> moves = board->getTurnArea(whiteKnight);

        // Check all 8 L-shaped moves
        QVERIFY(containsMove(moves, 2, 5));  // 2 up, 1 right
        QVERIFY(containsMove(moves, 2, 3));  // 2 up, 1 left
        QVERIFY(containsMove(moves, 3, 6));  // 1 up, 2 right
        QVERIFY(containsMove(moves, 3, 2));  // 1 up, 2 left
        QVERIFY(containsMove(moves, 6, 5));  // 2 down, 1 right
        QVERIFY(containsMove(moves, 6, 3));  // 2 down, 1 left
        QVERIFY(containsMove(moves, 5, 6));  // 1 down, 2 right
        QVERIFY(containsMove(moves, 5, 2));  // 1 down, 2 left

        QCOMPARE(moves.size(), 8);
    }

    void test_knight_jumps_over_pieces() {
        ChessPiece* whiteKnight = new ChessPiece(board, WHITE, KNIGHT, 4, 4);
        ChessPiece* whitePawn1 = new ChessPiece(board, WHITE, PAWN, 3, 4);
        ChessPiece* blackPawn1 = new ChessPiece(board, BLACK, PAWN, 4, 5);
        board->boardMap[4][4] = whiteKnight;
        board->boardMap[3][4] = whitePawn1;
        board->boardMap[4][5] = blackPawn1;

        QVector<Area> moves = board->getTurnArea(whiteKnight);

        // Knight should still have 8 moves
        QCOMPARE(moves.size(), 8);
    }

    // BISHOP TESTS
    void test_bishop_diagonal_moves() {
        ChessPiece* whiteBishop = new ChessPiece(board, WHITE, BISHOP, 4, 4);
        board->boardMap[4][4] = whiteBishop;

        QVector<Area> moves = board->getTurnArea(whiteBishop);

        // Check diagonal moves in all 4 directions
        QVERIFY(containsMove(moves, 3, 5));  // up-right
        QVERIFY(containsMove(moves, 2, 6));
        QVERIFY(containsMove(moves, 3, 3));  // up-left
        QVERIFY(containsMove(moves, 2, 2));
        QVERIFY(containsMove(moves, 5, 5));  // down-right
        QVERIFY(containsMove(moves, 6, 6));
        QVERIFY(containsMove(moves, 5, 3));  // down-left
        QVERIFY(containsMove(moves, 6, 2));
    }

    void test_bishop_blocked_by_own_piece() {
        ChessPiece* whiteBishop = new ChessPiece(board, WHITE, BISHOP, 4, 4);
        ChessPiece* whitePawn = new ChessPiece(board, WHITE, PAWN, 2, 6);
        board->boardMap[4][4] = whiteBishop;
        board->boardMap[2][6] = whitePawn;

        QVector<Area> moves = board->getTurnArea(whiteBishop);

        QVERIFY(containsMove(moves, 3, 5));
        QVERIFY(!containsMove(moves, 2, 6));
        QVERIFY(!containsMove(moves, 1, 7));
    }

    // QUEEN TESTS
    void test_queen_moves_all_directions() {
        ChessPiece* whiteQueen = new ChessPiece(board, WHITE, QUEEN, 4, 4);
        board->boardMap[4][4] = whiteQueen;

        QVector<Area> moves = board->getTurnArea(whiteQueen);

        // Horizontal
        QVERIFY(containsMove(moves, 4, 0));
        QVERIFY(containsMove(moves, 4, 7));
        // Vertical
        QVERIFY(containsMove(moves, 0, 4));
        QVERIFY(containsMove(moves, 7, 4));
        // Diagonal
        QVERIFY(containsMove(moves, 0, 0));
        QVERIFY(containsMove(moves, 7, 7));

        QCOMPARE(moves.size(), 27);  // Queen in center has 27 moves
    }

    // KING TESTS
    void test_king_one_square_moves() {
        ChessPiece* whiteKing = new ChessPiece(board, WHITE, KING, 4, 4);
        board->boardMap[4][4] = whiteKing;
        board->fillEndOfGame(WHITE);

        QVector<Area> moves = board->getTurnArea(whiteKing);

        // King should be able to move one square in any direction
        QVERIFY(moves.size() <= 8);
        QVERIFY(moves.size() > 0);
    }

    void test_king_corner_limited_moves() {
        ChessPiece* whiteKing = new ChessPiece(board, WHITE, KING, 0, 0);
        board->boardMap[0][0] = whiteKing;
        board->fillEndOfGame(WHITE);

        QVector<Area> moves = board->getTurnArea(whiteKing);

        // King in corner has at most 3 moves
        QVERIFY(moves.size() <= 3);
    }
};

QTEST_MAIN(MovementSteps)
#include "movement_steps.moc"
