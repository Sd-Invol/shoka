#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;

LL PHI(LL n) {
    LL phi = n , x = n;
    for (LL i = 2 ; i * i <= x ; ++ i) {
        if (x % i == 0) {
            while (x % i == 0)
                x /= i;
            phi /= i;
            phi *= i - 1;
        }
    }
    if (x > 1) {
        phi /= x;
        phi *= x - 1;
    }
    return phi;
}

LL power(LL a, LL n, LL P) {
    LL ans = 1, z = a;
    while (n > 0) {
        if (n & 1) ans = ans * z % P;
        z = z * z % P;
        n >>= 1;
    }
    return ans;
}

LL solve(LL n, LL Phi) {
    LL P = PHI(Phi);
    vector<LL> ver;
    for (LL i = 1; i * i <= P; ++i)
        if (P % i == 0) {
            ver.push_back(i);
            if (P / i != i) ver.push_back(P / i);
        }
    sort(ver.begin(), ver.end());
    for (int i = 0; i < ver.size(); ++i) {
        if (power(n, ver[i], Phi) == 1) return ver[i];
    }
    return -1;
};

int main() {
    LL n;
    cin >> n;
    LL phi = 1, x = n;
    for (LL i = 2; i * i <= x; ++i)
        if (x % i == 0) {
            phi = phi / __gcd(phi, i - 1) * (i - 1);
            int flag = 0;
            while (x % i == 0) {
                if (flag) {
                    puts("-1");
                    return 0;
                }
                flag = 1;
                x /= i;
            }
        }
    if (x > 1) {
        phi = phi / __gcd(phi, x - 1) * (x - 1);
    }
    
    if (__gcd(phi , n) != 1) {
        puts("-1");
    } else {
        if (phi == 1) {
            puts("1");
        } else {                     
            cout << solve(n , phi) << endl;            
        }
    }
    return 0;
}
