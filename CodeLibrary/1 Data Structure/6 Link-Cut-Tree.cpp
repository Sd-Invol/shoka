#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
const int INF = 1 << 30;

struct Node *null;

struct Node {
    Node *ch[2] , *fa;
    int size;
    bool rev;

    int val;
    int delta;
    int same;
    pair<int , int> mx[2];
    Node (int v = 0) {
        fa = ch[0] = ch[1] = null;
        size = 1;

        rev = 0;

        mx[0] = make_pair(v , 1);
        mx[1] = make_pair(-INF , 0);
        val = v;
        delta = 0;
        same = INF;
    }

    inline bool d() {
        return this == fa->ch[1];
    }
    inline bool isroot() {
        return fa == null || fa->ch[0] != this && fa->ch[1] != this;
    }

    void add(int v) {
        if (this == null) return;
        if (same != INF) same += v;
        delta += v;
        val += v;
        mx[0].first += v;
        mx[1].first += v;
    }
    void assign(int v) {
        if (this == null) return;
        same = val = v;
        delta = 0;
        mx[0] = make_pair(v , size);
        mx[1] = make_pair(-INF , 0);
    }
    void reverse() {
        if (this == null) return;
        rev ^= 1;
        swap(ch[0] , ch[1]);
    }

    void pushdown() {
        if (this == null) return;
        if (rev) {
            ch[0]->reverse();
            ch[1]->reverse();
            rev ^= 1;
        }
        if (delta) {
            ch[0]->add(delta);
            ch[1]->add(delta);
            delta = 0;
        }
        if (same != INF) {
            ch[0]->assign(same);
            ch[1]->assign(same);
            same = INF;
        }
    }

    void pushup() {
        if (this == null) return;
        size = ch[0]->size + 1 + ch[1]->size;
        int j = 0 , k = 0 , l = 0;
        for (int i = 0 ; i < 2 ; ++ i) {
            int x = max(ch[0]->mx[j].first , ch[1]->mx[l].first) , y = 0;
            if (k < 1) x = max(x , val);
            if (x == ch[0]->mx[j].first) y += ch[0]->mx[j ++].second;
            if (k < 1 && x == val) ++ y , ++ k;
            if (x == ch[1]->mx[l].first) y += ch[1]->mx[l ++].second;
            mx[i] = make_pair(x , y);
        }
    }

    void setc(Node *c , int d) {
        ch[d] = c;
        c->fa = this;
        pushup();
    }

    void rot() {
        Node *f = fa, *ff = fa->fa;
        int c = d(), cc = fa->d();
        f->setc(ch[c ^ 1],c);
        this->setc(f,c ^ 1);
        if (ff->ch[cc] == f) ff->setc(this,cc);
        else this->fa = ff;
    }

    void D() {
        if (!isroot()) fa->D();
        pushdown();
    }

    Node* splay() {
        D();
        while (!isroot()) {
            if (!fa->isroot()) {
                d() == fa->d() ? fa->rot() : rot();
            }
            rot();
        }
        return this;
    }

    Node *access() {
        for (Node *p = this,*q = null; p != null; ) {
            p->splay();
            p->setc(q,1);
            q = p;
            p = p->fa;
        }
        return splay();
    }
};

int n , m;
Node pool[N], *node[N], *alloc;

void setroot(Node *x) {
    x->access()->reverse();
}
void link(Node *x , Node *y) {
    setroot(x);
    x->fa = y;
    x->access();
}
void cut(Node *x , Node *y) {
    setroot(x);
    y->access();
    x->splay();
    x->setc(null , 1);
    y->fa = null;
}

void work() {
    alloc = pool;
    null = new(alloc ++) Node();
    null->fa = null->ch[0] = null->ch[1] = null;
    null->val = -INF;
    null->mx[0] = null->mx[1] = make_pair(-INF , 0);

    null->size = 0;

    static int ca = 0;
    printf("Case #%d:\n" , ++ ca);
    scanf("%d%d" , &n , &m);
    for (int i = 1 ; i <= n ; ++ i) {
        int v;
        scanf("%d" , &v);
        node[i] = new(alloc ++) Node(v);
    }
    for (int i = 1 ; i < n ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        link(node[x] , node[y]);
    }
    while (m --) {
        int o , x , y , v;
        scanf("%d%d%d" , &o , &x , &y);
        if (o == 1) {
            cut(node[x] , node[y]);
            scanf("%d%d" , &x , &y);
            link(node[x] , node[y]);
        } else {
            setroot(node[x]);
            node[y]->access();
            if (o == 2) {
                scanf("%d" , &v);
                node[y]->assign(v);
            } else if (o == 3) {
                scanf("%d" , &v);
                node[y]->add(v);
            } else {
                if (!node[y]->mx[1].second) {
                    puts("ALL SAME");
                } else {
                    printf("%d %d\n" , node[y]->mx[1].first, node[y]->mx[1].second);
                }
            }

        }

    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --) {
        work();
    }
}
