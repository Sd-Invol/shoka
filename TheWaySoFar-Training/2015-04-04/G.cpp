#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

const int N = 355;

char str[N];

string find(int l, int r) {
    if (l > r) return "";
    if (str[l] == '*') return find(l + 1, r);
    //printf("%d %d\n", l, r);
    if (l == r) {
        string T = "";
        if (str[l] == '$') return "";
        T += str[l];
        return T;
    }
    int sum = 0;
    for (int i = l; i <= r; ++i) {
        if (str[i] == '(') ++sum;
        if (str[i] == ')') --sum;
        if (sum == 0) {
            if (str[i] == '|') {
                string S, T;
                S = find(l, i - 1);
                T = find(i + 1, r);
                if (S.size() < T.size()) return S;
                else if (S.size() > T.size()) return T;
                return min(S, T);
            }
        }
    }
    for (int i = l; i < r; ++i) {
        if (str[i] == '(') ++sum;
        if (str[i] == ')') --sum;
        if (sum == 0) {
            if (str[i + 1] != '*')
                return find(l, i) + find(i + 1, r);
        }
    }
    if (str[r] == '*') return "";
    if (str[l] == '(') return find(l + 1, r - 1);
    assert(0);
}

void work() {
    scanf("%s", str);
    int n = strlen(str);
    string ans = find(0, n - 1);
    if (ans.size() == 0) puts("$");
    else cout << ans << endl;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) work();
    return 0;
}
