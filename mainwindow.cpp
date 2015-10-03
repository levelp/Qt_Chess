#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Вывод подписей к доске
  for(int i = 0; i < 8; ++i)
    QLabel* label = new QLabel();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_exitAction_triggered() {
  // Закрываем игру
  close();
}
