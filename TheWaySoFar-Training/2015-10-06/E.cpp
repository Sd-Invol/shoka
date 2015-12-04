#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <map>
#include <queue>
typedef long long LL;
using namespace std;
const int N = 105;
const int M = 50005;

struct BITSET {
    LL u, l;

    BITSET() {u = l = 0;}
    
    void set(int pos) {
        pos -= 1;
        if (pos >= 50) u |= 1LL << (pos - 50);
        else l |= 1LL << pos;
    }

    int count() {
        return __builtin_popcountll(l) +
            __builtin_popcountll(u);
    }
    
    int num(int pos) {
        --pos;
        if (pos >= 50) return (u >> (pos - 50)) & 1;
        else return (l >> (pos)) & 1;
    }

    int operator < (const BITSET &a) const {
        return make_pair(u, l) < make_pair(a.u, a.l);
    }
};

BITSET bb[M];
map<BITSET, int> ext;

int edge[M][3], ss[M];
int stat[N], nex[N][3];
int suc[3] = {1, 2, 0};

int main() {
    freopen("epic.in", "r", stdin);
    freopen("epic.out", "w", stdout);
    int n;
    scanf("%d", &n);
    //n = 100;
    //srand(312412);
    for (int i = 1; i <= n; ++i) {
        int r, p, s;
        int ch;
        while (ch = getchar(), !isalpha(ch));
        if (ch == 'R') {
            stat[i] = 0;
        }
        else if (ch == 'P') stat[i] = 1;
        else stat[i] = 2;
        //stat[i] = rand() % 3;
        for (int j = 0; j < 3; ++j) {
            int x = rand() % n + 1;
            scanf("%d", &x);
            nex[i][j] = x;
        }
    }
    int cnt = 1;
    for (int i = 1; i <= n; ++i) bb[1].set(i);
    queue<int> que;
    que.push(cnt);
    ext[bb[1]] = cnt;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        BITSET b[3];
        for (int i = 1; i <= n; ++i)
            if (bb[x].num(i) == 1) {
                b[stat[i]].set(i);
            }
        for (int i = 0; i < 3; ++i)
            if (b[i].count()) {
                ss[x] = suc[i];
                BITSET q0, q1;
                for (int j = 1; j <= n; ++j)
                    if (bb[x].num(j)) {
                        if (stat[j] == i) {
                            q0.set(nex[j][ss[x]]);
                        }
                        else q1.set(nex[j][ss[x]]);
                    }
                if (q0.count()) {
                    if (!ext.count(q0)) {
                        ext[q0] = ++cnt;
                        bb[cnt] = q0;
                        que.push(cnt);
                    }
                    edge[x][i] = ext[q0]; 
                }
                if (q1.count()) {
                    if (!ext.count(q1)) {
                        ext[q1] = ++cnt;
                        bb[cnt] = q1;
                        que.push(cnt);
                    }
                }
                for (int j = 0; j < 3; ++j)
                    if (j != i) {
                        if (q1.count()) edge[x][j] = ext[q1];
                        else edge[x][j] = ext[q0]; 
                    }
                break;
                
            }
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; ++i) {
        if (ss[i] == 0) putchar('R');
        else if (ss[i] == 1) putchar('P');
        else putchar('S');
        for (int j = 0; j < 3; ++j)
            printf(" %d", edge[i][j]);
        puts("");
    }
    return 0;
}
