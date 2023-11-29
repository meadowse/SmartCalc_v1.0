#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QtMath>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
#include "graph.h"
#ifdef __cplusplus
}
#endif

int isUnary(int index);
int isBinary(int index);
int isDigit(int index);
int isDigit2(int index);

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double xBegin, xEnd, h;
  int N;
  int count;
  double X = 0.0;
  double Y = 0.0;
  QVector<double> x, y;

 private slots:
  void num();
  void on_pushButton_all_del_clicked();
  void on_pushButton_del_clicked();
  void on_pushButton_dot_clicked();
  void function();
  void on_pushButton_x_clicked();
  void on_pushButton_close_clicked();
  void on_pushButton_open_clicked();
  void un_function();
  void bi_function();
  void on_pushButton_equal_clicked();
};
#endif  // MAINWINDOW_H
