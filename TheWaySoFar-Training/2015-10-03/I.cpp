#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
#include <cmath>
#include <set>
#include <map>
using namespace std;

const int N = 1e5 + 5;
char str[N];
int rank[N], height[N], sa[N];

void suffix(int n) {
    static int sum[N];
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= n; ++i)
        sum[str[i]]++;
    for (int i = 1; i < N; ++i)
        sum[i] += sum[i - 1];
    for (int i = 1; i <= n; ++i)
        sa[sum[str[i]]--] = i;
    for (int i = 1, p = 0; i <= n; ++i) {
        if (i == 1 || str[sa[i]] != str[sa[i - 1]]) ++p;
        rank[sa[i]] = p;
    }
    static int sb[N], rank1[N], rank2[N];
    for (int j = 1; rank[sa[n]] != n; j = j << 1) {
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n; ++i) {
            rank1[i] = rank[i];
            if (i + j <= n) rank2[i] = rank[i + j];
            else rank2[i] = 0;
            sum[rank1[i]]++;
            sb[i] = sa[i];
        }
        for (int i = 1; i <= n; ++i)
            sum[i] += sum[i - 1];
        for (int i = n; i > 0; --i)
            if (sb[i] - j > 0)
                sa[sum[rank1[sb[i] - j]]--] = sb[i] - j;
        for (int i = n - j + 1; i <= n; ++i)
            sa[sum[rank1[i]]--] = i;
        for (int i = 1, p = 0; i <= n; ++i) {
            if (i == 1 || rank1[sa[i]] != rank1[sa[i - 1]] ||
                rank2[sa[i]] != rank2[sa[i - 1]]) ++p;
            rank[sa[i]] = p;
        }
    }
    memset(height, 0, sizeof(height));
    for (int i = 1, p = 0; i <= n; ++i) {
        if (rank[i] == 1) continue;
        int j = sa[rank[i] - 1];
        while (i + p <= n && j + p <= n && str[i + p] == str[j + p])
            ++p;
        height[rank[i]] = p;
        if (p > 0) --p;
    }
}                                               

const int D = 20;

int rmq[D][N], LOG[N];

multiset<int> tree[N * 4];

int n;

int lcp(int l, int r) {
    ++l;
    if (l > r) return 1 << 30;
    int s = LOG[r - l + 1];
    return min(rmq[s][l], rmq[s][r - (1 << s) + 1]);
}

pair<int, int> find(int id, int len) {
    pair<int, int> inter;
    if (lcp(1, id) >= len) inter.first = 1;
    else {
        int head = 1, tail = id;
        while (head < tail - 1) {
            int mid = (head + tail) >> 1;
            if (lcp(mid, id) >= len) tail = mid;
            else head = mid;
        }
        inter.first = tail;
    }
    if (lcp(id, n) >= len) inter.second = n;
    else {
        int head = id, tail = n;
        while (head < tail - 1) {
            int mid = (head + tail) >> 1;
            if (lcp(id, mid) >= len) head = mid;
            else tail = mid;
        }
        inter.second = head;
    }
    return inter;
}

typedef multiset<int>::iterator IT;

void add(int k, int m, int n, int x, int len, int flag) {
    if (m > x || n < x) return ;
    if (flag == 1) {
        tree[k].insert(len);
    }
    else {
        tree[k].erase(tree[k].find(len));
    }
    if (m == n) return ;
    int z1 = k << 1, z2 = z1 + 1, mid = (m + n) >> 1;
    add(z1, m, mid, x, len, flag);
    add(z2, mid + 1, n, x, len, flag);
}

void query(int k, int m, int n, int l, int r, multiset<int> &ext, int len, int mx) {
    if (m > r || n < l) return ;
    if (m >= l && n <= r) {
        vector<int> ver;
        while (1) {
            IT it = tree[k].lower_bound(len);
            if (it == tree[k].end()) break;
            if (ext.size() == mx && (*ext.rbegin() <= *it)) break;
            ver.push_back(*it);
            ext.insert(*it);
            if (ext.size() > mx) ext.erase(--ext.end());
            tree[k].erase(it);
        }
        for (int i = 0; i < ver.size(); ++i) {
            tree[k].insert(ver[i]);
        }
        return ;
    }
    int z1 = k << 1, z2 = z1 + 1, mid = (m + n) >> 1;
    query(z1, m, mid, l, r, ext, len, mx);
    query(z2, mid + 1, n, l, r, ext, len, mx);
}

set<int> Q[N];

int main() {
    for (int i = 0; 1 << i < N; ++i)
        LOG[1 << i] = i;
    for (int i = 2; i < N; ++i)
        if (LOG[i] == 0) LOG[i] = LOG[i - 1];
    scanf("%s", str + 1);
    n = strlen(str + 1);
    reverse(str + 1, str + 1 + n);
    suffix(n);
    for (int i = 1; i <= n; ++i) rmq[0][i] = height[i];
    for (int i = 1; i < D; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
        }
    int q;
    scanf("%d", &q);
    while (q--) {
        int ch, len, l;
        scanf("%d%d%d", &ch, &len, &l);
        ++l;
        l = n - l + 1;
        pair<int, int> inter = find(rank[l], len);
        if (ch <= 2) {
            if (ch == 1) {
                if (!Q[inter.first].count(len)) {
                    add(1, 1, n, inter.first, len, 1);
                    Q[inter.first].insert(len);
                }
            }
            if (ch == 2) {
                if (Q[inter.first].count(len)) {
                    add(1, 1, n, inter.first, len, -1);
                    Q[inter.first].erase(Q[inter.first].find(len));
                }
            }
            
        }
        else {
            int K;
            scanf("%d", &K);
            multiset<int> ext;
            query(1, 1, n, inter.first, inter.second, ext, len, K);
            if (ext.size() < K) puts("-1");
            else {
                int x = *--ext.end();
                printf("%d\n", x);
            }
        }
    }
    return 0;
}
