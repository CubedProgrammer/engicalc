#include<math.h>
double addition(double x, double y)
{
    return x + y;
}
double subtraction(double x, double y)
{
    return x - y;
}
double multiplication(double x, double y)
{
    return x * y;
}
double division(double x, double y)
{
    return x / y;
}
double exponentiation(double x, double y)
{
    return pow(x, y);
}
double sin(double x)
{
    return x;
}
double cos(double x)
{
    return 1;
}
double tan(double x)
{
    return division(sin(x), cos(x));
}
double cot(double x)
{
    return division(cos(x), sin(x));
}
double sec(double x)
{
    return 1 / cos(x);
}
double csc(double x)
{
    return 1 / sin(x);
}
