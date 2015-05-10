#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5 + 5;

int a[4][N], num[100];
int n;

void ee() {
    for (int i = 1; i <= n; ++i) {
        int flag = 0;
        for (int j = 0; j < 4; ++j)
            if (a[j][i]) ++flag;
        if (flag == 1) {
            for (int j = 0; j < 4; ++j) {
                if (a[j][i] > 0) {
                    --num[a[j][i]];
                    a[j][i] = 0;
                }
            }
        }
    }
}

int check() {
    ee();
    while (1) {
        int K = 0;
        for (int i = 1; i <= 52; ++i) {
            int j = i;
            if (j <= 26) j += 26;
            else j -= 26;
            if (num[i] > 0 && num[j] == 0) {
                K = i;
            }
        }
        if (K == 0) break;
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < 4; ++j)
                if (a[j][i] == K) {
                    a[j][i] = 0;
                    num[K] --;
                }
        ee();
    }
    for (int i = 1; i <= 52; ++i)
        if (num[i] > 0) return 0;
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        char str[20];
        scanf("%s", str);
        int m = strlen(str);
        for (int k = 0; k < m; k += 2)
            if (isupper(str[k])) {
                int p0 = str[k] - 'A' + 1;
                int p1 = p0 + 26;
                if (str[k + 1] == '+') {
                    a[k / 2][i] = p0;
                    ++num[p0];
                }
                else {
                    a[k / 2][i] = p1;
                    ++num[p1];
                }
            }
    }
    if (check()) puts("bounded");
    else puts("unbounded");
    return 0;
}
