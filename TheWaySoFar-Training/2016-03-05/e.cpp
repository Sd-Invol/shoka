#include <cstdio>
#include <cstring>
#include <vector>
const int N = 1e5 + 5;
using namespace std;

typedef long long LL;
int prime[N], bo[N], m;
int matrix[33][33];
int R[N], C[N];

int main() {
    freopen("elegant.in", "r", stdin);
    freopen("elegant.out", "w", stdout);
    for (int i = 2; i < N; ++i)
        if (!bo[i])  {
            prime[m++] = i;
            for (int j = i; j < N; j += i)
                bo[j] = 1;
        }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            matrix[i][j] = 1;
    int M = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int k = (i + j) % n;
            matrix[j][k] *= prime[M];
        }
        ++M;
        for (int j = 0; j < n; ++j) {
            int k = (i - j + n) % n;
            matrix[j][k] *= prime[M];
        }
        ++M;
    }
    if (n % 2 == 0) {
        int r = n / 2;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < r; ++j) {
                int k = (i + j) % n;
                matrix[j * 2][k] *= prime[M];
                k = (i + j + r) % n;
                matrix[j * 2 + 1][k] *= prime[M];
            }
            ++M;
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            printf("%d%c", matrix[i][j], " \n"[j + 1 == n]);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int p = 0;
            for (int x = matrix[i][j], k = 0; k < M; ++k)
                if (x % prime[k] == 0)
                    p |= 1 << k;
            R[i] |= p;
            C[i] |= p;
        }
    }
    //for (int i = 0; i < n; ++i)
    //    printf("%d %d\n", R[i], C[i]);
    return 0;
}
