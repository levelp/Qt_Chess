// Шахматная доска - реализация
// ----------------------------
#include <QtGui>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include "chessboard.h"
#include "ui_chessboard.h"

ChessBoard::ChessBoard(QWidget* parent) :
  QFrame(parent),
  ui(new Ui::ChessBoard) {
  ui->setupUi(this);
  setAcceptDrops(true);
}

ChessBoard::~ChessBoard() {
  delete ui;
}

const char* mimeFormat = "application/x-chesspiece";

void ChessBoard::dragEnterEvent(QDragEnterEvent* event) {
  if (event->mimeData()->hasFormat(mimeFormat)) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else
      event->acceptProposedAction();
  } else
    event->ignore();
}

void ChessBoard::dragMoveEvent(QDragMoveEvent* event) {
  if (event->mimeData()->hasFormat(mimeFormat)) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else
      event->acceptProposedAction();
  } else
    event->ignore();
}

void ChessBoard::dropEvent(QDropEvent* event) {
  if (event->mimeData()->hasFormat(mimeFormat)) {
    qDebug() << "drop" << cur->id;

    QByteArray itemData = event->mimeData()->data(mimeFormat);
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap; // Картинка
    QPoint offset; // Смещение
    dataStream >> pixmap >> offset;

    cur->setPixmap(pixmap);

    // Перемещаем фигуру
    QPoint p = event->pos() - offset;
    cur->row = (p.y() + CELL / 2) / CELL;
    cur->col = (p.x() + CELL / 2) / CELL;
    cur->alignToGrid();
    cur->show();
    cur->setAttribute(Qt::WA_DeleteOnClose);

    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else
      event->acceptProposedAction();
  } else
    event->ignore();
}

void ChessBoard::mousePressEvent(QMouseEvent* event) {
  ChessPiece* piece = static_cast<ChessPiece*>(childAt(event->pos()));

  if (!piece)
    return;

  qDebug() << "Move" << piece->id;
  cur = piece;
  QPixmap pixmap = *piece->pixmap();

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << pixmap << QPoint(event->pos() - piece->pos());

  QMimeData* mimeData = new QMimeData;
  mimeData->setData("application/x-dnditemdata", itemData);

  QDrag* drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(event->pos() - piece->pos());

  QPixmap tempPixmap = pixmap;
  QPainter painter;
  painter.begin(&tempPixmap);
  painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
  painter.end();

  piece->setPixmap(tempPixmap);

  if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
    //piece->close();
  } else {
    piece->show();
    piece->setPixmap(pixmap);
  }
}

// Загрузка доски из файла
void ChessBoard::loadFile(QString fileName) {
  QFile f(fileName);

  if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::critical(this, "Не могу прочитать файл",
                          QString("\"%1\" ошибка \"%2\"")
                          .arg(f.fileName()).arg(f.errorString()));

    qDebug() << "Не могу открыть: " << f.fileName() <<
             " ошибка " << f.errorString() << endl;
    return;
  }

  QTextStream in(&f);

  for(int row = 0; row < 8; ++row) {
    // Читаем очередную строчку из файла
    QString line = in.readLine();
    qDebug() << "Прочитали:" << line;

    for(int col = 0; col < 8; ++col) {
      QChar c = line.at(col);

      if(c == '_') continue;

      PlayerSide side = (c.isLower()) ? BLACK : WHITE;
      PieceType type = char2pieceType(c);

      new ChessPiece(this, side, type, row, col);
    }
  }
}

// Загрузка доски из ресурса
void ChessBoard::loadRes(QString fileName) {
  qDebug() << "Загрузка ресурса " << fileName;
  QResource res(fileName);
  loadFile(res.absoluteFilePath());
}

