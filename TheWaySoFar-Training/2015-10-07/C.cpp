#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <queue>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        static int ca = 0;
        printf("Case #%d:\n", ++ca);
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        while (q--) {
            int x;
            scanf("%d", &x);
            int l = max(1, x - m);
            int r = min(n, x - 1);
            printf("%d\n", max(0, r - l + 1));
        }
    }
    return 0;
}