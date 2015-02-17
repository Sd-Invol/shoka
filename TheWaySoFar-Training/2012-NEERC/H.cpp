#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 300005;

int n;
char str[N];
map<LL , int> cnt;
void work() {
    scanf("%d%s" , &n , str);
    LL res = 0 , x = 0;
    ++ cnt[x];
    for (int i = 0 ; i < n ; ++ i) {
        if (islower(str[i]))
            x ^= (1LL << str[i] - 'a');
        else
            x ^= (1LL << str[i] - 'A' + 26);
        res += cnt[x];
        for (int j = 0 ; j < 52 ; ++ j)
            if (cnt.count(x ^ (1LL << j)))
                res += cnt[x ^ (1LL << j)];
        ++ cnt[x];
    }
    cout << res << endl;

}

int main() {
    freopen("hyperdrome.in" , "r" , stdin);
    freopen("hyperdrome.out" , "w" , stdout);
    work();
    return 0;
}
