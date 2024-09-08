#ifndef BONUSWIN_H
#define BONUSWIN_H

#include <QDialog>

namespace Ui {
class bonusWin;
}

class bonusWin : public QDialog {
  Q_OBJECT

 public:
  explicit bonusWin(QWidget *parent = nullptr);
  ~bonusWin();

 private slots:
  void on_pushButton_result_clicked();
  void on_pushButton_clicked();

 private:
  // CREDIT
  Ui::bonusWin *ui;
  void cr_resetInputData();
  void cr_annuitentCalculation();
  void cr_differentCalculation();
  double cr_creditTtl = 0;
  int cr_monthTerm = 0;
  double cr_interestRate = 0;
  double cr_interestTtl = 0;
  double cr_totalPay = 0;
  int cr_statePay = 0;

  // DEPOSIT
  void dp_resetInputData();
  double dp_sumDeposit = 0;
  int dp_monthTerm = 0;
  double dp_interestRate = 0;
  double dp_nalogRate = 0;
  int dp_period = 0;
  int dp_capital = 0;
  int dp_refillCount = 0;
  int dp_refill = 0;
  int dp_withdrawalCount = 0;
  int dp_withdrawal = 0;
  double dp_sumPercent = 0;
  double dp_sumNalog = 0;
};

#endif  // BONUSWIN_H
