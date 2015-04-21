#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
const int N = 1e6 + 5;

char str[N];
int S[N * 2], T[N], n;
vector<pair<int, int> > LE[N];

int gett(char ch) {
    if (ch == 'a') return 0;
    if (ch == 'b') return 1;
    if (ch == 'c') return 2;
}

int max1[N];
int r[N][3], bo[N][3];

int work() {
    static int fr[3];
    for (int i = n * 2 - 1; i >= 0; --i) {
        fr[S[i]] = i;
        if (i < n && T[i] == '*') {
            for (int j = 0; j < 3; ++j) 
                r[i][j] = fr[j] - i;
        }
    }
    memset(max1, 0, sizeof(max1));
    for (int i = 0; i < n << 1; ++i) {
        fr[S[i]] = i;
        
        if (i >= n && T[i - n] == '*') {
            for (int j = 0; j < 3; ++j) {
                int p = i - fr[j];
                if (p != 0)
                    max1[p - 1] = max(max1[p - 1], r[i - n][j]);
                // printf("%d %d\n", p, r[i - n][j]);
            }
        }
    }
    for (int j = n - 1; j >= 0; --j)
        max1[j] = max(max1[j + 1], max1[j]);
    int ans = 1 << 30;
    for (int i = 0; i <= n; ++i) {
        int res = max1[i];
        if (res == 0) ans = min(ans, i);
        else ans = min(ans, i * 2 + res);
        //printf("!%d %d\n", i, res);
        }
    return ans;
}

int main() {
    scanf("%s", str);
    n = strlen(str);
 
    for (int i = 0; i < n << 1; ++i) S[i] = gett(str[i % n]);
    scanf("%s", str);
    
    for (int i = 0; i < n; ++i) T[i] = str[i];
    int ans = work();
    reverse(S, S + n * 2);
    reverse(T, T + n);
    ans = min(ans, work());
    printf("%d\n", ans);
    return 0;
}
