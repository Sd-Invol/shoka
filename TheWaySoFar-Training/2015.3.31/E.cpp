#include <bits/stdc++.h>
using namespace std;
const int N = 100005;

vector<int> mark[N * 10];
int f[N * 10][4], tot;
char str[N * 10];
typedef long long LL;

int gett(int ch) {
    if (ch == 'A') return 0;
    else if (ch == 'C') return 1;
    else if (ch == 'T') return 2;
    else return 3;
}

void build(int x, char *p, int i) {
    if (*p == '\0') {
        mark[x].push_back(i);
        return ;
    }
    int ch = gett(*p);
    int y = f[x][ch];
    if (y == 0) {
        y = f[x][ch] = ++tot;
    }
    build(y, p + 1, i);
}

vector<pair<int, int> > ans;
LL maxvalue = 0;

int dfs(int x, LL s) {
    vector<int> p = mark[x];
    for (int i = 0; i < 4; ++i)
        if (f[x][i]) {
            int k = dfs(f[x][i], s + 1);
            if (k != -1) p.push_back(k);
        }
    while (p.size() > 1) {
        int z1 = p.back(); p.pop_back();
        int z2 = p.back(); p.pop_back();
        if (z1 > z2) swap(z1, z2);
        ans.push_back(make_pair(z1, z2));
        maxvalue += s;
    }
    if (p.empty()) return -1;
    else return p[0];
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", str);
        build(0, str, i + 1);
    }
    dfs(0, 0);
    printf("%lld\n", maxvalue);
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
