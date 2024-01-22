class Tarjan {
 public:
  int n, scnt;
  std::vector<std::vector<int>> e;
  std::vector<int> low, ord, bel, in_stack;
  std::stack<int> stack;

  Tarjan(std::vector<std::vector<int>> e) : n(e.size()), scnt(0), e(e) {
    low.assign(n, 0);
    ord.assign(n, 0);
    bel.assign(n, -1);
    in_stack.assign(n, 0);
  }
  void dfs(int x, int &&ncnt) {
    low[x] = ord[x] = ++ncnt;
    in_stack[x] = 1;
    stack.push(x);
    for (auto &y : e[x]) {
      if (!ord[y]) {
        dfs(y, std::move(ncnt));
        low[x] = std::min(low[x], low[y]);
      } else if (in_stack[y]) {
        low[x] = std::min(low[x], ord[y]);
      }
    }
    if (low[x] == ord[x]) {
      int i;
      do {
        i = stack.top();
        stack.pop();
        in_stack[i] = false;
        bel[i] = scnt;
      } while (i != x);
      ++scnt;
    }
  }
  void processScc() {
    scnt = 0;
    ord.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      if (!ord[i]) {
        dfs(i, 0);
      }
    }
  }
};

/***********************************************/
int dfn[N], low[N], ncnt;
stack<int> S;
int bel[M], tmp[N];
void dfs(int x, int fa) {
  dfn[x] = low[x] = ++ncnt;
  for (int i = pre[x]; ~i; i = e[i].next) {
    int y = e[i].x;
    if (!dfn[y]) {
      S.push(i);
      dfs(y, i ^ 1);
      low[x] = min(low[x], low[y]);
      if (low[y] > dfn[x]) {
      }  //(x , y) is bridge
      if (low[y] >= dfn[x]) {
        ++n;
        int j;
        do {
          j = S.top(), S.pop();
          if (tmp[e[j].x] != n)
            E[m++] = make_pair(n, e[j].x), tmp[e[j].x] = n;
          if (tmp[e[j ^ 1].x] != n)
            E[m++] = make_pair(n, e[j ^ 1].x), tmp[e[j ^ 1].x] = n;
          bel[j >> 1] = n;
        } while (j != i);
      }
    } else if (i != fa && dfn[y] < dfn[x])
      S.push(i), low[x] = min(low[x], dfn[y]);
  }
}
