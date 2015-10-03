#include <QLabel>
#include <QPainter>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessboard.h"

const int LABEL_HEIGHT = 20;
const int LABEL_WIDTH = 15;

// Подписи к шахматной доске
void MainWindow::boardLabel(char c, int x, int y, int width) {
  QLabel* l = new QLabel(QString("%1").arg(c), ui->chessBoard);
  // Выравнивание текста по-центру
  l->setAlignment(Qt::AlignCenter);
  // Перемещаем label в заданную точку и задаём размер
  l->setGeometry(x, y, width, LABEL_HEIGHT);
  // Можем ещё поставить шрифт побольше :)
  QFont font = l->font();
  font.setPointSize(12);
  l->setFont(font);
}

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Настраиваем размер доски
  ChessBoard* b = ui->board;
  int boardSize = 8 * CELL + 2 * (b->lineWidth() + 2);
  b->setGeometry(QRect(20, 20, boardSize, boardSize));
  b->setMinimumSize(QSize(boardSize, boardSize));
  b->setBaseSize(QSize(boardSize, boardSize));

  QRect g = b->geometry();

  // Вывод подписей к доске
  for(int i = 0; i < 8; ++i) {
    char L = 'a' + i; // Буква у края доски
    int x = i * CELL + g.left();
    boardLabel(L, x, g.top() - LABEL_HEIGHT, CELL);
    boardLabel(L, x, g.top() + g.height(), CELL);

    char D = '8' - i; // Цифра у края доски
    int y = i * CELL + g.top() + (CELL - LABEL_HEIGHT) / 2;
    boardLabel(D, g.left() - LABEL_WIDTH, y, LABEL_WIDTH);
    boardLabel(D, g.left() + g.width(), y, LABEL_WIDTH);
  }

  // Загрузка начальной конфигурации доски
  ui->board->loadRes(":/data/board.txt");
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_exitAction_triggered() {
  // Закрываем игру
  close();
}

// Отрисовка поля игры
void MainWindow::paintEvent(QPaintEvent*) {
  QPainter p(this);
  qDebug() << "paint";

  // Вычисляем координаты для рисования на форме
  QRect cw = ui->centralWidget->geometry();
  QRect cb = ui->chessBoard->geometry();
  QRect b = ui->board->geometry();
  const int x = cw.left() + cb.left() + b.left() + ui->board->lineWidth() + 1;
  const int y = cw.top() + cb.top() + b.top() + ui->board->lineWidth() + 1;

  // Цвета клеток доски
  QBrush disabledColor[] = { QBrush(Qt::white), QBrush(Qt::gray) } ;
  QBrush enabledColor[] = { QBrush(Qt::green), QBrush(Qt::darkGray) } ;

  // Рисуем клетки доски
  for(int i = 0; i < 8; ++i)
    for(int j = 0; j < 8; ++j) {
      switch(ui->board->avMoves[i][j]) {
        case ENABLE:
          p.setBrush(enabledColor[(i + j) % 2]);
          break;

        case DISABLE:
          p.setBrush(disabledColor[(i + j) % 2]);
          break;
      }

      p.drawRect(x + j * CELL, y + i * CELL, CELL, CELL);
    }
}
