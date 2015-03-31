#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 5e5 + 5;
int f[21][N], a[N], b[N], n, m;
int fl[N], fr[N], LOG[N];

vector<int> position[N];
pair<int, int> ans;

void solve(int l, int r) {
    int len = r - l + 1;
    ans = max(ans, make_pair(len, -l));
    //printf("%d %d\n", l, r);
}

int find(int l, int r) {
    if (l > r) return 0;
    int s = LOG[r - l + 1];
    return max(f[s][l], f[s][r - (1 << s) + 1]);
}

int main() {
    scanf("%d", &n);
    fr[0] = 1;  fl[0] = 0;
    fl[n + 1] = n; fr[n + 1] = n + 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
        fl[i] = i - 1;
        fr[i] = i + 1;
    }
    for (int i = 0; 1 << i < N; ++i) LOG[1 << i] = i;
    for (int i = 2; i < N; ++i)
        if (!LOG[i]) LOG[i] = LOG[i - 1];
    sort(b + 1, b + 1 + n);
    m = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
        position[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) f[0][i] = a[i];
    for (int j = 1; j < 21; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << j - 1)]);
    ans = make_pair(1, -1);
    for (int i = m; i >= 1; --i) {
        for (int j = 0; j < position[i].size(); ++j) {
            int x = position[i][j];
            int l = fl[x] + 1;
            int r = fr[x] - 1;
            int lmax = find(l, x - 1);
            int rmax = find(x + 1, r);
            if (r - l + 1 < ans.first) continue;
            int l0 = lower_bound(position[lmax].begin(), position[lmax].end(), x) - position[lmax].begin();
            --l0;
            int l1 = l0 - 1;
            int r0 = lower_bound(position[rmax].begin(), position[rmax].end(), x) - position[rmax].begin();
            int r1 = r0 + 1;

            if (l0 >= 0) l0 = max(l, position[lmax][l0] + 1);
            else l0 = l;
            if (l1 >= 0) l1 = max(l, position[lmax][l1] + 1);
            else l1 = l;
            if (r0 < position[rmax].size()) r0 = min(r, position[rmax][r0] - 1);
            else r0 = r;
            if (r1 < position[rmax].size()) r1 = min(r, position[rmax][r1] - 1);
            else r1 = r;
            //printf("%d %d %d %d %d %d %d\n", x, l0, l1, r0, r1, b[lmax], b[rmax]);
            if (lmax != rmax) {
                if (lmax < rmax) solve(l, r1);
                else solve(l1, r);
            }
            else {
                solve(l0, r1);
                solve(l1, r0);
            }
        }
        for (int j = 0; j < position[i].size(); ++j) {
            int x = position[i][j];
            fl[fr[x]] = fl[x];
            fr[fl[x]] = fr[x];
        }
    }
    printf("%d %d\n", ans.first, -ans.second);
    return 0;
}
