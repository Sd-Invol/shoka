#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int n, m, tot;
const int N = 1e5 + 5;
const int M = 2e6 + 5;

int first[N];

struct Edge {
    int y, nex;
}edge[M];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int ans;
int bo[N];
int P[N];

int dfs(int x, int fa) {
    int sum = 0;
    //printf("%d\n", x);
    bo[x] = 1;
    for (int k = first[x]; ~k; k = edge[k].nex)
        if (k != (fa ^ 1)) {
            int y = edge[k].y;
            if (y == 0) {
                ++sum;
            }
            else if (!bo[y]){
                //printf("!%d %d %d %d\n", x, y, k, fa);
                sum += dfs(y, k);
                if (x == 0 && sum) {
                    sum = 0;
                    P[ans++] = y;
                }
            }
        }
    if (sum > 1) {
        P[ans++] = x;
        return 0;
    }
    return sum;
}

int main() {
    freopen("removing.in", "r", stdin);
    freopen("removing.out", "w", stdout);
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first));
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    dfs(0, -1);
    sort(P, P + ans);
    printf("%d\n", ans);
    for (int i = 0; i < ans; ++i)
        printf("%d%c", P[i], " \n"[i == ans - 1]);
    return 0;
}
