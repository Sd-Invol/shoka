#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int N = 1e6 + 5;
typedef unsigned long long ULL;
const int P = 1e4 + 7;

char str[N];
ULL a[N];

int uptolower(int ch) {
    if (isupper(ch)) return ch - 'A' + 'a';
    else return ch;
};

map<ULL, vector<int> > ext;
int bo[N];

int main() {
    int n;
    scanf("%d", &n);
    int r = 0;
    gets(str);
    for (int i = 1; i <= n; ++i) {
        gets(str);
        //scanf("%s", str);
        int m = strlen(str);
        int p = 0;
        while (p < m) {
            while (p < m && !isalpha(str[p])) ++p;
            if (p >= m) break;
            a[r] = 0;
            while (p < m && isalpha(str[p])) {
                a[r] = a[r] * P + uptolower(str[p]);
                ++p;
            }
            ext[a[r]].push_back(r);
            ++r;
            bo[r - 1] = 1;
        }
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%s", str);
        int m = strlen(str);
        ULL p = 0;
        for (int i = 0; i < m; ++i)
            p = p * P + uptolower(str[i]);
        if (ext.count(p)) {
            vector<int> ver = ext[p];
            for (int i = 0; i < ver.size(); ++i)
                bo[ver[i]] = 0;
            ext.erase(p);
        }
    }
    int r0 = 0;
    for (int i = 0; i < r; ++i)
        if (bo[i]) a[r0++] = a[i];
    r = r0;
    map<ULL, int> num;
    for (int i = 0; i < r; ++i)
        num[a[i]]++;
    map<pair<ULL, ULL>, ULL> num1;
    for (int i = 0; i + 1 < r; ++i) {
        num1[make_pair(a[i], a[i + 1])]++;
        if (a[i] != a[i + 1]) num1[make_pair(a[i + 1], a[i])]++;
    }
    scanf("%d", &q);
    while (q--) {
        scanf("%s", str);
        int m = strlen(str);
        ULL t1 = 0, t2 = 0;
        for (int i = 0; i < m; ++i)
            t1 = t1 * P + uptolower(str[i]);
        scanf("%s", str);
        m = strlen(str);
        for (int i = 0; i < m; ++i)
            t2 = t2 * P + uptolower(str[i]);
        double A = (double)num[t1] / r;
        double B = (double)num[t2] / r;
        double AB = (double)num1[make_pair(t1, t2)] / (r - 1);
        printf("%.10f\n", AB / (A * B));
    }
    return 0;
}