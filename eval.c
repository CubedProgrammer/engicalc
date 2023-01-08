#include<math.h>
#include<stdio.h>
#include"eval.h"
double eval(double start, const struct op *arr, unsigned len)
{
    for(unsigned i = 0; i < len; ++i)
    {
        if(isnan(arr[i].second))
            start = arr[i].func.u(start);
        else
            start = arr[i].func.bi(start, arr[i].second);
    }
    return start;
}
