#include <QtTest/QtTest>
#include "../../chessboard.h"
#include "../../game.h"
#include "test_context.h"

class DiagonalMovementSteps : public QObject
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

    // Test diagonal moves in all 4 directions
    void test_diagonal_up_right() {
        QVector<Area> moves = board->getDiagonalStatus(4, 4, WHITE);

        QVERIFY(containsMove(moves, 3, 5));
        QVERIFY(containsMove(moves, 2, 6));
        QVERIFY(containsMove(moves, 1, 7));
    }

    void test_diagonal_up_left() {
        QVector<Area> moves = board->getDiagonalStatus(4, 4, WHITE);

        QVERIFY(containsMove(moves, 3, 3));
        QVERIFY(containsMove(moves, 2, 2));
        QVERIFY(containsMove(moves, 1, 1));
        QVERIFY(containsMove(moves, 0, 0));
    }

    void test_diagonal_down_right() {
        QVector<Area> moves = board->getDiagonalStatus(4, 4, WHITE);

        QVERIFY(containsMove(moves, 5, 5));
        QVERIFY(containsMove(moves, 6, 6));
        QVERIFY(containsMove(moves, 7, 7));
    }

    void test_diagonal_down_left() {
        QVector<Area> moves = board->getDiagonalStatus(4, 4, WHITE);

        QVERIFY(containsMove(moves, 5, 3));
        QVERIFY(containsMove(moves, 6, 2));
        QVERIFY(containsMove(moves, 7, 1));
    }

    void test_diagonal_from_corner() {
        QVector<Area> moves = board->getDiagonalStatus(0, 0, WHITE);

        // Only down-right direction available
        QVERIFY(containsMove(moves, 1, 1));
        QVERIFY(containsMove(moves, 2, 2));

        // Should have exactly 7 moves
        QCOMPARE(moves.size(), 7);
    }

    void test_diagonal_stops_at_boundary() {
        QVector<Area> moves = board->getDiagonalStatus(1, 1, WHITE);

        // Check it stops at board edge
        QVERIFY(containsMove(moves, 0, 0));

        // Verify all moves are within bounds
        for (const Area& area : moves) {
            QVERIFY(area.row >= 0 && area.row < 8);
            QVERIFY(area.col >= 0 && area.col < 8);
        }
    }

    void test_diagonal_blocked_by_own_piece() {
        ChessPiece* whitePawn = new ChessPiece(board, WHITE, PAWN, 2, 6);
        board->boardMap[2][6] = whitePawn;

        QVector<Area> moves = board->getDiagonalStatus(4, 4, WHITE);

        QVERIFY(containsMove(moves, 3, 5));
        QVERIFY(!containsMove(moves, 2, 6));
        QVERIFY(!containsMove(moves, 1, 7));
    }

    void test_diagonal_can_capture_opponent() {
        ChessPiece* blackPawn = new ChessPiece(board, BLACK, PAWN, 2, 6);
        board->boardMap[2][6] = blackPawn;

        QVector<Area> moves = board->getDiagonalStatus(4, 4, WHITE);

        QVERIFY(containsMoveWithStatus(moves, 3, 5, ENABLE));
        QVERIFY(containsMoveWithStatus(moves, 2, 6, ATTACK));
        QVERIFY(!containsMove(moves, 1, 7));
    }

    void test_diagonal_all_moves_within_bounds() {
        QVector<Area> moves = board->getDiagonalStatus(4, 4, WHITE);

        for (const Area& area : moves) {
            QVERIFY(area.row >= 0 && area.row < 8);
            QVERIFY(area.col >= 0 && area.col < 8);
        }
    }

    void test_diagonal_from_center_has_13_moves() {
        QVector<Area> moves = board->getDiagonalStatus(4, 4, WHITE);
        QCOMPARE(moves.size(), 13);
    }
};

QTEST_MAIN(DiagonalMovementSteps)
#include "diagonal_movement_steps.moc"
