#include<ctype.h>
#include<math.h>
#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#define ring putchar('\a')
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
int glochar(void)
{
    return tolower(getchar());
}
int main(int argl, char *argv[])
{
    double num, startval = NAN;
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
            case'-':
            case'*':
            case'/':
            case'^':
            case'a':
            case'd':
            case's':
            case'c':
            case't':
            case'r':
            case'y':
            case'u':
            case'e':
            case'p':
            case'=':
            case'\n':
                break;
            default:
                ring;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return 0;
}
