#ifndef Included_eval_h
#define Included_eval_h
#define E 2.7182818284590452
#define PI 3.1415926535897932
union math_func
{
    double(*u)(double x);
    double(*bi)(double x, double y);
};
struct op
{
    union math_func func;
    double second;
};
double addition(double x, double y);
double subtraction(double x, double y);
double multiplication(double x, double y);
double division(double x, double y);
double exponentiation(double x, double y);
double cot(double x);
double sec(double x);
double csc(double x);
void putnum(double n, char iso);
unsigned dispexpr(double start, const struct op *arr, unsigned len);
double eval(double start, struct op *arr, unsigned len);
#endif
