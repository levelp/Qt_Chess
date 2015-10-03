#include <QtTest/QtTest>
#include "../../chessboard.h"
#include "../../game.h"
#include "test_context.h"

class HorizontalMovementSteps : public QObject
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

    // Test horizontal moves to the right
    void test_horizontal_right() {
        QVector<Area> moves = board->getHorizontalStatus(4, 2, WHITE);

        QVERIFY(containsMove(moves, 4, 3));
        QVERIFY(containsMove(moves, 4, 4));
        QVERIFY(containsMove(moves, 4, 5));
        QVERIFY(containsMove(moves, 4, 6));
        QVERIFY(containsMove(moves, 4, 7));
    }

    // Test horizontal moves to the left
    void test_horizontal_left() {
        QVector<Area> moves = board->getHorizontalStatus(4, 5, WHITE);

        QVERIFY(containsMove(moves, 4, 4));
        QVERIFY(containsMove(moves, 4, 3));
        QVERIFY(containsMove(moves, 4, 2));
        QVERIFY(containsMove(moves, 4, 1));
        QVERIFY(containsMove(moves, 4, 0));
    }

    // Test vertical moves upward
    void test_vertical_up() {
        QVector<Area> moves = board->getHorizontalStatus(5, 3, WHITE);

        QVERIFY(containsMove(moves, 4, 3));
        QVERIFY(containsMove(moves, 3, 3));
        QVERIFY(containsMove(moves, 2, 3));
        QVERIFY(containsMove(moves, 1, 3));
        QVERIFY(containsMove(moves, 0, 3));
    }

    // Test vertical moves downward
    void test_vertical_down() {
        QVector<Area> moves = board->getHorizontalStatus(2, 3, WHITE);

        QVERIFY(containsMove(moves, 3, 3));
        QVERIFY(containsMove(moves, 4, 3));
        QVERIFY(containsMove(moves, 5, 3));
        QVERIFY(containsMove(moves, 6, 3));
        QVERIFY(containsMove(moves, 7, 3));
    }

    // Test stops at boundary
    void test_stops_at_boundary_horizontal() {
        QVector<Area> moves = board->getHorizontalStatus(4, 6, WHITE);

        QVERIFY(containsMove(moves, 4, 7));

        // Should not go beyond board
        for (const Area& area : moves) {
            QVERIFY(area.col >= 0 && area.col < 8);
        }
    }

    void test_stops_at_boundary_vertical() {
        QVector<Area> moves = board->getHorizontalStatus(6, 3, WHITE);

        QVERIFY(containsMove(moves, 7, 3));

        // Should not go beyond board
        for (const Area& area : moves) {
            QVERIFY(area.row >= 0 && area.row < 8);
        }
    }

    // Test blocked by own piece
    void test_blocked_by_own_piece_horizontal() {
        ChessPiece* whitePawn = new ChessPiece(board, WHITE, PAWN, 4, 5);
        board->boardMap[4][5] = whitePawn;

        QVector<Area> moves = board->getHorizontalStatus(4, 2, WHITE);

        QVERIFY(containsMove(moves, 4, 3));
        QVERIFY(containsMove(moves, 4, 4));
        QVERIFY(!containsMove(moves, 4, 5));
        QVERIFY(!containsMove(moves, 4, 6));
    }

    void test_blocked_by_own_piece_vertical() {
        ChessPiece* whitePawn = new ChessPiece(board, WHITE, PAWN, 2, 3);
        board->boardMap[2][3] = whitePawn;

        QVector<Area> moves = board->getHorizontalStatus(5, 3, WHITE);

        QVERIFY(containsMove(moves, 4, 3));
        QVERIFY(containsMove(moves, 3, 3));
        QVERIFY(!containsMove(moves, 2, 3));
    }

    // Test can capture opponent
    void test_capture_opponent_horizontal() {
        ChessPiece* blackPawn = new ChessPiece(board, BLACK, PAWN, 4, 5);
        board->boardMap[4][5] = blackPawn;

        QVector<Area> moves = board->getHorizontalStatus(4, 2, WHITE);

        QVERIFY(containsMoveWithStatus(moves, 4, 3, ENABLE));
        QVERIFY(containsMoveWithStatus(moves, 4, 4, ENABLE));
        QVERIFY(containsMoveWithStatus(moves, 4, 5, ATTACK));
        QVERIFY(!containsMove(moves, 4, 6));
    }

    void test_capture_opponent_vertical() {
        ChessPiece* blackPawn = new ChessPiece(board, BLACK, PAWN, 2, 3);
        board->boardMap[2][3] = blackPawn;

        QVector<Area> moves = board->getHorizontalStatus(5, 3, WHITE);

        QVERIFY(containsMoveWithStatus(moves, 4, 3, ENABLE));
        QVERIFY(containsMoveWithStatus(moves, 3, 3, ENABLE));
        QVERIFY(containsMoveWithStatus(moves, 2, 3, ATTACK));
        QVERIFY(!containsMove(moves, 1, 3));
    }

    // Test from edge
    void test_from_edge_position() {
        QVector<Area> moves = board->getHorizontalStatus(0, 4, WHITE);

        // Should have 14 moves (7 horizontal + 7 vertical)
        QCOMPARE(moves.size(), 14);

        for (const Area& area : moves) {
            QVERIFY((area.row == 0) || (area.col == 4));
        }
    }

    // Test all moves within bounds
    void test_all_moves_within_bounds() {
        QVector<Area> moves = board->getHorizontalStatus(4, 4, WHITE);

        for (const Area& area : moves) {
            QVERIFY(area.row >= 0 && area.row < 8);
            QVERIFY(area.col >= 0 && area.col < 8);
        }
    }

    void test_from_center_has_14_moves() {
        QVector<Area> moves = board->getHorizontalStatus(4, 4, WHITE);
        QCOMPARE(moves.size(), 14);
    }
};

QTEST_MAIN(HorizontalMovementSteps)
#include "horizontal_movement_steps.moc"
