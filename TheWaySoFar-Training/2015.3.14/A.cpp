#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

map<string , int> c , n;
char str[5000];
int a[5][2] , b[5][2];
bool f[5];
int s[5];
char N[20][20] = {
    "Barabashka",
"book",
"chair",
"mouse",
    "bottle"
};
char C[20][20] = {
    "white",
"blue",
"red",
"gray",
    "green"
};

int main() {
    freopen("barabashka.in", "r", stdin);
    freopen("barabashka.out", "w", stdout);
    n["Barabashka"] = 0;
    n["book"] = 1;
    n["chair"] = 2;
    n["mouse"] = 3;
    n["bottle"] = 4;

    c["white"] = 0;
    c["blue"] = 1;
    c["red"] = 2;
    c["gray"] = 3;
    c["green"] = 4;

    for (int i = 0 ; i < 5 ; ++ i) {
        gets(str);
        int len = strlen(str);
        for (int j = 0 , q = 0 , w = 0; j < len ; ++ j) {
            int k = j;
            string S = "";
            while (k < len && isalpha(str[k]))
                S += str[k ++];
            //cout << S << endl;
            if (c.count(S))
                a[i][q ++] = c[S];
            if (n.count(S))
                b[i][w ++] = n[S];
            j = k;
        }
        int x;
        if (a[i][0] == b[i][0])
            x = a[i][0];
        else if (a[i][1] == b[i][1])
            x = a[i][1];
        else
            x = 10 - a[i][0] - a[i][1] - b[i][0] - b[i][1];
        cout << C[x] << ' ' << N[x] << endl;
    }
    return 0;
}
