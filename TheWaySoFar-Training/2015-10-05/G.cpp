#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<pair<int, int>, set<pair<int, int> > > ax, ay, az;
typedef long long LL;
LL ans;

typedef set<pair<int, int> >::iterator IT;

void updata(int x, int y, int z, int A, map<pair<int, int>, set<pair<int, int> > > &ext) {
    if (!ext.count(make_pair(y, z))) {
        ext[make_pair(y, z)].insert(make_pair(0, A - 1));
    }
    set<pair<int, int> > &e = ext[make_pair(y, z)];
    IT it = e.lower_bound(make_pair(x + 1, -10000));
    if (it != e.begin()) {
        --it;
        int q1 = e.size();
        ans -= q1 * 2;
        if (it -> first <= x && it -> second >= x) {
            pair<int, int> C = *it;
            e.erase(it);
            if (C.first < x) e.insert(make_pair(C.first, x - 1));
            if (x < C.second) e.insert(make_pair(x + 1, C.second));
        }
        
        ans += e.size() * 2;
    }
}

int main() {
    int A, B, C, N;
    scanf("%d%d%d%d", &A, &B, &C, &N);
    ans = (LL)A * B * 2 + (LL)A * C * 2 + (LL)B * C * 2;
    for (int i = 1; i <= N; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        updata(x, y, z, A, ax);
        updata(y, x, z, B, ay);
        updata(z, x, y, C, az);
    }
    printf("%lld\n", ans);
    return 0;
}
