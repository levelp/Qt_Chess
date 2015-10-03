#include <QtTest/QtTest>
#include <QApplication>
#include "../../chessboard.h"
#include "../../chesspiece.h"
#include "../../game.h"
#include "test_context.h"

class PieceManagementSteps : public QObject
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
        // Create a new board for each test
        board = new ChessBoard(nullptr);
        context->board = board;
    }

    void cleanup() {
        // Cleanup after each test
        if (context->board) {
            delete context->board;
            context->board = nullptr;
        }
    }

    // Test: Create white pawn at starting position
    void test_create_white_pawn_at_starting_position() {
        ChessPiece* piece = new ChessPiece(board, WHITE, PAWN, 6, 0);

        QCOMPARE(piece->getSide(), WHITE);
        QCOMPARE(piece->getType(), PAWN);
        QCOMPARE(piece->getRow(), 6);
        QCOMPARE(piece->getCol(), 0);
    }

    // Test: Create black rook at starting position
    void test_create_black_rook_at_starting_position() {
        ChessPiece* piece = new ChessPiece(board, BLACK, ROOK, 0, 0);

        QCOMPARE(piece->getSide(), BLACK);
        QCOMPARE(piece->getType(), ROOK);
        QCOMPARE(piece->getRow(), 0);
        QCOMPARE(piece->getCol(), 0);
    }

    // Test: Update piece position
    void test_update_piece_position() {
        ChessPiece* piece = new ChessPiece(board, WHITE, KNIGHT, 7, 1);

        piece->setRow(5);
        piece->setCol(2);

        QCOMPARE(piece->getRow(), 5);
        QCOMPARE(piece->getCol(), 2);
    }

    // Test: Track piece turn state
    void test_track_piece_turn_state() {
        ChessPiece* piece = new ChessPiece(board, WHITE, PAWN, 6, 4);

        piece->setTurn(1);

        QCOMPARE(piece->getTurn(), 1);
    }

    // Test: Assign unique piece IDs
    void test_assign_unique_piece_ids() {
        QSet<int> ids;

        for (int i = 0; i < 32; i++) {
            int row = i / 8;
            int col = i % 8;
            ChessPiece* piece = new ChessPiece(board, WHITE, PAWN, row, col);
            ids.insert(piece->getId());
        }

        // All IDs should be unique
        QCOMPARE(ids.size(), 32);
    }

    // Test: Align piece to grid coordinates
    void test_align_piece_to_grid_coordinates() {
        ChessPiece* piece = new ChessPiece(board, WHITE, QUEEN, 3, 4);
        piece->alignToGrid();

        // Row 3, Col 4 -> X = 4 * 50 = 200, Y = 3 * 50 = 150
        QCOMPARE(piece->x(), 200);
        QCOMPARE(piece->y(), 150);
    }

    // Test: Get piece type
    void test_get_piece_type() {
        ChessPiece* piece = new ChessPiece(board, BLACK, BISHOP, 0, 2);

        PieceType type = piece->getType();

        QCOMPARE(type, BISHOP);
    }

    // Test: Get piece side
    void test_get_piece_side() {
        ChessPiece* piece = new ChessPiece(board, WHITE, KING, 7, 4);

        PlayerSide side = piece->getSide();

        QCOMPARE(side, WHITE);
    }
};

QTEST_MAIN(PieceManagementSteps)
#include "piece_management_steps.moc"
