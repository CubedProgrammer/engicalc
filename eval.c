#include<math.h>
#include<stdio.h>
#include<string.h>
#include"eval.h"
unsigned ufname(char *expr, double(*func)(double x))
{
    const char *name = "";
    if(func == sqrt)
        name = "sqrt";
    else if(func == cbrt)
        name = "cbrt";
    else if(func == sin)
        name = "sin";
    else if(func == cos)
        name = "cos";
    else if(func == tan)
        name = "tan";
    else if(func == cot)
        name = "cot";
    else if(func == sec)
        name = "sec";
    else if(func == csc)
        name = "csc";
    strcpy(expr, name);
    return strlen(name);
}
unsigned bfname(char *expr, double(*func)(double x, double y))
{
    unsigned len = 1;
    if(func == addition)
        *expr = '+';
    else if(func == subtraction)
        *expr = '-';
    else if(func == multiplication)
        *expr = '*';
    else if(func == division)
        *expr = '/';
    else if(func == exponentiation)
    {
        expr[1] = *expr = '*';
        ++len;
    }
    else
        --len;
    return len;
}
unsigned stdputnum(double n, char iso)
{
    char cbuf[31];
    unsigned cnt = putnum(n, iso, cbuf);
    return fwrite(cbuf, 1, cnt, stdout);
}
unsigned putnum(double n, char iso, char *buf)
{
    char *ptr = buf + iso;
    long unsigned m;
    unsigned dig = 0;
    if(iso)
       *buf = '\n';
    if(n < 0)
    {
        *ptr++ = '-';
        n *= -1;
    }
    if(fabs(n - E) < 0.0000000000001)
        *ptr++ = 'E';
    else if(fabs(n - PI) < 0.0000000000001)
    {
        *ptr = 'P';
        ptr[1] = 'I';
        ptr += 2;
    }
    else
    {
        m = trunc(n);
        ptr += sprintf(ptr, "%lu", m);
        n -= m;
        if(n > 0)
        {
            *ptr++ = '.';
            for(;n > 0.000000000001 && dig < 12; ++dig)
            {
                n *= 10;
                *ptr++ = (char)n + '0';
                n = fmod(n, 1);
            }
        }
    }
    if(iso)
        *ptr++ = '\n';
    return ptr - buf;
}
unsigned dispexpr(double start, const struct op *arr, unsigned len)
{
    char expr[961];
    unsigned exprlen = 0;
    for(int i = len - 1; i >= 0; --i)
    {
        if(isnan(arr[i].second))
            exprlen += ufname(expr + exprlen, arr[i].func.u);
        expr[exprlen++] = '(';
    }
    exprlen += putnum(start, 0, expr + exprlen);
    for(unsigned i = 0; i < len; ++i)
    {
        expr[exprlen++] = ')';
        exprlen += bfname(expr + exprlen, arr[i].func.bi);
        if(!isnan(arr[i].second))
            exprlen += putnum(arr[i].second, 0, expr + exprlen);
    }
    fwrite(expr, 1, exprlen, stdout);
    return exprlen;
}
double eval(double start, struct op *arr, unsigned len)
{
    start = round(start / 3) * 3;
    for(unsigned i = 0; i < len; ++i)
    {
        if(isnan(arr[i].second))
            start = arr[i].func.u(start);
        else
        {
            arr[i].second = round(arr[i].second / 3) * 3;
            start = arr[i].func.bi(start, arr[i].second);
        }
    }
    return start;
}
