#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

const int N = 5e6 + 5;

char str[N];
int stack[N];
char str1[N];
int next[N];

int main() {
    while (scanf("%s", str + 1) == 1) {
        int n = strlen(str + 1);
        next[0] = next[1] = 0;
        for (int i = 2; i <= n; ++i) {
            int p = next[i - 1];
            while (p != 0 && str[p + 1] != str[i])
                p = next[p];
            if (str[p + 1] == str[i]) next[i] = p + 1;
            else next[i] = 0;
        }
        int head = 0;
        gets(str1);
        char ch;
        int p = 0;
        while (ch = getchar(), ch != '\n') {
            while (p != 0 && str[p + 1] != ch)
                p = next[p];
            if (str[p + 1] == ch) p = p + 1;
            else p = 0;
            stack[++head] = p;
            str1[head] = ch;
            if (p == n) {
                head = head - n;
                p = stack[head];
            }
            //printf("%c %d %d\n", ch, head, p);
        }
        str1[head + 1] = '\0';
        puts(str1 + 1);
    }
    return 0;
}