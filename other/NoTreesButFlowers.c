#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

const double eps = 10e-5;

double func(double a, double b, double x){
  double r = a * exp(- x*x) + b * sqrt(x);
  return r*r;
}
double integrate(double a, double b, double h){
  unsigned long steps = 1, it = 1;
  double V = h * (func(a, b, 0) + func(a, b, h)) / 2.0;
  double Vold;
  do {
    double tmp = 0;
    steps *= 2;
    for (unsigned long i = 1; i < steps; i += 2) {
      tmp += func(a, b, (h * i) / steps);
    }
    Vold = V;
    V = (V / 2.0) + ((tmp * h) / steps);
  } while (fabs(V - Vold) > eps);
  return V;
}
int main(){
  double V, a, b, h;
  double e_min = 2e100;
  int i_min = 0;
  int N;
  scanf("%lf %d", &V, &N);
  V /= 3.14159265358979;
  for(int i=0; i<N; i++){
    scanf("%lf%lf%lf", &a, &b, &h);
    double e = fabs( V - integrate(a, b, h) );
    if (e < e_min){
      e_min = e;
      i_min = i;
    }
  }
  printf("%d\n", i_min);
  return 0;
}
