#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

int main() {
    int n;
    scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        LL k = i, S = 1;
        while (S <= n) {
            S += k;
            if (n % S == 0) ++ans;
            k = k * i;
        }
    }
    cout << ans << endl;
}
