#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned int UI;

int a[32];

void add_hash(int a[], int k) {
    int hash[32];
    memcpy(hash, a, sizeof(hash));
    for (int i = 0, j = 0; i < 32; ++i) {
        if (i < k) a[i] = hash[i];
        else {
            if (1 == (hash[i] ^ j))
                a[i] = a[i - k] ^ 1;
            else a[i] = a[i - k];
            j = (j + a[i - k] + a[i]) / 2;
        }
    }
}

void xor_hash(int a[], int k) {
    int hash[32];
    memcpy(hash, a, sizeof(hash));
    reverse(hash, hash + 32);
    for (int i = 0; i < 32; ++i)
        if (i < k) a[i] = hash[i];
        else {
            if (hash[i] == 1)
                a[i] = a[i - k] ^ 1;
            else a[i] = a[i - k];
        }
    reverse(a, a + 32);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        UI x;
        scanf("%u", &x);
        for (int j = 0; j < 32; ++j)
            a[j] = (x >> j) & 1;
        add_hash(a, 16);
        xor_hash(a, 11);
        add_hash(a, 3);
        xor_hash(a, 6);
        add_hash(a, 10);
        x = 0;
        for (int j = 0; j < 32; ++j)
            x |= ((UI)a[j]) << j;
        printf("%u\n", x);
    }
    return 0;
}
