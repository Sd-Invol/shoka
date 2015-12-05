#include <cstdio>
#include <algorithm>
using namespace std;
int n , m , k;
int T[10][10];
int a[10];

int dfs(int x) {
    if (x >= 9) {
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if ((a[i] * a[j] - 1 + 9) % 9 + 1 != T[i][j])
                    return 0;
        return 1;
    }
    for (int i = 0; i < 9; ++i)
        if ((i * i - 1 + 9) % 9 + 1 == T[x][x]) {
            a[x] = i;
            // printf("%d %d\n", x, i);
            if (dfs(x + 1)) return 1;
        }
    return 0;
}

int main() {
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            scanf("%d", &T[i][j]);
        }
    if (!dfs(0)) {
        puts("No solution");
    }
    else {
        int tmp = 0;
        for (int i = 0; i < 9; ++i) {
            while (a[i] <= tmp) a[i] += 9;
            tmp = a[i];
            printf("%d%c", a[i], " \n"[i == 8]);
        }
    }
    return 0;
}
