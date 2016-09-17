const int N = 500005;
struct Node {
    Node *ch[2] , *p;
    int size;
    int val , sum , lm , rm , sm;
    int same;
    bool rev;
    Node () {
        size = val = sum = 0;
        lm = rm = sm = -1e9;
        same = 1 << 30 , rev = 0;
    }
    bool d() {
        return this == p->ch[1];
    }
    void setc(Node *c , int d) {
        ch[d] = c;
        c -> p = this;
    }
    void setsame(int x) {
        same = val = x;
        sum = val * size;
        lm = rm = sm = max(val , sum);
    }
    void reverse() {
        rev ^= 1;
        swap(ch[0] , ch[1]);
        swap(lm , rm);
    }
    void pushdown();
    void pushup() {
        size = ch[0] -> size + ch[1] -> size + 1;
        sum = ch[0] -> sum + val + ch[1] -> sum;
        lm = max(ch[0] -> lm , max(ch[0] -> sum + val , ch[0] -> sum + val + ch[1] -> lm));
        rm = max(ch[1] -> rm , max(ch[1] -> sum + val , ch[1] -> sum + val + ch[0] -> rm));
        sm = max(val , max(ch[0] -> sm , ch[1] -> sm));
        sm = max(sm , max(ch[0]->rm , ch[1]->lm) + val);
        sm = max(sm , ch[0]->rm + val + ch[1]->lm);
    }
}Tnull , *null = &Tnull;
Node mem[N] , *C = mem;
Node* rub[N];
int rubsize;
void Node::pushdown() {
    if (rev) {
        if (ch[0] != null)
            ch[0]->reverse();
        if (ch[1] != null)
            ch[1]->reverse();
        rev ^= 1;
    }
    if (same != 1 << 30) {
        if (ch[0] != null)
            ch[0]->setsame(same);
        if (ch[1] != null)
            ch[1]->setsame(same);
        same = 1 << 30;
    }
}
Node* newnode(int v) {
    Node *p = rubsize ? rub[-- rubsize] : C ++;
    p->ch[0] = p->ch[1] = p->p = null;
    p->size = 1;
    p->val = p->sum = p->lm = p->rm = p->sm = v;
    p->same = 1 << 30 , p->rev = 0;
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
void update(Node *t) {
    static Node* Stack[N];
    int top = 0;
    while (t != null) {
        Stack[top ++] = t;
        t = t->p;
    }
    for (int i = top - 1 ; i >= 0 ; -- i)
        Stack[i]->pushdown();
}
void splay(Node *t , Node *f = null) {
    update(t);
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
        t->pushdown();
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
        x->pushdown();
        p = select(x , x->size);
        splay(p);
        p->setc(y , 1);
        p->pushup();
    }
}
int n , m , a[N];
Node* build(int l , int r) {
    if (l > r)
        return null;
    int mid = l + r >> 1;
    Node *t = newnode(a[mid]);
    t->setc(build(l , mid - 1) , 0);
    t->setc(build(mid + 1 , r) , 1);
    t->pushup();
    return t;
}
void del(Node *p) {
    if (p == null)
        return;
    rub[rubsize ++] = p;
    del(p->ch[0]);
    del(p->ch[1]);
}
int main() {
    scanf("%d%d" , &n , &m);
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%d" , &a[i]);
    Node *root = build(1 , n);
    return 0;
}
