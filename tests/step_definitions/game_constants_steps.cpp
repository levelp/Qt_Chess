#include <QtTest/QtTest>
#include "../../game.h"
#include "test_context.h"

class GameConstantsSteps : public QObject
{
    Q_OBJECT

private:
    TestContext* context;

private slots:
    void initTestCase() {
        context = TestContext::instance();
    }

    // Player Side Conversions
    void test_convert_white_player_side_to_string() {
        PlayerSide side = WHITE;
        QString result = playerSide2s(side);
        QCOMPARE(result, QString("WHITE"));
    }

    void test_convert_black_player_side_to_string() {
        PlayerSide side = BLACK;
        QString result = playerSide2s(side);
        QCOMPARE(result, QString("BLACK"));
    }

    // Piece Type Conversions
    void test_convert_pawn_to_string() {
        PieceType type = PAWN;
        QString result = pieceType2s(type);
        QCOMPARE(result, QString("PAWN"));
    }

    void test_convert_rook_to_string() {
        PieceType type = ROOK;
        QString result = pieceType2s(type);
        QCOMPARE(result, QString("ROOK"));
    }

    void test_convert_knight_to_string() {
        PieceType type = KNIGHT;
        QString result = pieceType2s(type);
        QCOMPARE(result, QString("KNIGHT"));
    }

    void test_convert_bishop_to_string() {
        PieceType type = BISHOP;
        QString result = pieceType2s(type);
        QCOMPARE(result, QString("BISHOP"));
    }

    void test_convert_queen_to_string() {
        PieceType type = QUEEN;
        QString result = pieceType2s(type);
        QCOMPARE(result, QString("QUEEN"));
    }

    void test_convert_king_to_string() {
        PieceType type = KING;
        QString result = pieceType2s(type);
        QCOMPARE(result, QString("KING"));
    }

    void test_convert_empty_to_string() {
        PieceType type = EMPTY;
        QString result = pieceType2s(type);
        QCOMPARE(result, QString("EMPTY"));
    }

    // Character Parsing
    void test_parse_lowercase_p_as_pawn() {
        QChar ch = 'p';
        PieceType result = char2pieceType(ch);
        QCOMPARE(result, PAWN);
    }

    void test_parse_uppercase_p_as_pawn() {
        QChar ch = 'P';
        PieceType result = char2pieceType(ch);
        QCOMPARE(result, PAWN);
    }

    void test_parse_lowercase_r_as_rook() {
        QChar ch = 'r';
        PieceType result = char2pieceType(ch);
        QCOMPARE(result, ROOK);
    }

    void test_parse_h_as_knight() {
        QChar ch = 'h';
        PieceType result = char2pieceType(ch);
        QCOMPARE(result, KNIGHT);
    }

    void test_parse_b_as_bishop() {
        QChar ch = 'b';
        PieceType result = char2pieceType(ch);
        QCOMPARE(result, BISHOP);
    }

    void test_parse_q_as_queen() {
        QChar ch = 'q';
        PieceType result = char2pieceType(ch);
        QCOMPARE(result, QUEEN);
    }

    void test_parse_k_as_king() {
        QChar ch = 'k';
        PieceType result = char2pieceType(ch);
        QCOMPARE(result, KING);
    }

    void test_parse_underscore_as_empty() {
        QChar ch = '_';
        PieceType result = char2pieceType(ch);
        QCOMPARE(result, EMPTY);
    }

    void test_parse_invalid_character_throws_exception() {
        QChar ch = 'x';
        bool exceptionThrown = false;
        try {
            char2pieceType(ch);
        } catch (...) {
            exceptionThrown = true;
        }
        QVERIFY(exceptionThrown);
    }
};

QTEST_MAIN(GameConstantsSteps)
#include "game_constants_steps.moc"
