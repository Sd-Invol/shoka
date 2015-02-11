#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 50005;
const int Q = 1e9 + 7;
int n;
map<string , int> h;
int f[N] , p[N];
char str[N] , word[N] , name[N];

void print(int x) {
    if (!x) return;
    print(p[x]);
    cout << x << ' ';
}

void work() {
    pair<int , int> res(-1 , -1);
    scanf("%d\n" , &n);
    for (int i = 1 ; i <= n ; ++ i) {
        gets(str);
        int L = strlen(str) , l = 0;
        while (str[l] != ':')
            name[l] = str[l] , l ++;
        name[l] = 0;
        l += 2;
        while (l < L) {
            sscanf(str + l , "%s" , word);
            l += strlen(word) + 1;
            if (*word == '@' && strcmp(word , name) && h.count(word)) {
                int x = h[word];
                if (x != i && f[x] > f[i]) {
                    f[i] = f[x];
                    p[i] = x;
                }
            }
        }
        res = max(res , make_pair(++ f[i] , i));
        if (f[i] > f[h[name]])
            h[name] = i;
    }
    cout << res.first << endl;
    print(res.second);
}

int main() {
    freopen("join.in" , "r" , stdin);
    freopen("join.out" , "w" , stdout);
    work();
    return 0;
}
