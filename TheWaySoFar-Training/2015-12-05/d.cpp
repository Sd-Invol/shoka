#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char str1[1005], str2[1005];

int f[1005][1005];

void print(int n, int m) {
    if (n == 0 && m == 0) return ;
    if (n > 0 && m > 0 && str1[n] == str2[m] &&
        f[n][m] == f[n - 1][m - 1] + 1) {
        print(n - 1, m - 1);
        putchar(str1[n]);
        return ;
    }
    if (n == 0 || (m > 0 && f[n][m] == f[n][m - 1])) {
        print(n, m - 1);
        putchar(str2[m]);
        return ;
    }
    if (m == 0 || (n > 0 && f[n][m] == f[n - 1][m])) {
        print(n - 1, m);
        putchar(str1[n]);
        return ;
    }
}

int main() {
    scanf("%s", str1 + 1);
    scanf("%s", str2 + 1);
    int n = strlen(str1 + 1);
    int m = strlen(str2 + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (str1[i] == str2[j]) {
                f[i][j] = f[i - 1][j - 1] + 1;
            }
            f[i][j] = max(f[i][j], f[i - 1][j]);
            f[i][j] = max(f[i][j], f[i][j - 1]);
        }
    
    print(n,);
    puts("");
    return 0;
}
