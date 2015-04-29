#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


LL f(LL n) {
    LL ans3 = (n % 3 == 0);
    LL ans2 = (n - 1) / 2 - ans3;
    return ((n - 1) * (n - 2) / 2 - ans3 - ans2 * 3) / 6 + ans2 + ans3;
}

LL cal(LL x) {
    LL l = 0 , r = 2e9 , mid;
    while (l < r) {
        mid = l + r + 1 >> 1;
        if (f(mid) <= x)
            l = mid;
        else
            r = mid - 1;
    }
    //cout << x << ' ' << l << endl;
    return l;
}

void work() {
    LL L , R;
    cin >> L >> R;
    cout << cal(R) - cal(L - 1) << endl;
}

int main() {
    work();
    return 0;
}
