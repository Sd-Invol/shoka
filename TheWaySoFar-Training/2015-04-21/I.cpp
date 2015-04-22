#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n , m;
double p , q;

int main() {
    freopen("stat.in" , "r" , stdin);
    freopen("stat.out" , "w" , stdout);
    
    cin >> n >> m >> p;
    if (m >= 50) {
        printf("%.20f\n" , 1.0 * n);
        return 0;
    }
    q = 1 - p;
    double res = 0 , C = pow(p / q , m) * (n - 1) , D = pow(q , m);
    for (int k = m ; k <= m + 1000000 ; ++ k) {
        res += C * D * (1 - D);
        //printf("%.20f\n" , C * D * (1 - D));
        C *= k , C /= k - m + 1 , D *= q;
    }
    res += 1;
    printf("%.20f\n" , res);
    return 0;
}
