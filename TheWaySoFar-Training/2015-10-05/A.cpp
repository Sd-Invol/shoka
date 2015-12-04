#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

int num0[10005];
int num1[10005];

int main() {
    int n, m;
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int ch;
            while (ch = getchar(), ch != 'W' && ch != 'E');
            if (ch == 'E') num0[j]++;
            else num1[j]++;
        }
    }
    for (int j = 1; j <= m + 1; ++j) {
        num0[j] += num0[j - 1];
        num1[j] += num1[j - 1];
    }
    int L = 1 << 30, pos = -1;
    for (int i = 0; i <= m; ++i)
        if (num0[i] + num1[m] - num1[i] < L) {
            L = num0[i] + num1[m] - num1[i];
            pos = i;
        }
    printf("%d %d\n", pos, pos + 1);
    return 0;
}
