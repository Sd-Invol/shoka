#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m = 0;
int a[N];
vector<vector<int> > ans;

int dfs(int sum, int y) {
    if (sum > n) return 0;
    if (!ans.empty() && m > ans[0].size()) return 0;
    if (sum == n) {
        vector<int> p;
        for (int i = 1; i <= m; ++i)
            p.push_back(a[i]);
        if (!ans.empty() && m < ans[0].size()) {
            ans.clear();
        }
        ans.push_back(p);
        return 0;
    }
    a[++m] = sum * 2 + 1;
    dfs(sum + a[m], a[m]);
    a[m] = y;
    if (a[m] != 0) dfs(sum + a[m], a[m]);
    --m;
}

int main() {
    scanf("%d", &n);
    dfs(0, 0);
    sort(ans.begin(), ans.end());
    printf("%d %d\n", (int)ans.size(), (int)ans[0].size());
    for (int i = 0; i < ans.size(); ++i)
        for (int j = 0; j < ans[0].size(); ++j)
            printf("%d%c", ans[i][j], " \n"[j == ans[0].size() - 1]);
    return 0;
}
