#include "bonuswin.h"

#include "ui_bonuswin.h"

extern "C" {
#include "credit_deposit.h"
}

#include "QtWidgets/qtablewidget.h"

bonusWin::bonusWin(QWidget *parent) : QDialog(parent), ui(new Ui::bonusWin) {
  ui->setupUi(this);
}

bonusWin::~bonusWin() { delete ui; }

// ===================================================== CREDIT

void bonusWin::on_pushButton_result_clicked() {
  cr_resetInputData();
  if (ui->radioButton_annuitent->isChecked()) {  // определение типа
    cr_annuitentCalculation();
  }
  if (ui->radioButton_different->isChecked()) {
    cr_differentCalculation();
  }
}

void bonusWin::cr_resetInputData() {  // для обновления значений всех
  // переменных
  cr_creditTtl = ui->spinBox_creditTtl->text().toDouble();
  cr_monthTerm = ui->spinBox_monthTerm->text().toInt();
  cr_interestRate =
      (ui->doubleSpinBox_interestRate->text().toDouble()) / 100 / 12;
  cr_interestTtl = 0;
  cr_totalPay = 0;
  cr_statePay = 0;
}

void bonusWin::cr_annuitentCalculation() {
  ui->tableWidget_monthlyPayment->setRowCount(
      cr_monthTerm);  // задаём параметры таблицы
  ui->tableWidget_monthlyPayment->setColumnCount(1);
  ui->tableWidget_monthlyPayment->setHorizontalHeaderLabels(QStringList()
                                                            << "Amount");
  for (int i = 0; i < cr_monthTerm; i++) {  // расчёт ежемесячных выплат
    QTableWidgetItem *tbl = new QTableWidgetItem(QString::number(
        creditAnnuitentCalculation(cr_creditTtl, cr_monthTerm, cr_interestRate,
                                   &cr_interestTtl, &cr_totalPay),
        'f', 3));
    ui->tableWidget_monthlyPayment->setItem(0, i, tbl);
  }
  ui->lineEdit_overpayment->setText(QString::number(cr_interestTtl, 'f', 3));
  ui->lineEdit_totalPay->setText(QString::number(cr_totalPay, 'f', 3));
}

void bonusWin::cr_differentCalculation() {
  cr_statePay = cr_monthTerm - 1;
  ui->tableWidget_monthlyPayment->setRowCount(
      cr_monthTerm);  // задаём параметры таблицы
  ui->tableWidget_monthlyPayment->setColumnCount(1);
  ui->tableWidget_monthlyPayment->setHorizontalHeaderLabels(QStringList()
                                                            << "Amount");
  for (int i = cr_monthTerm - 1; i >= 0; i--) {  // расчёт ежемесячных выплат

    QTableWidgetItem *tbl = new QTableWidgetItem(QString::number(
        creditDifferentCalculation(cr_creditTtl, cr_monthTerm, &cr_statePay,
                                   cr_interestRate, &cr_interestTtl,
                                   &cr_totalPay),
        'f', 3));
    ui->tableWidget_monthlyPayment->setItem(0, i, tbl);
  }
  if (cr_monthTerm != 0) cr_interestTtl = cr_interestTtl - cr_creditTtl;

  ui->lineEdit_overpayment->setText(QString::number(cr_interestTtl, 'f', 3));
  ui->lineEdit_totalPay->setText(QString::number(cr_totalPay, 'f', 3));
}

// ===================================================== DEPOSIT

void bonusWin::on_pushButton_clicked() {
  dp_resetInputData();
  if (ui->checkBox_capital->isChecked())  // капитализация
    dp_capital = 1;
  else
    dp_capital = 0;
  ui->lineEdit_sumDepositEnd->setText(QString::number(depositCalc(
      dp_sumDeposit, dp_monthTerm, dp_interestRate, dp_nalogRate, dp_period,
      dp_capital, dp_refillCount, dp_refill, dp_withdrawalCount, dp_withdrawal,
      &dp_sumPercent, &dp_sumNalog)));
  ui->lineEdit_sumPercent->setText(QString::number(dp_sumPercent));
  ui->lineEdit_sumNalog->setText(QString::number(dp_sumNalog));
}

void bonusWin::dp_resetInputData() {  // для обновления значений всех
                                      // переменных
  dp_sumDeposit = ui->spinBox_sumDeposit->text().toDouble();
  dp_monthTerm = ui->spinBox_monthTerm_2->value();
  dp_interestRate = ui->doubleSpinBox_interestRate_2->value() / 100;
  dp_nalogRate = ui->doubleSpinBox_nalogRate->value() / 100;

  if (ui->comboBox_period->currentIndex() == 0)  // периодичность выплат
    dp_period = 1;
  else if (ui->comboBox_period->currentIndex() == 1)
    dp_period = 3;
  else if (ui->comboBox_period->currentIndex() == 2) {
    dp_period = 0;
  }

  if (ui->comboBox_refill->currentIndex() == 0)  // периодичность пополнений
    dp_refillCount = -1;
  else if (ui->comboBox_refill->currentIndex() == 1)
    dp_refillCount = 1;
  else if (ui->comboBox_refill->currentIndex() == 2)
    dp_refillCount = 3;
  else if (ui->comboBox_refill->currentIndex() == 3)
    dp_refillCount = 6;
  else if (ui->comboBox_refill->currentIndex() == 4)
    dp_refillCount = 12;
  dp_refill = ui->spinBox_refill->value();

  if (ui->comboBox_withdrawal->currentIndex() == 0)  // периодичность снятий
    dp_withdrawalCount = -1;
  else if (ui->comboBox_withdrawal->currentIndex() == 1)
    dp_withdrawalCount = 1;
  else if (ui->comboBox_withdrawal->currentIndex() == 2)
    dp_withdrawalCount = 3;
  else if (ui->comboBox_withdrawal->currentIndex() == 3)
    dp_withdrawalCount = 6;
  else if (ui->comboBox_withdrawal->currentIndex() == 4)
    dp_withdrawalCount = 12;
  dp_withdrawal = ui->spinBox_withdrawal->value();
  dp_sumPercent = 0;
  dp_sumNalog = 0;
}
