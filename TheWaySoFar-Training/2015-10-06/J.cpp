#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>
typedef long long LL;
using namespace std;

const int N = 1000;
char a[N];
unordered_map<LL, int> f[100];
typedef unordered_map<LL, int>::iterator IT;
int b[1000];

int main() {
    //for (int i = 1; i <= 50; ++i) b[i] =i;
    //random_shuffle(b + 1, b + 1 + 50);
    //for (int i = 1; i <= 50; ++i)
    //    cout << b[i];
    //cout << endl;
    freopen("joke.in", "r", stdin);
    freopen("joke.out", "w", stdout);
    scanf("%s", a + 1);

    int len = strlen(a + 1);
    int n;
    if (len < 10) n = len;
    else n = (len - 9) / 2 + 9;
    f[0][0] = 1;
    for (int i = 0; i < len; ++i) {
        for (IT it = f[i].begin(); it != f[i].end(); ++it) {
            LL mask = it -> first;
            LL x = a[i + 1] - '0';
            //printf("%d %lld\n", i, mask);
            if (x != 0 && (mask >> (x - 1) & 1) == 0) {
                f[i + 1][mask | (1LL << (x - 1))] = 1;
            }
            x = x * 10 + a[i + 2] - '0';
            if (i + 2 <= len && x <= n && x > 0 && (mask >> (x - 1) & 1) == 0)
                f[i + 2][mask | (1LL << (x - 1))] = 2;
        }
    }
    vector<int> ver;
    int x = len;
    LL mask = (1LL << n) - 1;
    while (x > 0) {
        int l = f[x][mask];
        if (l == 1) {
            ver.push_back(a[x] - '0');
            //x --;
            mask ^= 1LL << (a[x] - '0' - 1);
            x--;
            continue;
        }
        else if (l == 2) {
            LL y = (a[x - 1] - '0') * 10 + a[x] - '0';
            ver.push_back(y);
            mask ^= 1LL << (y - 1);
            x -= 2;
        }
        else break;
    }
    reverse(ver.begin(), ver.end());
    for (int i = 0; i < ver.size(); ++i)
        printf("%d%c", ver[i], " \n"[i == (int)ver.size() - 1]);
    return 0;
}
