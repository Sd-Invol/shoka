#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 105;

int ans[N], d[N];

int main() {
    int n, k, p;
    scanf("%d%d%d", &n, &k, &p);
    if (p == 100) {
        printf("1\n0 1");
        for (int i = 3; i <= n; ++i)
            printf(" %d", 0);
        puts("");
        return 0;
    }
    if (p >= 50) {
        printf("0\n");
        return 0;
    }
    int a = 100 - p * 2;
    int b = 100;
    int tt = __gcd(a, b);
    a /= tt;
    b /= tt;
    bool flag = 1;
    d[1] = a;
    b -= a;
    for (int i = 2; i <= n; ++i)
        if (b) {
            if (b > k) {
                b -= k;
                d[i] = k;
            }
            else {
                d[i] = b;
                b = 0;
            }
        }
    if (b) flag = 0;
    for (int i = 1; i <= n; ++i) {
        if (d[i] > k) {
            flag = 0;
            break;
        }
    }
    if (flag == 0) {
        puts("0");
    }
    else {
	printf("1\n");
        for (int i = 1; i <= n; ++i)
            printf("%d%c", d[i], i == n ? '\n' : ' ');
	}
    return 0;
}
