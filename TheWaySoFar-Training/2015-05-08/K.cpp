#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 35;
string Pre , In , Post;
struct state {
    string pre , in , post;
    state () {}
    state (string _pre , string _in , string _post) {
        pre = _pre;
        in = _in;
        post = _post;
    }
    string operator [] (int x) const {
        if (x == 0)
            return pre;
        if (x == 1)
            return in;
        return post;
    }
    string& operator [] (int x) {
        if (x == 0)
            return pre;
        if (x == 1)
            return in;
        return post;
    }
    bool operator < (const state& R) const {
        if (pre != R.pre)
            return pre < R.pre;
        if (in != R.in)
            return in < R.in;
        return post < R.post;
    }
};
string Name[3] = {"Pre" , "In" , "Post"};
int logic[3][2];
state Begin;
set<state> vis;
map<state , state> Hash;

int mask(const string& S) {
    int res = 0;
    for (int i = 0 ; i < S.size() ; ++ i)
        res |= 1 << S[i] - 'A';
    return res;
}

bool get(const state& x , state& res) {
    if (vis.count(x)) {
        if (!Hash.count(x))
            return 0;
        res = Hash[x];
        return 1;
    }
    vis.insert(x);
    int n = max(x[0].size() , max(x[1].size() , x[2].size()));
    if (n == 0) {
        res = Hash[x] = x;
        return 1;
    }
    if (x[0].size() && x[2].size() && x[0][0] != x[2][n - 1])
        return 0;
    bool upd = 0;
    for (int Ls = 0 ; Ls < n ; ++ Ls) {
        int Rs = n - Ls - 1;
        char root;
        if (x[0].size()) root = x[0][0];
        if (x[1].size()) root = x[1][Ls];
        if (x[2].size()) root = x[2][n - 1];
        if (x[0].size() && root != x[0][0]) continue;
        if (x[1].size() && root != x[1][Ls]) continue;
        if (x[2].size() && root != x[2][n - 1]) continue;
        string L[3] , R[3];
        if (!x[0].empty()) {
            L[0] = x[0].substr(1 , Ls);
            R[0] = x[0].substr(1 + Ls , Rs);
        }
        if (!x[1].empty()) {
            L[1] = x[1].substr(0 , Ls);
            R[1] = x[1].substr(1 + Ls , Rs);
        }
        if (!x[2].empty()) {
            L[2] = x[2].substr(0 , Ls);
            R[2] = x[2].substr(Ls , Rs);
        }
        state Left , Right;
        bool vaild = 1;
        for (int i = 0 ; i < 3 ; ++ i) {
            int j = logic[i][0];
            if (Left[j].empty())
                Left[j] = L[i];
            else if (!L[i].empty() && Left[j] != L[i])
                vaild = 0;
        }
        for (int i = 0 ; i < 3 ; ++ i)
            for (int j = i + 1 ; j < 3 ; ++ j)
                if (!Left[i].empty() && !Left[j].empty() && mask(Left[i]) != mask(Left[j]))
                    vaild = 0;
        if (!vaild) continue;
        for (int i = 0 ; i < 3 ; ++ i) {
            int j = logic[i][1];
            if (Right[j].empty())
                Right[j] = R[i];
            else if (!R[i].empty() && Right[j] != R[i])
                vaild = 0;
        }
        for (int i = 0 ; i < 3 ; ++ i)
            for (int j = i + 1 ; j < 3 ; ++ j)
                if (!Right[i].empty() && !Right[j].empty() && mask(Right[i]) != mask(Right[j]))
                    vaild = 0;
        if (!vaild) continue;
        state resL , resR;
        if (!get(Left , resL)) continue;
        if (!get(Right , resR)) continue;
        state ans;
        ans[0] = root + resL[0] + resR[0];
        ans[1] = resL[1] + root + resR[1];
        ans[2] = resL[2] + resR[2] + root;
        if (!upd) {
            upd = 1;
            res = ans;
        } else {
            res = min(res , ans);
        }
    }
    if (upd) {
        Hash[x] = res;
    }
    return upd;
}

void dfs(int k , int sa , int sb , int sc) {
    if (k == 6) {
        vis.clear();
        Hash.clear();
        state res;
        if (get(Begin , res)) {
            for (int i = 0 ; i < 3 ; ++ i)
                for (int j = 0 ; j < 2 ; ++ j)
                    printf("%s%c" , Name[logic[i][j]].c_str() , " \n"[i == 2 && j == 1]);
            cout << res[0] << endl;
            cout << res[1] << endl;
            cout << res[2] << endl;
        }
    } else {
        if (sa < 2) {
            logic[k / 2][k % 2] = 0;
            dfs(k + 1 , sa + 1 , sb , sc);
        }
        if (sb < 2) {
            logic[k / 2][k % 2] = 1;
            dfs(k + 1 , sa , sb + 1 , sc);
        }
        if (sc < 2) {
            logic[k / 2][k % 2] = 2;
            dfs(k + 1 , sa , sb , sc + 1);
        }
    }
}

int main() {
    cin >> Pre >> In >> Post;
    Begin = state(Pre , In , Post);
    dfs(0 , 0 , 0 , 0);
    return 0;
}
