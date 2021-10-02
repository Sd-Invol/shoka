namespace SegTree {
inline int id(int l, int r) {
  return l + r | l != r;
}
#define Left l, mid
#define Right mid + 1, r
typedef std::pair<int, int> Node;
struct stree {
  Node w;
  int f;
  void add(int x) {
    f += x;
    w.first += x;
  }
} t[N << 1];
Node merge(const Node& A, const Node B) {
  Node C(std::min(A.first, B.first), 0);
  if (C.first == A.first) {
    C.second += A.second;
  }
  if (C.first == B.first) {
    C.second += B.second;
  }
  return C;
}
void pushup(int p, int l, int mid, int r) {
  t[p].w = merge(t[id(Left)].w, t[id(Right)].w);
}
void pushdown(int p, int l, int mid, int r) {
  if (t[p].f) {
    t[id(Left)].add(t[p].f);
    t[id(Right)].add(t[p].f);
    t[p].f = 0;
  }
}
void add(int l, int r, int top, int bot, int w) {
  int p = id(l, r);
  if (top <= l && r <= bot) {
    t[p].add(w);
  } else {
    int mid = l + r >> 1;
    pushdown(p, l, mid, r);
    if (top <= mid) {
      add(Left, top, bot, w);
    }
    if (bot > mid) {
      add(Right, top, bot, w);
    }
    pushup(p, l, mid, r);
  }
}
Node query(int l, int r, int top, int bot) {
  int p = id(l, r);
  if (top <= l && r <= bot) {
    return t[p].w;
  } else {
    int mid = l + r >> 1;
    pushdown(p, l, mid, r);
    if (bot <= mid) {
      return query(Left, top, bot);
    }
    if (top > mid) {
      return query(Right, top, bot);
    }
    return merge(query(Left, top, bot), query(Right, top, bot));
  }
}
void build(int l, int r) {
  int p = id(l, r);
  t[p].f = 0;
  if (l == r) {
    t[p].w = Node(0, a[l]);
  } else {
    int mid = l + r >> 1;
    build(Left);
    build(Right);
    pushup(p, l, mid, r);
  }
}
#undef Left
#undef Right
}  // namespace SegTree
