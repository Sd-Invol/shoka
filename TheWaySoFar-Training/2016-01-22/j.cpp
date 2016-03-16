#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e6 + 5;

pair<int, int> pr[N];

int sqrt0[N];
int sum[N];
int nex[N];
int f[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i * i < N; ++i)
        sqrt0[i * i] = i;
    for (int i = N - 2; i >= 0; --i)
        if (sqrt0[i] == 0)
            sqrt0[i] = sqrt0[i + 1];
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &pr[i].first);
        pr[i].second = i;
    }
    sort(pr + 1, pr + 1 + n);
    vector<pair<int, int> > ver;
    for (int i = 1; i <= n; ++i) {
        int l = i, r = pr[i].second;
        if (l > r) swap(l, r);
        sum[l]++;
        sum[r]--;
    }
    for (int i = 1; i <= n; ++i) {
        sum[i] += sum[i - 1];
    }
    for (int i = n, j = n + 1; i >= 0; --i) {
        if (sum[i] == 0) j = i;
        nex[i] = j;
    }
    memset(f, 63, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; ++i) {
        if (sum[i - 1] == 0) f[i] = f[i - 1];
        for (int j = 2, low = 1; ; ++j) {
            int upper = j * j;
            int L = max(0, i - upper);
            int R = min(i - 1, i - low);
            if (nex[L] <= R) {
                f[i] = min(f[i], f[nex[L]] + j);
                //printf("%d %d %d\n", i, nex[L]);
            }
            if (j * j >= i) break;
            low = upper + 1;
        }
    }
    cout << f[n] << endl; 
}
