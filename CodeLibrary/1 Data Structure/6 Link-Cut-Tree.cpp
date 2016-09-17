const int N = 100005;
const int INF = -1 << 30;
struct Node {
    Node *ch[2] , *p , *fa;
    int size;
    int val , add;
    int same;
    pair<int , int> mx[2];
    bool rev;
    Node () {
        mx[0].first = mx[1].first = INF;
        size = val = add = 0;
        same = 1 << 30 , rev = 0;
    }
    bool d() {
        return this == p->ch[1];
    }
    void setc(Node *c , int d) {
        ch[d] = c;
        c->p = this;
    }
    void addwei(int x) {
        if (same != 1 << 30)
            same += x;
        add += x , val += x;
        mx[0].first += x , mx[1].first += x;
    }
    void setsame(int x) {
        same = val = x;
        add = 0;
        mx[0] = make_pair(x , size);
        mx[1] = make_pair(INF , 0);
    }
    void reverse() {
        rev ^= 1;
        swap(ch[0] , ch[1]);
    }
    void pushdown();
    void pushup() {
        size = ch[0]->size + ch[1]->size + 1;
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
}Tnull , *null = &Tnull;
Node mem[N] , *C = mem;
void Node::pushdown() {
    if (rev) {
        if (ch[0] != null)
            ch[0]->reverse();
        if (ch[1] != null)
            ch[1]->reverse();
        rev ^= 1;
    }
    if (add) {
        if (ch[0] != null)
            ch[0]->addwei(add);
        if (ch[1] != null)
            ch[1]->addwei(add);
        add = 0;
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
    Node *p = C ++;
    p->ch[0] = p->ch[1] = p->p = p->fa = null;
    p->size = 1;
    p->val = v;
    p->same = 1 << 30 , p->rev = p->add = 0;
    p->mx[0] = make_pair(v , 1);
    p->mx[1] = make_pair(INF , 0);
    return p;
}
void rotate(Node *t) {
    Node *p = t->p;
    int d = t->d();
    p->p->setc(t , p->d());
    p->setc(t->ch[!d] , d);
    t->setc(p , !d);
    p->pushup();
    t->fa = p->fa;
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
Node* expose(Node *x) {
    Node *y = null;
    while (x != null) {
        splay(x);
        Node *z = x->ch[1];
        z->p = null;
        z->fa = x;
        x->setc(y , 1);
        y->fa = null;
        x->pushup();
        y = x , x = x->fa;
    }
    return y;
}
void setroot(Node *x) {
    expose(x);
    splay(x);
    x->reverse();
}
void link(Node *x , Node *y) {
    setroot(x);
    x->fa = y;
    expose(x);
}
void cut(Node *x , Node *y) {
    setroot(x);
    expose(y);
    splay(x);
    x->setc(null , 1);
    x->pushup();
    y->fa = y->p = null;
}
int n , m , pre[N] , mcnt , ca;
struct edge {
    int x , next;
}e[N << 1];
bool vis[N];
Node *V[N];
void work() {
    printf("Case #%d:\n" , ++ ca);
    scanf("%d%d" , &n , &m);
    C = mem;
    for (int i = 1 ; i <= n ; ++ i) {
        int x;
        scanf("%d" , &x);
        V[i] = newnode(x);
    }

    queue<int> Q;
    memset(vis , 0 , sizeof(vis));
    Q.push(1) , vis[1] = 1;
    while (!Q.empty()) {
        int x = Q.front() ; Q.pop();
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (!vis[y]) {
                V[y]->fa = V[x];
                vis[y] = 1;
                Q.push(y);
            }
        }
    }
}
