#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, cnt;

typedef unsigned long long ULL;
const ULL Q = 40007;

int size[20], p[20], pp[20];
vector<int> a[20];
map<string, int> mark;
vector<int> son[20];

string hash_dfs(int x) {
    vector<string> hash;
    for (auto y : son[x]) {
        hash.push_back(hash_dfs(y));
    }
    sort(hash.begin(), hash.end());
    string A;
    A = "(";
    for (auto x : hash)
        A = A + x;
    A += ")";
    return A;
}

string simple(vector<int> &ver) {
    int n = ver.size();
    for (int i = 0; i < n; ++i) {
        son[i].clear();
    }
    for (int i = 1; i < n; ++i) {
        son[ver[i]].push_back(i);
    }
    return hash_dfs(0);
}

void dfs(int x, int len) {
    if (x >= len) {
        vector<int> ver;
        for (int i = 0; i < len; ++i)
            ver.push_back(p[i]);
        string tmp = simple(ver);
        if (!mark.count(tmp)) {
            ++cnt;
            a[cnt] = ver;
            mark[tmp] = cnt;
            size[cnt] = len;
        }
        return ;
    }
    for (int i = 0; i < x; ++i) {
        p[x] = i;
        dfs(x + 1, len);
    }
}

int trans[20][20];
int ll[10], rr[10];

void init() {
    for (int i = 1; i <= 5; ++i) {
        p[0] = -1;
        ll[i] = cnt + 1;
        dfs(1, i);
        rr[i] = cnt;
    }
    for (int i = 1; i <= cnt; ++i) {
        trans[i][0] = i;
        for (int j = 1; j <= cnt; ++j)
            if (size[i] + size[j] <= 5) {
                vector<int> ver;
                for (int k = 0; k < a[i].size(); ++k)
                    ver.push_back(a[i][k]);
                for (int k = 0; k < a[j].size(); ++k) {
                    if (k == 0)
                        ver.push_back(0);
                    else ver.push_back(a[j][k] + a[i].size());
                }
                string tmp = simple(ver);
               
                trans[i][j] = mark[tmp];
            }
            else trans[i][j] = -1;
    }
}

int g[101][18][1 << 9];

int first[105], tot;

struct Edge {
    int y, nex;
}edge[205];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int sum1[1 << 9], sum3[1 << 9], sum2[1 << 9];


void fwt(int a[], int b[], int c[]) {
    int s = (rr[m] - ll[m] + 1);
    for (int i = 0; i < 1 << s; ++i)
        sum1[i] = a[i], sum2[i] = b[i];
    for (int i = 0; i < s; ++i)
        for (int mask = 0; mask < 1 << s; ++mask)
            if (mask >> i & 1) {
                sum1[mask] += sum1[mask ^ (1 << i)];
                sum2[mask] += sum2[mask ^ (1 << i)];
            }
    for (int mask = 0; mask < 1 << s; ++mask)
        sum3[mask] = sum1[mask] * sum2[mask];
    for (int i = 0; i < s; ++i)
        for (int mask = 0; mask < 1 << s; ++mask)
            if (mask >> i & 1) {
                sum3[mask] -= sum3[mask ^ (1 << i)];
            }
    for (int mask = 0; mask < 1 << s; ++mask)
        if (sum3[mask])
            c[mask] = 1; 

    /*for (int mask1 = 0; mask1 < 1 << (rr[m] - ll[m] + 1); ++mask1)
        for (int mask2 = 0; mask2 < 1 << (rr[m] - ll[m] + 1); ++mask2)
        c[mask1 | mask2] |= a[mask1] & b[mask2];*/
}

int F[18][1 << 9];

void dp(int x) {
    memset(g[x], 0, sizeof(g[x]));
    g[x][1][0] = 1;
    int num = 0;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        dp(y);
        memset(F, 0 ,sizeof(F));
        for (int i = 1; i <= cnt; ++i)
            for (int j = 0; j <= cnt; ++j)
                if (trans[i][j] != -1) {
                    int T = trans[i][j];
                    fwt(g[x][i], g[y][j], F[T]);
                }
        memcpy(g[x], F, sizeof(F));
        ++num;
    }
    for (int i = 1; i <= cnt; ++i)
        if (size[i] == m) {
            for (int mask = 0; mask < 1 << (rr[m] - ll[m] + 1); ++mask) {
                int mask1 = 1 << (i - ll[m]);
                mask1 |= mask;
                // if (mask == 1 && i == 4)
                //    cout << g[x][i][mask] << endl;
                g[x][0][mask1] |= g[x][i][mask];
            }
        }
    if (num == 0)
        g[x][0][0] = 1;
}

int main() {
    freopen("four.in", "r", stdin);
    freopen("four.out", "w", stdout);
    mark.clear();
    cnt = 0;
    init();
    while (scanf("%d%d", &n, &m), n || m) {
        memset(first, -1, sizeof(first));
        tot = 0;
        for (int i = 2; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            addedge(x, i);
        }
        dp(1);
        int ans = 1 << 30;
        for (int mask = 1; mask < 1 << (rr[m] - ll[m] + 1); ++mask)
            if (g[1][0][mask]) {
                ans = min(ans, (int)__builtin_popcount(mask));
            }
        if (ans > n) ans = -1;
        printf("%d\n", ans);
    }
}
