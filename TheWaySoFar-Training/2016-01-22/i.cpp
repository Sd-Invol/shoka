#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>
using namespace std;
const int N = 100005;
char str[N];
vector<string> res;

map<int , string> S[26][26];
map<int , int> cnt[26][26];

int main() {
    while (~scanf("%s" , str)) {
        int L = strlen(str);
        if (L < 4)
            res.push_back(str);
        else {
            int a = str[0] - 'a';
            int b = str[L - 1] - 'a';
            if (S[a][b][L] == str) {
                sprintf(str , "%c%d%c" , 'a' + a , L - 2 ,'a' + b);
                res.push_back(str);
            } else {
                if (!cnt[a][b][L]) {
                    ++ cnt[a][b][L];
                    S[a][b][L] = str;
                } else {
                    ++ cnt[a][b][L];
                    S[a][b][L] = "";
                }
                res.push_back(str);
            }
        }
    }
    for (int i = 0 ; i < (int)res.size() ; ++ i)
        printf("%s%c" , res[i].c_str() , " \n"[i + 1 == res.size()]);
    return 0;
}
