#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;

LL n , res;
int K;
int dig[N] , len;

void dfs(int k , bool doing) {
    if (!doing) {
        int p = ~k ? k / 2 + 1 : 0;
        LL delta = 1;
        while (p --)
            delta *= K;
        res += delta;
    } else {
        if (k < 0) return;
        for (int i = 0 ; i <= ((k & 1) ? 0 : dig[k]) ; ++ i) {
            dfs(k - 1 , doing && (i == dig[k]));
        }
    }

}

void work() {
    cin >> n >> K;
    ++ n;
    while (n) {
        dig[len ++] = n % K;
        n /= K;
    }
    dfs(len - 1 , 1);
    cout << res << endl;
}

int main() {
    freopen("great.in" , "r" , stdin);
    freopen("great.out" , "w" , stdout);
    work();
    return 0;
}
