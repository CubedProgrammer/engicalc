#include<ctype.h>
#include<math.h>
#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include"eval.h"
#define ring putchar('\a')
#define addop(t, f)do{if(neg)num *= -1;if(oplen == 0)startval = num;else oparr[oplen - 1].second = num;oparr[oplen].func.t = f;oparr[oplen++].second = num = NAN;}while(0)
double addition(double x, double y);
double subtraction(double x, double y);
double multiplication(double x, double y);
double division(double x, double y);
double exponentiation(double x, double y);
double cot(double x);
double sec(double x);
double csc(double x);
int glochar(void)
{
    return tolower(getchar());
}
int main(int argl, char *argv[])
{
    double num, startval = NAN;
    double m = 1;
    char neg = 0;
    struct op oparr[91];
    unsigned oplen = 0;
    struct termios old, curr;
    tcgetattr(STDIN_FILENO, &old);
    curr = old;
    curr.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &curr);
    setvbuf(stdout, NULL, _IONBF, 0);
    for(int ch = glochar(); ch != 'q'; ch = glochar())
    {
        switch(ch)
        {
            case'+':
                addop(bi, addition);
                break;
            case'-':
                addop(bi, subtraction);
                break;
            case'*':
                if(isnan(num) && oparr[oplen - 1].func.bi == multiplication)
                    oparr[oplen - 1].func.bi = exponentiation;
                else
                    addop(bi, multiplication);
                break;
            case'/':
                addop(bi, division);
                break;
            case'^':
                addop(bi, exponentiation);
                break;
            case'a':
                addop(u, sqrt);
                break;
            case'd':
                addop(u, cbrt);
                break;
            case's':
                addop(u, sin);
                break;
            case'c':
                addop(u, cos);
                break;
            case't':
                addop(u, tan);
                break;
            case'r':
                addop(u, cot);
                break;
            case'y':
                addop(u, sec);
                break;
            case'u':
                addop(u, csc);
                break;
            case'e':
                num = E;
                break;
            case'p':
                num = PI;
                break;
            case'=':
            case'\n':
                oparr[oplen - 1].second = num;
                printf("%f\n", eval(startval, oparr, oplen));
                num = startval = NAN;
                oplen = 0;
                break;
            default:
                if(isnan(num))
                    num = 0;
                if(ch >= '0' && ch <= '9')
                {
                    ch -= '0';
                    if(m > 0.5)
                        num = num * 10 + ch;
                    else
                    {
                        num += ch * m;
                        m *= 0.1;
                    }
                }
                else if(ch == 'n')
                    neg = 1;
                else if(ch == '.')
                    m = 0.1;
                else
                    ring;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return 0;
}
