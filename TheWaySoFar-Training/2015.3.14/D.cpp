#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef unsigned int uint;

uint cur = 0, a, b, F[1 << 16], G[1 << 16], H[1 << 16];

uint nextRand16() {
    cur = cur * a + b;
    return cur / (1 << 16);
}

uint sF[1 << 16], sG[1 << 16],  sum[1 << 16];

int gett(int mask) {
    if (__builtin_popcount(mask) & 1) return 1;
    else return -1;
}

int main() {
    freopen("convolution.in", "r", stdin);
    freopen("convolution.out", "w", stdout);
    // freopen("1.txt", "r", stdin);
    int n, T;
    scanf("%d%d", &n, &T);
    scanf("%u%u", &a, &b);
    while (T--) {
        for (int i = 0; i < 1 << n; ++i) 
            F[i] = nextRand16();
        for (int i = 0; i < 1 << n; ++i) {
            G[i] = nextRand16();
        }
        for (int mask = 0; mask < 1 << n; ++mask) {
            sF[mask] = F[mask];
            sG[mask] = G[mask];
        }
        for (int j = 0; j < n; ++j)
            for (int mask = 0; mask < 1 << n; ++mask)
                if (mask >> j & 1) {
                    sF[mask] += sF[mask ^ (1 << j)];
                    sG[mask] += sG[mask ^ (1 << j)];
                }
        uint res = 0;
        for (int mask = 0; mask < 1 << n; ++mask)
            sum[mask] = 0;
        for (int mask = 0; mask < 1 << n; ++mask) {
            sum[mask] += sF[mask] * sG[mask];
        }
        for (int j = 0; j < n; ++j)
            for (int mask = 0; mask < 1 << n; ++mask)
                if (!(mask >> j & 1))
                    sum[mask ^ (1 << j)] -= sum[mask];
        //for (int mask = 1; mask < 1 << n; ++mask)
        //    for (int op = (mask - 1) & mask; ; op = (op - 1) & mask) {
        //        sum[mask] -= sum[op];
        //        if (op == 0) break;
        //    }
            for (int mask = 0; mask < 1 << n; ++mask)
                res += sum[mask] * (mask + 1), H[mask] = sum[mask];
            //for (int i = 0; i < 1 << n; ++i)
            //printf("%u%c", H[i], " \n"[i + 1 == (1 << n)]);
        //cout << 3 * 45526 + 113 * 25547 + 113 * 45526 << endl;
        printf("%u\n", res);
    }
    return 0;
}
