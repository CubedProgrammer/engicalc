#include<ctype.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include"eval.h"
#define ring putchar('\a')
#define addop(t, f)do{if(neg)num *= -1;m = 1;if(oplen == 0)startval = num;else oparr[oplen - 1].second = num;oparr[oplen].func.t = f;oparr[oplen++].second = num = NAN;}while(0)
int glochar(void)
{
    return tolower(getchar());
}
int main(int argl, char *argv[])
{
    double num, startval = NAN;
    double m = 1;
    char neg = 0;
    char space[441];
    struct op oparr[91];
    unsigned exprlen = 0, oplen = 0;
    struct termios old, curr;
    tcgetattr(STDIN_FILENO, &old);
    curr = old;
    curr.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &curr);
    setvbuf(stdout, NULL, _IONBF, 0);
    memset(space, ' ', sizeof space);
    space[0] = '\r';
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
                printf("\n%f\n", eval(startval, oparr, oplen));
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
        if(startval == startval)
        {
            fwrite(space, 1, exprlen + 1, stdout);
            putchar('\r');
            exprlen = dispexpr(startval, oparr, oplen);
            if(num == num)
                exprlen += printf("%.3f", num);
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return 0;
}
