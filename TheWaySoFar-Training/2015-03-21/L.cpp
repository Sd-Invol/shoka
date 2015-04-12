#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

int n;
LL m;

int main() {
    cin >> n >> m;
    LL s = 1;
    for (int i = 1 ; i <= n ; ++ i) {
        s *= (2 * i);
    }
    //cout << s << endl;
    if (n > 16 || m <= s)
        puts("Harshat Mata");
    else
        puts("Nope");
    return 0;
}
