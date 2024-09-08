#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  UltraCalc w;
  w.setWindowTitle("ULTRA CALC");
  w.show();
  return a.exec();
}
