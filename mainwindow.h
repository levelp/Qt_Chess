#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

  // Игра
  Game game;

 private slots:
  void on_exitAction_triggered();

 private:
  Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
