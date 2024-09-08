#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QInputDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QString>

#include "bonuswin.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class UltraCalc;
}
QT_END_NAMESPACE

class UltraCalc : public QMainWindow {
  Q_OBJECT

 public:
  UltraCalc(QWidget *parent = nullptr);
  ~UltraCalc();

 private:
  Ui::UltraCalc *ui;
  Graph *graph;
  bonusWin *bonusWin;

 private slots:
  void on_btn_res_clicked();
  void num_buttons();
  void brackets();
  void mul_div();
  void on_btn_dot_clicked();
  void on_btn_clear_clicked();
  void on_btn_ac_clicked();
  void on_btn_plot_clicked();
  void on_btn_credit_clicked();
};
#endif  // MAINWINDOW_H
