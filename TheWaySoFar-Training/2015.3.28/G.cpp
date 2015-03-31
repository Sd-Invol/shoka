#include <bits/stdc++.h>
using namespace std;
const int N = 20005;
int n = 20000 , m = 50;
char str[55];
string s[N];
map< string , int > pre[55];
int nxt[N] , len[N] , deg[N];
bool f[N];
int main() {
    freopen("genome.in","r",stdin);
    freopen("genome.out","w",stdout);    
    int i , j , k , x , y;
    for (i = 0 ; i < n ; ++ i) {
        gets(str);
        s[i] = str;
    }
    sort(s , s + n);
    n = unique(s , s + n) - s;
    for (i = 0 ; i < n ; ++ i) {
        for (j = 1 ; j < m ; ++ j) 
            pre[j][s[i].substr(0 , j)] = i;                
    }
    memset(nxt , -1 , sizeof(nxt));
    for (i = 0 ; i < n ; ++ i) {
        for (j = m - 1 ; j >= 1 ; -- j) {
            string t = s[i].substr(m - j , j);
            if (pre[j].count(t)) {
                k = pre[j][t];
                nxt[i] = k;
                len[i] = j;
                ++ deg[k];
                break;
            }
        }
    }
    //for (i = 0 ; i < n ; ++ i)
    //    printf("%d %d\n" , nxt[i] , len[i]);
    int res = 0;
    for (i = 0 ; i < n ; ++ i) {
        if (deg[i]) continue;
        x = i;
        string t = "";
        do {
            f[x] = 1;
            t += s[x].substr(0 , m - len[x]);
            x = nxt[x];
        } while (~x && !f[x]);
        if (t.size() < 500)
            continue;
        if (res + t.size() <= 50000) {
            res += t.size();
            for (j = 0 ; j < t.size() ; j += 5000) {
                string w = t.substr(j , min(5000 , (int)t.size() - j));
                if (w.size() >= 500)
                    cout << w << endl;
            }
        } else
            break;        
    }
    
    return 0;
}
