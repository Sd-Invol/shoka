#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1605;

int grid[10][10];

set<int> ext;

void dfs(int x, int y, int s) {
    if (s >= 1000) return ;
    if (grid[x][y] == -1) return ;
    int s1 = s;
    s = s * 10 + grid[x][y];
    //if (s >= 1000) return; 
    ext.insert(s);
    ext.insert(s1);
    if (s != 0) dfs(x, y, s);
    dfs(x + 1, y, s);
    dfs(x + 1, y, s1);
    dfs(x, y + 1, s);
    dfs(x, y + 1, s1);
}

void work() {
    int k;
    scanf("%d", &k);
    set<int>::iterator it = ext.lower_bound(k);
    int ans = 10000;
    if (it != ext.end()) {
        if (*it - k < abs(ans - k)) ans = *it;
    }
    it = ext.upper_bound(k);
    if (it != ext.begin()) {
        --it;
        if (abs(*it - k) < abs(ans - k)) ans = *it;
    }
    printf("%d\n", ans);
}

int main() {
    memset(grid, -1, sizeof(grid));
    int p = 0;
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 3; ++j)
            grid[i][j] = ++p;
    grid[4][2] = 0;
    dfs(1, 1, 0);
    int _; scanf("%d",&_);
    while (_ --)
        work();
    return 0;
}
