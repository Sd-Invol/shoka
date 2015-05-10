#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e6 + 5;
int n, m, r;
int a[N], b[N * 2], bo[N], c[N * 2];

int check(int x) {
    int num = 0;
    memset(bo, 0, sizeof(bo));
    for (int i = 1; i < r && num < n; ++i) {
        if (!bo[i] && !bo[i + 1] && abs(a[i] - a[i + 1]) <= x) {
            b[num * 2 + 1] = a[i];
            b[num * 2 + 2] = a[i + 1];
            c[num * 2 + 1] = c[num * 2 + 2] = 1;
            bo[i] = bo[i + 1] = 1;
            ++num;
        }
    }
    if (num < n) return 0;
    num = 1;
    for (int i = 1; i <= r; ++i)
        if (!bo[i]) {
            if (a[i] < b[num]) return 0;
            if (++c[num] == m) {
                ++num;
            }
        }
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    r = n * m * 2;
    for (int i = 1; i <= r; ++i)
        scanf("%d", &a[i]);
    sort(a + 1, a + 1 + r);
    int head = 0, tail = a[r] - a[1];
    while (head < tail - 1) {
        int mid = head + tail >> 1;
        if (check(mid)) tail = mid;
        else head = mid;
    }
    if (check(head)) tail = head;
    printf("%d\n", tail);
    return 0;
}
