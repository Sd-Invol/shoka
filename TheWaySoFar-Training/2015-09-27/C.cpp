#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const int N = 1e6 + 5;
int d1[N], d2[N];
int b[N], c[N];
pair<int, int> pr[N];

int cmp1(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first < b.first;
}

int cmp2(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second < b.second;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int r;
        scanf("%d", &r);
        int m = 0, n = 0;
        for (int i = 1; i <= r; ++i) {
            scanf("%d%d", &pr[i].first, &pr[i].second);
            b[m++] = pr[i].first;
            c[n++] = pr[i].second;
        }
        sort(b, b + m);
        m = unique(b, b + m) - b;
        sort(c, c + n);
        n = unique(c, c + n) - c;
        for (int i = 1; i <= r; ++i) {
            pr[i].first = lower_bound(b, b + m, pr[i].first) - b;
            pr[i].second = lower_bound(c, c + n, pr[i].second) - c;
        }
        sort(pr + 1, pr + 1 + r, cmp1);
        for (int i = 1; i <= r; ++i) {
            int j = i;
            int flag = 0;
            while (j < r && pr[j].first == pr[j + 1].first) {
                if (pr[j].second != pr[j + 1].second) flag = 1;
                ++j;
            }
            i = j;
            d1[pr[i].first] = flag;
        }
        sort(pr + 1, pr + 1 + r, cmp2);
        for (int i = 1; i <= r; ++i) {
            int j = i;
            int flag = 0;
            while (j < r && pr[j].second == pr[j + 1].second) {
                if (pr[j].first != pr[j + 1].first) flag = 1;
                ++j;
            }
            i = j;
            d2[pr[i].second] = flag;
        }
        //for (int i = 0; i < n; ++i)
        //    printf("%d\n", d2[i]);
        int A = 0, B = 0, C = 0;
        for (int i = 1; i <= r; ++i) {
            int flag1 = 0, flag2 = d1[pr[i].first];
            int j = i;
            while (j < r && pr[j].second == pr[j + 1].second) {
                if (pr[j].first != pr[j + 1].first) flag1 = 1;
                if (d1[pr[j + 1].first]) flag2 = 1;
                ++j;
            }
            if (flag2 == 0) {
                if (flag1 == 0 && d2[pr[i].second] == 0) C++;
                else if (flag1 == 1 && d2[pr[i].second] == 1) B++;
            }
            i = j;
        }
        sort(pr + 1, pr + 1 + r, cmp1);
        for (int i = 1; i <= r; ++i) {
            int flag1 = 0, flag2 = d2[pr[i].second];
            int j = i;
            while (j < r && pr[j].first == pr[j + 1].first) {
                if (pr[j].second != pr[j + 1].second) flag1 = 1;
                if (d2[pr[j + 1].second]) flag2 = 1;
                ++j;
            }
            if (flag2 == 0) {
                if (flag1 == 1 && d1[pr[i].first] == 1) A++;
                //printf("%d %d\n", flag1, d1[pr[i].first]);
            }
            i = j;
        }
        static int ca = 0;
        printf("Case #%d: %d %d %d\n", ++ca, A, B, C);
    }
    return 0;
}