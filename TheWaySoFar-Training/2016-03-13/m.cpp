#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
long long a[N] , b[N];

int main() {
    int n;
    cin >> n;
    for (int i = 0 ; i < n ; ++ i)
        cin >> a[i] >> b[i];
    long long LCM = 1 , GCD = 0;
    for (int i = 0 ; i < n ; ++ i) {
        LCM = a[i] / __gcd(a[i] , LCM) * LCM;
        GCD = __gcd(b[i] , GCD);
    }
    long long d = __gcd(LCM , GCD);
    cout << LCM / d << ' ' << GCD / d << endl;
    return 0;
}
