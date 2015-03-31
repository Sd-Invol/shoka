#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e6 + 5;
char str[N];

int extend[N];
typedef long long LL;

void work() {
    scanf("%s", str + 1);
    int n = strlen(str + 1);
    for (int i = 0; i <= n; ++i)
        extend[i] = 0;
    for (int i = 2, j = 2, a = 1; i <= n; ++i) {
        int k = i - j + 1;
        int p = min(extend[k], a - i + 1);
        if (p < 0) p = 0;
        while (i + p <= n && str[p + 1] == str[i + p]) ++p;
        extend[i] = p;
        if (i + extend[i] >= extend[j] + j) {
            j = i;
            a = i + extend[i] - 1;
        }
    }
    extend[1] = n;
    //for (int i = 1; i <= n; ++i)
    //    printf("%d %d\n", i, extend[i]);
    int K;
    for (K = 2; ; ++K) {
        int flag = 0;
        LL t = K - 1;
        while (!flag) {
            if (t + 1 >= n) break;
            for (int i = 1; i <= n; i += t + 1) {
                int len = extend[i];
                if (len >= t) continue;
                if (i + len - 1 == n) continue;
                flag = 1;
            }
            t = K * t + K - 1;
        }
        if (!flag) break;
    }
    printf("%d\n", K);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) work();
    return 0;
}
