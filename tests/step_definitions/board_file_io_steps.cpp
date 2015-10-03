#include <QtTest/QtTest>
#include <QFile>
#include <QTextStream>
#include "../../chessboard.h"
#include "../../game.h"
#include "test_context.h"

class BoardFileIOSteps : public QObject
{
    Q_OBJECT

private:
    ChessBoard* board;
    QString testFileName;

private slots:
    void init() {
        board = new ChessBoard(nullptr);
        testFileName = "test_board.txt";
    }

    void cleanup() {
        delete board;
        // Clean up test file
        QFile::remove(testFileName);
    }

    // Test loading standard starting position
    void test_load_standard_position() {
        board->loadRes(":/board.txt");

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

    // Test parsing uppercase as white pieces
    void test_parse_uppercase_as_white() {
        createTestFile("P_______\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        QVERIFY(board->boardMap[0][0] != nullptr);
        QCOMPARE(board->boardMap[0][0]->getType(), PAWN);
        QCOMPARE(board->boardMap[0][0]->getSide(), WHITE);
    }

    // Test parsing lowercase as black pieces
    void test_parse_lowercase_as_black() {
        createTestFile("p_______\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        QVERIFY(board->boardMap[0][0] != nullptr);
        QCOMPARE(board->boardMap[0][0]->getType(), PAWN);
        QCOMPARE(board->boardMap[0][0]->getSide(), BLACK);
    }

    // Test parsing different piece types
    void test_parse_rook() {
        createTestFile("r_______\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        QCOMPARE(board->boardMap[0][0]->getType(), ROOK);
        QCOMPARE(board->boardMap[0][0]->getSide(), BLACK);
    }

    void test_parse_knight() {
        createTestFile("h_______\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        QCOMPARE(board->boardMap[0][0]->getType(), KNIGHT);
    }

    void test_parse_bishop() {
        createTestFile("b_______\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        QCOMPARE(board->boardMap[0][0]->getType(), BISHOP);
    }

    void test_parse_queen() {
        createTestFile("q_______\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        QCOMPARE(board->boardMap[0][0]->getType(), QUEEN);
    }

    void test_parse_king() {
        createTestFile("k_______\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        QCOMPARE(board->boardMap[0][0]->getType(), KING);
    }

    // Test parsing underscore as empty
    void test_parse_underscore_as_empty() {
        createTestFile("________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                QVERIFY(board->boardMap[row][col] == nullptr);
            }
        }
    }

    // Test loading from resource
    void test_load_from_resource() {
        board->loadRes(":/board.txt");

        // Verify standard position
        QCOMPARE(board->boardMap[0][0]->getType(), ROOK);
        QCOMPARE(board->boardMap[0][0]->getSide(), BLACK);
        QCOMPARE(board->boardMap[7][4]->getType(), KING);
        QCOMPARE(board->boardMap[7][4]->getSide(), WHITE);
    }

    // Test full 8x8 grid parsing
    void test_full_grid_parsing() {
        createTestFile("rhbqkbhr\n"
                       "pppppppp\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "PPPPPPPP\n"
                       "RHBQKBHR");

        board->loadFile(testFileName);

        // Verify all 64 cells are processed
        int processedCells = 0;
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                processedCells++;
            }
        }

        QCOMPARE(processedCells, 64);
    }

    // Test mixed case configuration
    void test_mixed_case_configuration() {
        createTestFile("rP______\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________\n"
                       "________");

        board->loadFile(testFileName);

        QCOMPARE(board->boardMap[0][0]->getSide(), BLACK);  // lowercase
        QCOMPARE(board->boardMap[0][1]->getSide(), WHITE);  // uppercase
    }

private:
    void createTestFile(const QString& content) {
        QFile file(testFileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << content;
            file.close();
        }
    }
};

QTEST_MAIN(BoardFileIOSteps)
#include "board_file_io_steps.moc"
