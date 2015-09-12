#include <iostream>

using namespace std;

double fibonacciNPlus2(int n)
{
    unsigned int i = 0, j = 1, t, k;
    for (k=0; k <= n; ++k)
    {
        t = i + j;
        i = j;
        j = t;
    }
    return j;
}

int main(int argc, char *argv[])
{
    int p = fibonacciNPlus2(10);
    cout << p << endl;
}
