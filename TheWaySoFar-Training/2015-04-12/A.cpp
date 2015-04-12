#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 15;

char c[N][N] , s[N][N];
vector<string> res;

int type(char *S) {
    if (isdigit(*S)) return 0;
    if (isalpha(*S)) return 1;
    if (*S == '.') return 2;
    return -1;
}

int to(string S) {
    if (S == ".") return 1;
    if (S == "..") return 2;
    if (S == "...") return 3;
    if (S == "....") return 4;
    if (S == ".....") return 5;
    if (S == "......") return 6;

    if (S == "I") return 1;
    if (S == "II") return 2;
    if (S == "III") return 3;
    if (S == "IV") return 4;
    if (S == "V") return 5;
    if (S == "VI") return 6;

    if (S == "1") return 1;
    if (S == "2") return 2;
    if (S == "3") return 3;
    if (S == "4") return 4;
    if (S == "5") return 5;
    if (S == "6") return 6;
    return -1;
}

void work() {
    int i , j;
    for (i = 0 ; i < 3 ; ++ i) {
        scanf("%s%s" , c[i] , s[i]);
    }
    if (*s[0] == '.' && *s[1] == '.' && *s[2] == '.')
        res.push_back("John");
    if (!isalpha(*s[0]) && !isalpha(*s[1]) && !isalpha(*s[2]))
        res.push_back("David");
    if (*c[0] == 'W' && *c[1] == 'W' && *c[2] == 'W')
        res.push_back("Peter");
    if ((*c[0] == 'B' || *c[0] == 'W') && (*c[1] == 'B' || *c[1] == 'W') && (*c[2] == 'B' || *c[2] == 'W'))
        res.push_back("Robert");
    for (i = 0 ; i < 3 ; ++ i) {
        j = to(s[i]);
        if (j % 2 == 1 && *c[i] != 'W') break;
        if (j % 2 == 0 && *c[i] != 'B') break;        
    }
    if (i >= 3)
        res.push_back("Mark");
    for (i = 0 ; i < 3 ; ++ i) {
        j = to(s[i]);
        if ((j == 2 || j == 3 || j == 5) && !isdigit(*s[i]))
            break;
        if ((j != 2 && j != 3 && j != 5) && isdigit(*s[i]))
            break;
        
    }
    if (i >= 3)
        res.push_back("Paul");
    if (*c[0] == *c[1] && *c[1] == *c[2] && *c[0] != 'B' && *c[0] != 'W')
        res.push_back("Patrick");
    for (i = 0 ; i < 3 ; ++ i) {
        j = to(s[i]);
        if (isalpha(*s[i]) && *c[i] != 'Y')
            break;        
    }
    if (i >= 3)
        res.push_back("Jack");
    if (*c[0] != *c[1] && *c[1] != *c[2] && *c[0] != *c[2])
        res.push_back("Max");
    bool f = 0;
    for (i = 0 ; i < 3 ; ++ i)
        for (j = i + 1 ; j < 3 ; ++ j) {
            if (type(s[i]) == type(s[j])) {
                if (*c[i] != *c[j])
                    f = 1;
            } else {
                if (*c[i] == *c[j])
                    f = 1;            
            }
        }
    if (!f)
        res.push_back("Alex");
    for (i = 0 ; i < res.size() ; ++ i) {
        cout << res[i];
        cout << " \n"[i + 1 == res.size()];
    }
    
    
}

int main() {
    work();
    return 0;
}
