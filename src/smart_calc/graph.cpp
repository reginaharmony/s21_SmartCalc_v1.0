#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget* parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  //  ui->month_choose_label->setVisible(false);
  //  ui->month_choose->setVisible(false);
}

Graph::~Graph() { delete ui; }
void Graph::graphics(char* pstr) {
  ui->expression->setText(pstr);
  double res = 0;
  double* px = NULL;
  px = &X;
  y_start = ui->y_min->text().toDouble();
  y_end = ui->y_max->text().toDouble();
  x_start = ui->x_min->text().toDouble();
  x_end = ui->x_max->text().toDouble();
  if (x_start < -LIMIT) x_start = -LIMIT;
  if (x_end > LIMIT) x_end = LIMIT;

  step = (x_end - x_start) / 10000;
  ui->widget->xAxis->setRange(x_start, x_end);
  ui->widget->yAxis->setRange(y_start, y_end);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");

  x.clear();
  y.clear();

  ui->widget->clearPlottables();
  ui->widget->clearGraphs();

  for (X = x_start; X <= x_end && step != 0; X += step) {
    SmartCalc(pstr, &res, px);
    x.push_back(X);
    y.push_back(res);
  }

  ui->widget->addGraph();
  QPen pen;
  pen.setWidth(1);
  pen.setColor(QColor(0, 0, 139));
  ui->widget->graph(0)->setPen(pen);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setAdaptiveSampling(false);
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void Graph::on_build_graphics_clicked() {
  QString str = ui->expression->text();
  QByteArray byte_string = str.toLocal8Bit();
  char* equation = byte_string.data();
  graphics(equation);
}