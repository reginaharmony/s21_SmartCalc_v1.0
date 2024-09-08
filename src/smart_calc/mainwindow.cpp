#include "mainwindow.h"

#include "ui_mainwindow.h"

UltraCalc::UltraCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::UltraCalc) {
  ui->setupUi(this);

  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->btn_plus, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->btn_min, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->btn_mul, SIGNAL(clicked()), this, SLOT(mul_div()));
  connect(ui->btn_div, SIGNAL(clicked()), this, SLOT(mul_div()));

  connect(ui->btn_sin, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->btn_cos, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->btn_tan, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->btn_atan, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->btn_acos, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->btn_asin, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->btn_log, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->btn_ln, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->btn_sqrt, SIGNAL(clicked()), this, SLOT(brackets()));

  connect(ui->btn_mod, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->btn_pow, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->btn_x, SIGNAL(clicked()), this, SLOT(num_buttons()));

  connect(ui->btn_lb, SIGNAL(clicked()), this, SLOT(num_buttons()));
  connect(ui->btn_rb, SIGNAL(clicked()), this, SLOT(num_buttons()));
}

UltraCalc::~UltraCalc() {
  delete graph;
  delete bonusWin;
  delete ui;
}

void UltraCalc::num_buttons() {
  QPushButton *button = (QPushButton *)sender();
  QString input = ui->result->text();
  if (input == "0") {
    ui->result->clear();
  }
  QString newlabel = ui->result->text() + button->text();
  ui->result->setText(newlabel);
}

void UltraCalc::brackets() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonText;
  if (button) {
    buttonText = button->text();
    if (buttonText == "√") buttonText = "sqrt";
  }
  QString input = ui->result->text();
  if (input == "0") {
    ui->result->clear();
  }
  QString newlabel = ui->result->text() + buttonText + "(";
  ui->result->setText(newlabel);
}

void UltraCalc::mul_div() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonText;
  if (button) {
    buttonText = button->text();
    if (buttonText == "÷") {
      buttonText = "/";
    } else if (buttonText == "×") {
      buttonText = "*";
    }
  }
  QString input = ui->result->text();
  if (input == "0") {
    ui->result->clear();
  }
  QString newlabel = ui->result->text() + buttonText;
  ui->result->setText(newlabel);
}
void UltraCalc::on_btn_dot_clicked() {
  if (!(ui->result->text().endsWith('.')))
    ui->result->setText(ui->result->text() + ".");
}

void UltraCalc::on_btn_ac_clicked() { ui->result->setText("0"); }

void UltraCalc::on_btn_clear_clicked() {
  QString currentText = ui->result->text();
  if (!currentText.isEmpty() && currentText != "0") {
    currentText = currentText.left(currentText.length() - 1);
    ui->result->setText(currentText);
  } else {
    ui->result->setText("0");
  }
}

void UltraCalc::on_btn_res_clicked() {
  QString str = ui->result->text();
  QByteArray byte_string = str.toLocal8Bit();
  char *equation = byte_string.data();
  double res = 0;
  double entered_x = 0;
  double *X = &entered_x;
  if (str.contains('x')) {
    bool ok;
    entered_x = QInputDialog::getDouble(
        this, "Enter value", "Enter value of X:", 0, -100000, 100000, 7, &ok);
    if (!ok) return;
  } else
    X = NULL;
  if (SmartCalc(equation, &res, X)) {
    QString numberResult = QString::number(res, 'g', 15);
    ui->result->setText(numberResult);
  } else {
    ui->result->setText("ERROR");
  }
}

void UltraCalc::on_btn_plot_clicked() {
  QString str = ui->result->text();
  QByteArray byte_string = str.toLocal8Bit();
  char *equation = byte_string.data();
  if (isValid(equation)) {
    graph = new Graph;
    graph->show();
    graph->graphics(equation);
  } else {
    ui->result->setText("ERROR");
  }
}

void UltraCalc::on_btn_credit_clicked() {
  class bonusWin window;
  window.setModal(true);
  window.exec();
}
