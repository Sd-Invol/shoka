#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
#include <cmath>
#include <set>
#include <map>
using namespace std;

int f[2][21][21][21][21];
int a[205];
int A, B;

int b[1005], c[1005];
int bo[205];

int main() {
    int n;
    scanf("%d%d%d", &n, &A, &B);
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
    for (int i = 1; i <= n; ++i) {
        a[i] = b[i] + c[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        while (a[i] > 0) {
            memset(bo, 0, sizeof(bo));
            --a[i];
            ++ans;
            int t = A - 1;
            bo[i] = 1;
            for (int j = i + 1; j < i + B && t > 0; ++j)
                if (a[j] == 2) {
                    --a[j];
                    bo[j] = 1;
                    --t;
                }
            for (int j = i + 1; j < i + B && t > 0; ++j)
                if (a[j] == 1 && !bo[j]) {
                    --a[j];
                    --t;
                }
        }
    printf("%d\n", ans);
    return 0;
}