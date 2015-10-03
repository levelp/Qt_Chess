#include <QtTest/QtTest>
#include "../../chessboard.h"
#include "../../game.h"
#include "test_context.h"

class CellStatusSteps : public QObject
{
    Q_OBJECT

private:
    ChessBoard* board;

private slots:
    void init() {
        board = new ChessBoard(nullptr);
        board->loadRes(":/board.txt");
    }

    void cleanup() {
        delete board;
    }

    // Test: Empty cell returns ENABLE status
    void test_empty_cell_enable() {
        status result = board->getPoleStatus(4, 4, WHITE);
        QCOMPARE(result, ENABLE);
    }

    // Test: Cell with own piece returns DISABLE status
    void test_own_piece_disable() {
        status result = board->getPoleStatus(6, 0, WHITE);
        QCOMPARE(result, DISABLE);
    }

    // Test: Cell with opponent piece returns ATTACK status
    void test_opponent_piece_attack() {
        status result = board->getPoleStatus(1, 0, WHITE);
        QCOMPARE(result, ATTACK);
    }

    // Test: Out-of-bounds row returns DISABLE
    void test_out_of_bounds_row() {
        status result = board->getPoleStatus(8, 4, WHITE);
        QCOMPARE(result, DISABLE);
    }

    // Test: Out-of-bounds column returns DISABLE
    void test_out_of_bounds_column() {
        status result = board->getPoleStatus(4, 8, WHITE);
        QCOMPARE(result, DISABLE);
    }

    // Test: Negative row returns DISABLE
    void test_negative_row() {
        status result = board->getPoleStatus(-1, 4, WHITE);
        QCOMPARE(result, DISABLE);
    }

    // Test: Negative column returns DISABLE
    void test_negative_column() {
        status result = board->getPoleStatus(4, -1, WHITE);
        QCOMPARE(result, DISABLE);
    }

    // Test: Cell at boundary with own piece
    void test_boundary_own_piece() {
        status result = board->getPoleStatus(7, 7, WHITE);
        QCOMPARE(result, DISABLE);
    }

    // Test: Cell at boundary with opponent piece
    void test_boundary_opponent_piece() {
        status result = board->getPoleStatus(0, 0, WHITE);
        QCOMPARE(result, ATTACK);
    }

    // Test: BLACK player checking white piece cell
    void test_black_player_white_piece() {
        status result = board->getPoleStatus(7, 0, BLACK);
        QCOMPARE(result, ATTACK);
    }

    // Test: BLACK player checking black piece cell
    void test_black_player_black_piece() {
        status result = board->getPoleStatus(0, 0, BLACK);
        QCOMPARE(result, DISABLE);
    }
};

QTEST_MAIN(CellStatusSteps)
#include "cell_status_steps.moc"
