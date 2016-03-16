#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1000005;

char str[N];
int len , top , ln , rn;
char S[N] , L[N] , R[N];

int main() {
    char c;
    while (c = getchar() , c != '\n' && c != -1 && c != '\r') {
        str[len ++] = c;       
        if (c == '(' || c == '[' || c == '{') {
            S[top ++] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            char p;
            if (c == ')') p = '(';
            if (c == ']') p = '[';
            if (c == '}') p = '{';            
            if (!top) {                
                L[ln ++] = p;                
            } else {
                if (S[top - 1] != p) {
                    puts("NIE");
                    return 0;
                }
                -- top;
            }
        }
    }
    str[len] = 0;
    L[ln] = 0;
    reverse(L , L + ln);    
    printf("%s%s" , L , str);
    for (int i = top - 1 ; i >= 0 ; -- i) {
        c = S[i];  char p;       
        if (c == '(') p = ')';
        if (c == '[') p = ']';
        if (c == '{') p = '}';
        putchar(p);
    }
    puts("");
    return 0;
}
