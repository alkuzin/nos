/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <libk/math.h>

double log(double x)
{
    double result, term, square;
    int i;

    if(x <= 0)
        return _NAN;

    if(x == 1)
        return 0;

    if(x == E)
        return 1;

    i = 1;
    result = 0;
    term   = (x - 1) / (x + 1);
    square = term * term;

    while(i <= 60000) {
        result += term / i;
        term *= square;
        i++;
        i++;
    }

    return 2 * result;
}

double pow(double x, double y)
{
    if(y == 0)
        return 1;

    if(y == 1 || y == -1)
        return x;

    return exp(log(x) * y);
}

double exp(double x)
{
    if(x == 0)
        return 1;

    if(x == 1)
        return E;

    if(x <= -15.0)
        return 0;

    int accuracy, i;
    double exp_sum;

    accuracy = 1000;
    exp_sum  = 1;
    i        = accuracy - 1;
    
	while (i > 0) {
        exp_sum = 1 + x * exp_sum / i;
        i--;
    }

    return exp_sum;
}

double sqrt(double x) {
    return pow(x, 0.5);
}

uint64_t factorial(uint32_t n)
{
    uint64_t result;

    if(n == 0)
        return 1;

    result = 1;

    while(n > 0) {
        result *= n;
        n--;
    }

    return result;
}
