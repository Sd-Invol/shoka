#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N = 22;
typedef long long LL;
using namespace std;

int res[] = {-1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , 0 , 17 , -1 , 10 , -1 , 4 , -1 , 7 , -1 , -1 , -1 , 1 , -1 , 18 , -1 , 8 , -1 , 11 , -1 , -1 , -1 , 5 , -1 , 78 , -1 , 88 , -1 , 15 , -1 , -1 , -1 , 105 , -1 , 2 , -1 , 12 , -1 , 115 , -1 , -1 , -1 , 9 , -1 , 102 , -1 , 112 , -1 , 19 , -1 , -1 , -1 , 89 , -1 , 6 , -1 , 16 , -1 , 79 , -1 , -1 , -1 , 149 , -1 , 46 , -1 , 56 , -1 , 159 , -1 , -1 , -1 , 13 , -1 , 106 , -1 , 116 , -1 , 3 , -1 , -1 , -1 , 53 , -1 , 166 , -1 , 156 , -1 , 63 , -1};

int main() {
    int x , y;
    cin >> x >> y;
    cout << res[x * 10 + y] << endl;
    return 0;
}
