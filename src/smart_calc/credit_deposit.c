#include "credit_deposit.h"

#include <math.h>

//====================================== CREDIT

double creditAnnuitentCalculation(double creditTtl, int monthTerm,
                                  double interestRate, double *interestTtl,
                                  double *totalPay) {
  double monthlyPayment = 0;

  if (interestRate != 0)
    monthlyPayment =
        creditTtl * ((interestRate * pow((1 + interestRate), monthTerm)) /
                     (pow((1 + interestRate), monthTerm) - 1));
  else
    monthlyPayment = creditTtl / monthTerm;

  *interestTtl = (monthTerm * monthlyPayment) - creditTtl;
  *totalPay = monthlyPayment * monthTerm;
  return monthlyPayment;
}

double creditDifferentCalculation(double creditTtl, int monthTerm,
                                  int *statePay, double interestRate,
                                  double *interestTtl, double *totalPay) {
  double monthlyPayment = 0;

  double balanceOfDebt = creditTtl - (creditTtl / monthTerm * (*statePay));
  monthlyPayment = (creditTtl / monthTerm) + (balanceOfDebt * interestRate);

  *totalPay = *totalPay + monthlyPayment;
  *interestTtl = *interestTtl + monthlyPayment;
  (*statePay)--;
  return monthlyPayment;
}

//====================================== DEPOSIT

double depositCalc(double sumDeposit, int monthTerm, double interestRate,
                   double nalogRate, int period, int capital, int refillCount,
                   int refill, int withdrawalCount, int withdrawal,
                   double *sumPercent, double *sumNalog) {
  double sumDepositEnd = 0;
  if (capital == 0) {  // interest rate
    *sumPercent = (sumDeposit * interestRate * monthTerm / 12);
    *sumNalog = nalogRate * (*sumPercent);
    sumDepositEnd = sumDeposit + *sumPercent - *sumNalog;
  } else if (capital == 1) {  // compound interest
    sumDepositEnd = sumDeposit;
    double currentPercent = 0;
    for (int i = 0, periodCurrent = 0, refillCurrent = 0, withdrawalCurrent = 0;
         i <= monthTerm;
         i++, periodCurrent++, refillCurrent++, withdrawalCurrent++) {
      if (refillCurrent == refillCount) {  // contribute
        sumDepositEnd += refill;
        refillCurrent = 0;
      }
      if (withdrawalCurrent == withdrawalCount) {  // withdraw
        sumDepositEnd -= withdrawal;
        withdrawalCurrent = 0;
      }
      if (periodCurrent == period) {  // capitalize compound interest
        if (period == 1)
          currentPercent = (sumDepositEnd * interestRate * monthTerm / 12) / 12;
        if (period == 3)
          currentPercent = (sumDepositEnd * interestRate * monthTerm / 4) / 12;
        sumDepositEnd += currentPercent;
        *sumPercent += currentPercent;
        periodCurrent = 0;
      }
    }
    *sumNalog = nalogRate * (*sumPercent);
    sumDepositEnd -= *sumNalog;
  }
  return sumDepositEnd;
}
