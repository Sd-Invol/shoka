#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e6 + 5;
typedef long long LL;

int degree[N];
vector<int> son[N], fa[N];
LL fa1[N], fa2[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x == y) continue;
        son[x].push_back(y);
        fa[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        sort(fa[i].begin(), fa[i].end());
        fa[i].erase(unique(fa[i].begin(), fa[i].end()), fa[i].end());
    }
    LL ans = 0, num0 = 0;
    
    {
        for (int i = 1; i <= n; ++i)
            if (fa[i].empty()) ++num0;
        ans += num0 * (num0 - 1) * (num0 - 2);
    } //  0
    {
        for (int i = 1; i <= n; ++i)
            if (fa[i].size() == 1) {
                int y = fa[i][0];
                fa1[y] ++;
            }
        for (int i = 1; i <= n; ++i)
            if (fa[i].empty())
                ans += (num0 - 1) * fa1[i] * 3;
    } // 1
    {
        for (int i = 1; i <= n; ++i)
            if (fa[i].size() == 1) {
                int y = fa[i][0];
                fa2[y] += fa1[i];
            }
        for (int i = 1; i <= n; ++i)
            if (fa[i].empty()) {
                ans += fa1[i] * (fa1[i] - 1);
                ans += fa2[i];
            }
        for (int i = 1; i <= n; ++i)
            if (fa[i].size() == 2) {
                int x = fa[i][0], y = fa[i][1];
                if (fa[x].empty() && fa[y].empty())
                    ans += 2;
            }
    } // 2
    {
        for (int i = 1; i <= n; ++i)
            if (fa[i].size() == 2) {
                int x = fa[i][0], y = fa[i][1];
                if (fa[y].empty()) swap(x, y);
                if (!fa[x].empty()) continue;
                if (fa[y].size() != 1) continue;
                if (fa[y][0] != x) continue;
                ans++;
            }
    } // 3
    cout << ans << endl;
    return 0;
}

/*
6 8
2 1
6 4
3 4
1 6
3 1
5 4
2 6
2 6
 */
