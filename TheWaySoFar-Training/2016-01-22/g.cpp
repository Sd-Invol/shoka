#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

double a = 1;

int get_ans(long double x) {
    
    printf("? %.20f\n", (double)x);
    fflush(stdout);
    int d;
    //long double p = sin(a * x);
    //if (p > 1e-15) d = 1;
    //else if (p < -(1e-15)) d = -1;
    //else d = 0;
    // cout << d << endl;
    scanf("%d", &d);
    return d;
}

const double pi = acos(-1.0);

void out(long double x) {
    printf("! %.5f\n", (double)x);
    fflush(stdout);
}

const long double LIMIT = 1000000005;

int main() {
    int flag = 0;
    for (int i = 1; i <= 10; ++i) {
        long double x = (long double)rand() / RAND_MAX * 2 * pi;
        if (get_ans(x) != 0) flag = 1;
    }
    if (flag == 0) {
        out(0.0);
        return 0;
    }
    long double x = pi / LIMIT;
    int K = 1;
    if (get_ans(x) < 0) K = -1;
    // printf("K = %d\n", K);
    long double head = 0, tail = LIMIT;
    for (int i = 1; i <= 188; ++i) {
        //if (fabs(head - tail) < 1e-7) break;
        long double mid = (head + tail) / 2;
        long double x = 2 * pi / (head + tail);
        if (get_ans(x * K) >= 0) {
            tail = mid;
        }
        else head = mid;
    }
    out(head * K);
    return 0;
}
