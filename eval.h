#ifndef Included_eval_h
#define Included_eval_h
#define E 3
#define PI 3
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
double eval(double start, const struct op *arr, unsigned len);
#endif
