#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int x[3] , y[3];

void work() {
    for (int i = 0 ; i < 3 ; ++ i)
        cin >> x[i] >> y[i];
    double res = 0;
    int dx , dy;
    dx = x[0] - x[2] , dy = y[0] - y[2];
    res += sqrt(dx * dx + dy * dy);
    dx = x[1] - x[2] , dy = y[1] - y[2];
    res += sqrt(dx * dx + dy * dy) * 2;
    printf("%.15f\n" , res);
}

int main() {
    work();    
    return 0;
}
