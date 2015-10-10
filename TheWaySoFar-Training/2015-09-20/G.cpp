#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
int n , m;

int bo[8][1 << 21];
int power[10], mx[10], mn[10];
int b[10], v[10];
int N = 7;

int main() {
    for (int N = 1; N < 8; ++N) {
        queue<int> que;
        int mask = 0;
        for (int i = 0; i < N; ++i)
            mask |= i << (3 * i);
        bo[N][mask] = 1;
        que.push(mask);
        while (!que.empty()) {
            int mask = que.front(); que.pop();
            //cout << mask << endl;
            for (int i = 0; i < N; ++i) {
                mx[i] = -1;
                mn[i] = 1 << 30;
            }
            // if (N == 3) cout << "---" << endl;
            for (int i = 0; i < N; ++i) {
                int x = (mask >> (3 * i)) & 7;
                mx[x] = max(mx[x], i);
                mn[x] = min(mn[x], i);
                //  if (N == 3) printf("%d %d\n", i, x);
            }
            //if (N == 3) cout << "----" << endl;
            for (int i = 0; i < N; ++i) {
                int mask1 = mask;
                int x = (mask >> (3 * i)) & 7;
                if (mn[x] != i) continue;
                if (x > 0 && mn[x - 1] > i)  {
                    mask1 ^= x << (3 * i);
                    mask1 ^= (x - 1) << (3 * i);
                    if (bo[N][mask1] == 0) {
                        bo[N][mask1] = bo[N][mask] + 1;
                        que.push(mask1);
                    }
                }
                mask1 = mask;
                if (x + 1 < N && mn[x + 1] > i) {
                    mask1 ^= x << (3 * i);
                    mask1 ^= (x + 1) << (3 * i);
                    if (bo[N][mask1] == 0) {
                        bo[N][mask1] = bo[N][mask] + 1;
                        que.push(mask1);
                    }
                }
            }
        }
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            b[i] = v[i];
        }
        sort(b, b + n);
        for (int i = 0; i < n; ++i)
            v[i] = lower_bound(b, b + n, v[i]) - b;
        int mask = 0;
        for (int i = 0; i < n; ++i)
            mask |= (i) << (3 * (v[i]));
        printf("%d\n", bo[n][mask] - 1);
    }
    return 0;
}
