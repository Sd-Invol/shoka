#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
using namespace std;
const int N = 10005;
typedef long long LL;
char mode[20];
char a[10][10] , op[N];
int L , comb , point , step , bonus , Round;
int Lev , mxc;
LL score;

void notcmp() {
    puts("Game log is not complete");
    exit(0);
}
void error(int T) {
    printf("Error in game log at position %d\n" , T);
    exit(0);
}
void show() {
    for (int i = 1 ; i <= 8 ; ++ i) {
        a[i][8] = 0;
        puts(a[i] + 1);
        a[i][8] = '.';
    }    
}

void gettile(char &c , int &y) {
    if (!op[point]) {
        notcmp();
    }
    c = op[point ++];
    if (!op[point]) {
        notcmp();
    }
    if (!isdigit(op[point])) {
        error(point + 1);
    }
    y = op[point ++] - '0';
}
int level(char c) {
    if (isupper(c))
        return c - 'A' + 1;
    else if (islower(c))
        return c - 'a' + 1;
    else
        return c - '0';
}
void bomb(char &c) {
    if (isupper(c))
        c = c - 'A' + 'a';
    else if (islower(c))
        c = c - 'a' + '1';    
}
bool bang[20][20];

void work() {
    // show(); puts("&&&&&&&&&&&&&&");
    int cnt = 0;
    do {
        for (int i = 1 ; i <= 7 ; ++ i) {
            int m = 8;
            for (int j = 8 ; j > 0 ; -- j) {
                if (a[j][i] != '.')
                    a[m --][i] = a[j][i];
            }
            while (m > 0) {
                a[m --][i] = '.';
            }
        }
        //show(); puts("233333333333333333333333333");
        memset(bang , 0 , sizeof(bang));
        cnt = 0;
        for (int i = 1 ; i <= 8 ; ++ i) {
            for (int j = 1 ; j <= 7 ; ++ j) {
                if (!isdigit(a[i][j]))
                    continue;
                int L = j , R = j;
                while (a[i][L] != '.')
                    -- L;
                while (a[i][R] != '.')
                    ++ R;
                if (R - L - 1 == level(a[i][j])) {
                    bang[i][j] = 1;
                    ++ cnt;
                    continue;
                }
                L = i , R = i;
                while (a[L][j] != '.')
                    -- L;
                while (a[R][j] != '.')
                    ++ R;
                if (R - L - 1 == level(a[i][j])) {
                    bang[i][j] = 1;
                    ++ cnt;
                }
            }
        }
        if (cnt) {
            ++ comb;
            mxc = max(mxc , comb);
            LL delta = (7LL * comb * comb * comb + 72LL * comb * comb - 73LL * comb + 36) / 6;
            score += cnt * delta;
        }
        for (int i = 1 ; i <= 8 ; ++ i)
            for (int j = 1 ; j <= 7 ; ++ j) {
                if (bang[i][j]) {
                    a[i][j] = '.';
                    bomb(a[i - 1][j]);
                    bomb(a[i + 1][j]);
                    bomb(a[i][j - 1]);
                    bomb(a[i][j + 1]);                    
                }
            }        
    } while (cnt > 0);
}
/*
Score: 60
Longest chain: 2
Level reached: 1
.e.....
.e.....
.e.....
.e.....
.e.....
.e.....
.e.....
.e..7..
 */


void gg(bool dead = 0) {
    if (point < L) {
        error(point + 1);
    }
    if (dead)
          puts("Game is over!");
    printf("Score: %lld\n" , score);
    printf("Longest chain: %d\n" , mxc);
    printf("Level reached: %d\n" , Lev);
    show();
    exit(0);
}

int main() {
    scanf("%s" , mode);
    scanf("%s" , mode);
    Lev = 1;
    if (*mode == 'H') {
        bonus = 17000;
        step = 5;
    } else {
        bonus = 7000;
        step = 30;
    }
    memset(a , '.' , sizeof(a));
    for (int i = 1 ; i <= 8 ; ++ i) {
        scanf("%s" , a[i] + 1);
        a[i][8] = '.';
    }
    scanf("%s" , op);
    L = strlen(op);

    point = 0;

    while (point < L) {
        //printf("L: %d S: %lld\n" , Lev , score);
        comb = 0;
        ++ Round;
        int y; char c;
        gettile(c , y);        
        a[1][y] = c;
        if (a[2][y] != '.') {
            gg(1);
            break;
        }
        work();

        if (Round == step) {
            ++ Lev;
            score += bonus;
            Round = 0;
            step = max(5 , step - 1);
            if (point + 6 >= L)
                notcmp();
            for (int i = 1 ; i <= 8 ; ++ i)
                for (int j = 1 ; j <= 7 ; ++ j)
                    a[i][j] = a[i + 1][j];            
            for (int i = 1 ; i <= 7 ; ++ i) {
                a[8][i] = op[point ++];
            }for (int i = 1 ; i <= 7 ; ++ i) {
                if (a[1][i] != '.') {
                    gg(1);                    
                }
            }
            
            //show();
            work();
        }
    }
    gg(0);
    
    return 0;
}
