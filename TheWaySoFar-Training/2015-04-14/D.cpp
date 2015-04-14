#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int ma[10] = {0, 1, 12, 123, 1234, 12345, 123456, 1234567, 12345678, 123456789};
char str[N];

void solve() {
    int n = strlen(str);
    assert(str[0] != '0');
    if (n == 1) {
        printf("%d\n", ma[str[0] - '0']);
        return ;
    }
    int ans[11];
    int K = (str[0] - '0'), L, mark = 0, C;
    for (L = 1; L <= 10; ++L)
        if (L < K) putchar(L + '0');
        else break;
    int last = 0;
    for (int i = 1; i < n; ++i)
        if (str[i] < str[i - 1]) {
            last = i;
        }
        else if (str[i] > str[i - 1]) break;
    n -= 1;
    if (last != 0) {
        for (int i = 1; i <= last; ++i) {
            int C = str[i] - '0';
            int P = str[i - 1] - '0';
            if (i == last) ++C;
            for (int j = C; j <= P; ++j)
                putchar('0' + j);
            for (int j = 0; j < 10; ++j)
                if (j < C || j > P)
                    putchar('0' + j);
        }
        n -= last;
    }
    else putchar(L + '0');
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 10; ++j)
            putchar(j + '0');
    puts("");
}

int main() {
    scanf("%s", str);
    solve();
    return 0;
}
