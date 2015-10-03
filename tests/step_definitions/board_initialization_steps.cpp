#include <QtTest/QtTest>
#include "../../chessboard.h"
#include "../../game.h"
#include "test_context.h"

class BoardInitializationSteps : public QObject
{
    Q_OBJECT

private:
    TestContext* context;
    ChessBoard* board;

private slots:
    void initTestCase() {
        context = TestContext::instance();
    }

    void init() {
        board = new ChessBoard(nullptr);
        context->board = board;
    }

    void cleanup() {
        if (context->board) {
            delete context->board;
            context->board = nullptr;
        }
    }

    // Test: Load standard starting position from resource
    void test_load_standard_starting_position() {
        board->loadRes(":/board.txt");

        // Count pieces
        int pieceCount = 0;
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (board->boardMap[row][col] != nullptr) {
                    pieceCount++;
                }
            }
        }

        QCOMPARE(pieceCount, 32);
    }

    // Test: Black back rank has correct pieces
    void test_black_back_rank_pieces() {
        board->loadRes(":/board.txt");

        QVERIFY(board->boardMap[0][0] != nullptr);
        QCOMPARE(board->boardMap[0][0]->getType(), ROOK);
        QCOMPARE(board->boardMap[0][0]->getSide(), BLACK);

        QCOMPARE(board->boardMap[0][1]->getType(), KNIGHT);
        QCOMPARE(board->boardMap[0][2]->getType(), BISHOP);
        QCOMPARE(board->boardMap[0][3]->getType(), QUEEN);
        QCOMPARE(board->boardMap[0][4]->getType(), KING);
        QCOMPARE(board->boardMap[0][5]->getType(), BISHOP);
        QCOMPARE(board->boardMap[0][6]->getType(), KNIGHT);
        QCOMPARE(board->boardMap[0][7]->getType(), ROOK);
    }

    // Test: White back rank has correct pieces
    void test_white_back_rank_pieces() {
        board->loadRes(":/board.txt");

        QCOMPARE(board->boardMap[7][0]->getType(), ROOK);
        QCOMPARE(board->boardMap[7][0]->getSide(), WHITE);
        QCOMPARE(board->boardMap[7][1]->getType(), KNIGHT);
        QCOMPARE(board->boardMap[7][2]->getType(), BISHOP);
        QCOMPARE(board->boardMap[7][3]->getType(), QUEEN);
        QCOMPARE(board->boardMap[7][4]->getType(), KING);
        QCOMPARE(board->boardMap[7][5]->getType(), BISHOP);
        QCOMPARE(board->boardMap[7][6]->getType(), KNIGHT);
        QCOMPARE(board->boardMap[7][7]->getType(), ROOK);
    }

    // Test: All white pawns in correct position
    void test_white_pawns_correct() {
        board->loadRes(":/board.txt");

        int pawnCount = 0;
        for (int col = 0; col < 8; col++) {
            QVERIFY(board->boardMap[6][col] != nullptr);
            QCOMPARE(board->boardMap[6][col]->getType(), PAWN);
            QCOMPARE(board->boardMap[6][col]->getSide(), WHITE);
            pawnCount++;
        }

        QCOMPARE(pawnCount, 8);
    }

    // Test: All black pawns in correct position
    void test_black_pawns_correct() {
        board->loadRes(":/board.txt");

        int pawnCount = 0;
        for (int col = 0; col < 8; col++) {
            QVERIFY(board->boardMap[1][col] != nullptr);
            QCOMPARE(board->boardMap[1][col]->getType(), PAWN);
            QCOMPARE(board->boardMap[1][col]->getSide(), BLACK);
            pawnCount++;
        }

        QCOMPARE(pawnCount, 8);
    }

    // Test: Middle rows are empty
    void test_middle_rows_empty() {
        board->loadRes(":/board.txt");

        for (int row = 2; row <= 5; row++) {
            for (int col = 0; col < 8; col++) {
                QVERIFY(board->boardMap[row][col] == nullptr);
            }
        }
    }

    // Test: Clear available moves resets highlighting
    void test_clear_available_moves() {
        board->loadRes(":/board.txt");

        // Set some moves
        board->avMoves[3][4] = ENABLE;
        board->avMoves[3][5] = ATTACK;

        // Clear
        board->clearAvMoves();

        // Verify all are DISABLE
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                QCOMPARE(board->avMoves[row][col], DISABLE);
            }
        }
    }
};

QTEST_MAIN(BoardInitializationSteps)
#include "board_initialization_steps.moc"
