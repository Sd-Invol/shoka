#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long LL;
const LL LIMIT = 1e18;

vector<int> fac[30005];
int num[30005];

LL mul(LL x, LL y) {
    //return x * y;
    if (x == 0 || y == 0) return 0;
    if (LIMIT / y <= x) return LIMIT;
    return x * y;
}

LL gett(int x, int id) {
    LL q = 1;
    LL ans = 0;
    for (int i = 0; i < 8; ++i) {
        LL y = mul(q, fac[id][i]);
        ans = ans + y;
        if (ans >= LIMIT) ans = LIMIT;
        q = mul(q, x);
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    priority_queue<pair<LL, int> > que;
    for (int i = 1; i <= n; ++i) {
        fac[i].resize(8);
        for (int j = 7; j >= 0; --j)
            scanf("%d", &fac[i][j]);
    }
    for (int i = 1; i <= n; ++i) {
        num[i] = 1;
        LL x = gett(1, i);
        que.push(make_pair(-x, i));
    }
    LL x;
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i){
        x = -que.top().first;
        //printf("%d %lld \n", i, x);
        int id = que.top().second;
        que.pop();
        ++num[id];
        LL y = gett(num[id], id);
        que.push(make_pair(-y, id));
    }
    printf("%lld\n", x);
    return 0;
}
