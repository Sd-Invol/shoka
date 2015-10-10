#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
typedef long long LL;
const int N = 100005;
int ca;
struct Node {
    Node *ch[2] , *p;
    int size , key;    
    Node () {
        size = key = 0;
    }
    bool d() {
        return this == p->ch[1];
    }
    void setc(Node *c , int d) {
        ch[d] = c;
        c -> p = this;
    }
    void pushup() {
        size = ch[0] -> size + ch[1] -> size + 1;
    }
}Tnull , *null = &Tnull;
Node mem[N] , *C = mem;
Node* newnode(int v) {
    Node *p = C ++;
    p->ch[0] = p->ch[1] = p->p = null;
    p->size = 1;
    p->key = v;
    return p;
}
void rotate(Node *t) {
    Node *p = t->p;
    int d = t->d();
    p->p->setc(t , p->d());
    p->setc(t->ch[!d] , d);
    t->setc(p , !d);
    p->pushup();
}
void splay(Node *t , Node *f = null) {
    while (t->p != f) {
        if (t->p->p == f)
            rotate(t);
        else {
            if (t->d() == t->p->d())
                rotate(t->p) , rotate(t);
            else
                rotate(t) , rotate(t);
        }
    }
    t->pushup();
}
Node* select(Node *t , int k) {
    while (1) {
        int c = 1 + t->ch[0]->size;
        if (k == c)
            return t;
        if (k > c)
            k -= c , t = t->ch[1];
        else
            t = t->ch[0];
    }
}
void split(Node *p , Node *&x , Node *&y , int K) {
    if (K == 0) {
        x = null , y = p;
    } if (K == p->size) {
        x = p , y = null;
    } else {
        y = select(p , K + 1);
        splay(y);
        x = y->ch[0];
        y->ch[0] = x->p = null;
        y->pushup();
    }
}
void merge(Node *&p , Node *x , Node *y) {
    if (x == null)
        p = y;
    else if (y == null)
        p = x;
    else {
        p = select(x , x->size);
        splay(p);
        p->setc(y , 1);
        p->pushup();
    }
}
int res[N] , ww;
void orz(Node *p) {
    if (p == null) return;
    orz(p->ch[0]);
    res[ww ++] = p->key;
    orz(p->ch[1]);    
}

int n;
pair<int , int> a[N];
void work() {
    printf("Case #%d: " , ++ ca);
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &a[i].first , &a[i].second);       
    }
    int cnt = 0;
    Node *root = null;
    C = mem;
    sort(a , a + n);
    for (int i = n - 1 ; i >= 0 ; -- i) {        
        if (a[i].second < 0 || a[i].second > cnt) {
            puts("impossible");
            return;
        }
        int K = min(a[i].second , cnt - a[i].second);
        Node *x , *y;
        split(root , root , x , K);
        y = newnode(a[i].first);
        merge(root , root , y);
        merge(root , root , x);
        ++ cnt;
    }
    ww = 0;
    orz(root);
    for (int i = 0 ; i < n ; ++ i)
        printf("%d%c" , res[i] , " \n"[i + 1 == n]);    
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}