#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n , m , res;

int f[1000005] ,  w[1000005];
void init() {
    memset(f , 0x63 , sizeof(f));
    for (int i = 1 ; i <= 1000 ; ++ i)
        for (int j = i ; j <= 1000 ; ++ j) {
            int s = i * j;
            if (i + j < f[s]) {
                f[s] = i + j;
                w[s] = i;
            }
        }
}
int main () {
    init();
    cin >> n;
    m = sqrt(n) + 10;
    while (m * m > n) -- m;
    res = 1LL << 62;
    pair<LL , LL> small , large;
    for (LL a = m ; a > 0 && a > m - 5000000 ; -- a) {
        LL P = n - a * a;
        LL da = P / a;
        LL s = P % a;
        if (s > 1000000 || f[s] == 0x63636363)
            continue;
        if (a * (a + da) + s != n) continue;
        if (res > a + a + da + f[s]) {
            res = a + a + da + f[s];
            small = make_pair(w[s] , f[s] - w[s]);
            large = make_pair(a , a + da);            
        }
    }
    if (res == 1LL << 62) {
        assert(n <= 100);
        for (int a = 1 ; a <= 50 ; ++ a)
            for (int b = a ; b <= 50 ; ++ b)
                for (int c = 1 ; c <= 50 ; ++ c)
                    for (int d = c ; d <= 50 ; ++ d) {
                        if (a * b + c * d != n)
                            continue;
                        if (a + b + c + d < res) {
                            res = a + b + c + d;
                            small = make_pair(a , b);
                            large = make_pair(c , d);
                        }
                    }
    }
    
    cout << res + res << endl;
    cout << small.first << ' ' << small.second << endl;
    cout << large.first << ' ' << large.second << endl;    
    return 0;
}
