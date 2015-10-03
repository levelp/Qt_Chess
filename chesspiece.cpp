// Шахматная фигура - реализация
// -----------------------------
#include <QDebug>
#include "chesspiece.h"

int ChessPiece::count = 0;

// parent - шахматная доска
// side - цвет: чёрный / белый
// type - тип фигуры
// row, col - строка и столбец 0..7
ChessPiece::ChessPiece(ChessBoard* parent,
                       PlayerSide side, PieceType type, int row, int col) :
  QLabel((QWidget*)parent),  // Вызов QLabel с нужным parent
  id(++count), // Вычисляем id фигуры (для отладки)
  side(side), type(type), row(row), col(col) {
  // Получаем имя файла с картинкой
  QString s = playerSide2s(side).toLower(); // Сторона
  QString t = pieceType2s(type).toLower(); // Тип
  QString png = QString(":/data/%1-%2.png").arg(t).arg(s);
  setPixmap(QPixmap(png));

  qDebug() << "Фигура:" << id << s << t << png;
  //параметр который обновляется только для пешек, ладей и короля
  turn = -1;
  // Выравним фигуру по сетке

  alignToGrid();
  show();
  setAttribute(Qt::WA_DeleteOnClose);
}

// Выравнивание фигуры по сетке
void ChessPiece::alignToGrid() {
  move(col * CELL + 3, row * CELL + 3);
}

ChessPiece::~ChessPiece() {

}

