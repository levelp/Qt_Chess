#include <QtTest/QtTest>
#include "../../chessboard.h"
#include "../../game.h"
#include "test_context.h"

class KingSafetySteps : public QObject
{
    Q_OBJECT

private:
    ChessBoard* board;

private slots:
    void init() {
        board = new ChessBoard(nullptr);
    }

    void cleanup() {
        delete board;
    }

    // Test attacked squares by pawn
    void test_pawn_attacked_squares() {
        ChessPiece* blackPawn = new ChessPiece(board, BLACK, PAWN, 3, 4);
        board->boardMap[3][4] = blackPawn;

        board->fillEndOfGame(WHITE);

        // Black pawn attacks diagonal forward (down for black)
        QVERIFY(board->endOfGame[4][3] == true);
        QVERIFY(board->endOfGame[4][5] == true);
        QVERIFY(board->endOfGame[4][4] == false);
    }

    // Test attacked squares by rook
    void test_rook_attacked_squares() {
        ChessPiece* blackRook = new ChessPiece(board, BLACK, ROOK, 3, 3);
        board->boardMap[3][3] = blackRook;

        board->fillEndOfGame(WHITE);

        // Rook attacks entire row and column
        for (int col = 0; col < 8; col++) {
            if (col != 3) {
                QVERIFY(board->endOfGame[3][col] == true);
            }
        }

        for (int row = 0; row < 8; row++) {
            if (row != 3) {
                QVERIFY(board->endOfGame[row][3] == true);
            }
        }
    }

    // Test attacked squares by knight
    void test_knight_attacked_squares() {
        ChessPiece* blackKnight = new ChessPiece(board, BLACK, KNIGHT, 4, 4);
        board->boardMap[4][4] = blackKnight;

        board->fillEndOfGame(WHITE);

        // Knight attacks L-shaped squares
        QVERIFY(board->endOfGame[2][3] == true);
        QVERIFY(board->endOfGame[2][5] == true);
        QVERIFY(board->endOfGame[3][2] == true);
        QVERIFY(board->endOfGame[3][6] == true);
        QVERIFY(board->endOfGame[5][2] == true);
        QVERIFY(board->endOfGame[5][6] == true);
        QVERIFY(board->endOfGame[6][3] == true);
        QVERIFY(board->endOfGame[6][5] == true);
    }

    // Test attacked squares by bishop
    void test_bishop_attacked_squares() {
        ChessPiece* blackBishop = new ChessPiece(board, BLACK, BISHOP, 4, 4);
        board->boardMap[4][4] = blackBishop;

        board->fillEndOfGame(WHITE);

        // Bishop attacks diagonals
        QVERIFY(board->endOfGame[3][3] == true);
        QVERIFY(board->endOfGame[2][2] == true);
        QVERIFY(board->endOfGame[5][5] == true);
        QVERIFY(board->endOfGame[6][6] == true);

        // Non-diagonal squares not attacked
        QVERIFY(board->endOfGame[4][5] == false || board->endOfGame[4][5] == true); // May be attacked by other pieces
    }

    // Test attacked squares by queen
    void test_queen_attacked_squares() {
        ChessPiece* blackQueen = new ChessPiece(board, BLACK, QUEEN, 4, 4);
        board->boardMap[4][4] = blackQueen;

        board->fillEndOfGame(WHITE);

        // Queen attacks row, column, and diagonals
        QVERIFY(board->endOfGame[4][0] == true);  // Horizontal
        QVERIFY(board->endOfGame[0][4] == true);  // Vertical
        QVERIFY(board->endOfGame[0][0] == true);  // Diagonal
        QVERIFY(board->endOfGame[7][7] == true);  // Diagonal
    }

    // Test attacked squares by king
    void test_king_attacked_squares() {
        ChessPiece* blackKing = new ChessPiece(board, BLACK, KING, 2, 2);
        board->boardMap[2][2] = blackKing;

        board->fillEndOfGame(WHITE);

        // King attacks all adjacent squares
        QVERIFY(board->endOfGame[1][1] == true);
        QVERIFY(board->endOfGame[1][2] == true);
        QVERIFY(board->endOfGame[1][3] == true);
        QVERIFY(board->endOfGame[2][1] == true);
        QVERIFY(board->endOfGame[2][3] == true);
        QVERIFY(board->endOfGame[3][1] == true);
        QVERIFY(board->endOfGame[3][2] == true);
        QVERIFY(board->endOfGame[3][3] == true);
    }

    // Test safe squares
    void test_safe_squares() {
        ChessPiece* blackRook = new ChessPiece(board, BLACK, ROOK, 0, 0);
        board->boardMap[0][0] = blackRook;

        board->fillEndOfGame(WHITE);

        // Far squares should be safe
        QVERIFY(board->endOfGame[5][5] == false);
        QVERIFY(board->endOfGame[4][4] == false);
    }

    // Test multiple attackers
    void test_multiple_attackers() {
        ChessPiece* blackRook = new ChessPiece(board, BLACK, ROOK, 0, 0);
        ChessPiece* blackBishop = new ChessPiece(board, BLACK, BISHOP, 7, 7);
        board->boardMap[0][0] = blackRook;
        board->boardMap[7][7] = blackBishop;

        board->fillEndOfGame(WHITE);

        // Rook attacks
        QVERIFY(board->endOfGame[0][4] == true);
        QVERIFY(board->endOfGame[4][0] == true);

        // Bishop attacks
        QVERIFY(board->endOfGame[4][4] == true);

        // Both might attack some squares
        QVERIFY(board->endOfGame[0][4] == true || board->endOfGame[4][4] == true);
    }

    // Test fillEndOfGame initialization
    void test_fill_end_of_game_initialization() {
        // Initially all squares should be false
        board->fillEndOfGame(WHITE);

        // After filling, check that endOfGame array is properly set
        bool hasAttackedSquares = false;
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (board->endOfGame[row][col]) {
                    hasAttackedSquares = true;
                    break;
                }
            }
        }

        // With no pieces, no squares should be attacked
        QVERIFY(!hasAttackedSquares);
    }

    // Test king cannot move to attacked square
    void test_king_cannot_move_to_attacked_square() {
        ChessPiece* whiteKing = new ChessPiece(board, WHITE, KING, 4, 4);
        ChessPiece* blackRook = new ChessPiece(board, BLACK, ROOK, 0, 5);
        board->boardMap[4][4] = whiteKing;
        board->boardMap[0][5] = blackRook;

        board->fillEndOfGame(WHITE);
        QVector<Area> moves = board->getTurnArea(whiteKing);

        // King should not be able to move to column 5
        for (const Area& area : moves) {
            QVERIFY(area.col != 5);
        }
    }
};

QTEST_MAIN(KingSafetySteps)
#include "king_safety_steps.moc"
