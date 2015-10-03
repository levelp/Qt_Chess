#ifndef TEST_CONTEXT_H
#define TEST_CONTEXT_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include "../../chessboard.h"
#include "../../chesspiece.h"

/**
 * TestContext - Shared context for BDD tests
 * Stores state between test steps
 */
class TestContext : public QObject
{
    Q_OBJECT

public:
    static TestContext* instance() {
        static TestContext* inst = new TestContext();
        return inst;
    }

    // Shared test data
    ChessBoard* board;
    ChessPiece* currentPiece;
    QVector<Area> currentMoves;
    QMap<QString, QVariant> data;

    void reset() {
        if (board) {
            delete board;
            board = nullptr;
        }
        currentPiece = nullptr;
        currentMoves.clear();
        data.clear();
    }

    void set(const QString& key, const QVariant& value) {
        data[key] = value;
    }

    QVariant get(const QString& key) const {
        return data.value(key);
    }

    bool has(const QString& key) const {
        return data.contains(key);
    }

private:
    TestContext() : board(nullptr), currentPiece(nullptr) {}
    ~TestContext() {
        reset();
    }
};

#endif // TEST_CONTEXT_H
