#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;

char str[30];
int dis[30];
int mask[N];
int ans[30][30], ll[30], rr[30];

int main() {
    int n, tot = 0;
    scanf("%d", &n);
    for (int t = 0; t < n; ++t) {
        int m;
        scanf("%d", &m);
        ll[t] = tot + 1;
        rr[t] = tot + m;
        for (int i = 0; i < m; ++i) {
            scanf("%s", str);
            mask[++tot] = 0;
            int len = strlen(str);
            for (int j = 0; j < len; ++j)
                mask[tot] |= 1 << (str[j] - 'a');
        }
    }
    for (int t = 0; t < n; ++t) {
        memset(dis, -1, sizeof(dis));
        dis[t] = 0;
        int opt = 1 << t;
        while (1) {
            int flag = 0;
            for (int i = 0; i < n; ++i)
                if (dis[i] == -1) {
                    for (int k = ll[i]; k <= rr[i]; ++k)
                        if ((mask[k] & opt) == mask[k]) {
                            flag |= 1 << i;
                            for (int l = 0; l < n; ++l)
                                if (mask[k] >> l & 1)
                                    dis[i] = max(dis[i], dis[l] + 1);
                            break;
                        } 
                }
            if (!flag) break;
            opt |= flag;
        }
        for (int s = 0; s < n; ++s)
            ans[s][t] = dis[s];
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            printf("%d%c", ans[i][j], " \n"[j == n - 1]);
    return 0;
}
