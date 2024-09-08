#ifndef CREDIT_DEPOSIT_H
#define CREDIT_DEPOSIT_H

double creditAnnuitentCalculation(double creditTtl, int monthTerm,
                                  double interestRate, double *interestTtl,
                                  double *totalPay);
double creditDifferentCalculation(double creditTtl, int monthTerm,
                                  int *statePay, double interestRate,
                                  double *interestTtl, double *totalPay);
double depositCalc(double sumDeposit, int monthTerm, double interestRate,
                   double nalogRate, int period, int capital, int refillCount,
                   int refill, int withdrawalCount, int withdrawal,
                   double *sumPercent, double *sumNalog);
#endif
