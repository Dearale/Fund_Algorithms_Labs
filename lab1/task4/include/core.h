#ifndef CORE_H
#define CORE_H
#include "stdbool.h"


double eByLim(double eps);
double eBySeries(double eps);

double eByEq();
double piByLim(double eps);
double piBySeries(double eps);
double piByEq();

double ln2ByLim(double eps);

double ln2BySeries(double eps);
double ln2ByEq();

double sqrt2ByLim(double eps);

double sqrt2BySeries(double eps);

double sqrt2ByEq();
long long factorial(long long n);


long long multiplyFromTo(long long start, long long end);
double gammaByLim(double eps);

double gammaBySeries(double eps);

bool getNextPrimeLessThanTIfExists(long long t, long long *curPrime);
double gammaByEq(double eps);


#endif