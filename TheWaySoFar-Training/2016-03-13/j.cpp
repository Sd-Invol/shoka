#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1e7 + 5;

struct node {
    node *l , *r;
    int L , R , f;
    int l0 , l1;
    void black() {
        f = 1;
        l0 = 1 << 30 , l1 = L;
    }
    void pushdown();
    void pushup();
};

node T[N] , *root , *null;
int cnt;

node* newnode(int l , int r) {
    node *p  = &T[++ cnt];
    p->l = null; p->L = l;
    p->r = null; p->R = r;
    p->f = 0;
    p->l0 = l , p->l1 = 1 << 30;
    return p;
}
void node::pushdown() {
    if (f) {
        int mid = L + R >> 1;
        if (l == null) l = newnode(L , mid);
        if (r == null) r = newnode(mid + 1 , R);
        l->black();
        r->black();
        f = 0;
    }
}
void node::pushup() {
    int mid = L + R >> 1;
    l0 = min(l == null ? L : l->l0 , r == null ? mid + 1 :r->l0);
    l1 = min(l->l1 , r->l1);
}

void update(node *&p , int l , int r , int top , int bot) {
    if (p == null) p = newnode(l , r);
    if (top <= l && r <= bot) {
        // printf("-- %d %d\n" , l , r);
        p->black();
    } else {
        int mid = l + r >> 1;
        p->pushdown();
        if (top <= mid) update(p->l , l , mid , top , bot);
        if (bot > mid) update(p->r , mid + 1 , r, top , bot);
        p->pushup();
    }
}
void erase(node *&p , int l , int r , int x) {
    if (p == null) p = newnode(l , r);
    if (x <= l && r <= x) {
        p->l0 = l;
        p->l1 = 1 << 30;
    } else {
        int mid = l + r >> 1;
        p->pushdown();
        if (x <= mid) erase(p->l , l , mid , x);
        if (x > mid) erase(p->r , mid + 1 , r, x);
        p->pushup();
    }
}
int find0(node *&p , int l , int r , int x) {
    if (p == null) p = newnode(l , r);
    if (x <= l) {
        return p->l0;
    } else {
        int mid = l + r >> 1;
        p->pushdown();
        if (x <= mid) {
            int res = find0(p->l , l , mid , x);
            if (res != 1 << 30)
                return res;
        }
        return find0(p->r , mid + 1 , r, x);
    }
}
int find1(node *&p , int l , int r , int x) {
    if (p == null) p = newnode(l , r);
    if (x <= l) {
        return p->l1;
    } else {
        int mid = l + r >> 1;
        p->pushdown();
        if (x <= mid) {
            int res = find1(p->l , l , mid , x);
            if (res != 1 << 30)
                return res;
        }
        return find1(p->r , mid + 1 , r, x);
    }
}

int n;

int main() {

    null = &T[++ cnt];
    null->l0 = null->l1 = 1 << 30;
    root = null;
    int RR = 1e9;
    scanf("%d" , &n);

    for (int i = 0 ; i < n ; ++ i) {
        int x , p;
        scanf("%d" , &x);
        if (x < 0) {
            x = -x;
            erase(root , 0 , RR , x);
        } else {
            scanf("%d" , &p);
            int y = find0(root , 0 , RR , x);
            int w = find1(root , 0 , RR , y);
            w = min(y + p - 1 , w - 1);
            printf("%d %d\n" , y , w);
            update(root , 0 , RR , y , w);
        }
    }
    return 0;
}
