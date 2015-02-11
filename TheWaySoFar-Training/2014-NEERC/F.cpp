#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1005;
const int Q = 1e9 + 7;
int n;
string S , T;
vector<string> res;

void work() {
    cin >> S >> n;
    for (int i = 0 , j ; i < n ; ++ i) {
        cin >> T;
        for (j = 0 ; j < S.size() ; ++ j)
            if (S[j] != '*' && S[j] != T[j])
                break;
        if (j >= S.size())
            res.push_back(T);
    }
    cout << res.size() << endl;
    for (auto p : res)
        cout << p << endl;
}

int main() {
    freopen("fraud.in","r",stdin);
    freopen("fraud.out","w",stdout);
    work();
    return 0;
}
