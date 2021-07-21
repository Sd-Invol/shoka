const int INF = 1e9;
const int N = 505;
int n;
int from[N][N + N];
int edge[N][N + N];
int sel[N + N], f[N + N], vis[N + N];
int getf(int x) {
  return f[x] == x ? x : f[x] = getf(f[x]);
}
void liuzhu() {
  f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    sel[i] = 1;
    f[i] = i;
    for (int j = 1; j <= n; ++j)
      if (f[j] != i) {
        from[j][i] = i;
        if (edge[sel[i]][i] > edge[j][i])
          sel[i] = j;
      }
  }
  int limit = n;
  while (1) {
    int prelimit = limit;
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= prelimit; ++i)
      if (f[i] == i && !vis[i]) {
        int j = i;
        while (j != 1 && !vis[j]) {
          vis[j] = i;
          j = getf(sel[j]);
        }
        if (j == 1 || vis[j] != i)
          continue;
        vector<int> C;
        int k = j;
        do {
          C.push_back(k);
          k = getf(sel[k]);
        } while (k != j);
        ++limit;
        for (int i = 1; i <= n; ++i) {
          edge[i][limit] = INF;
          from[i][limit] = limit;
        }
        f[limit] = vis[limit] = limit;
        for (int i = 0; i < (int)C.size(); ++i) {
          int x = C[i];
          f[x] = limit;
          for (int j = 1; j <= n; ++j) {
            if (edge[j][x] == INF)
              continue;
            if (edge[j][limit] > edge[j][x] - edge[sel[x]][x]) {
              edge[j][limit] = edge[j][x] - edge[sel[x]][x];
              from[j][limit] = x;
            }
          }
        }
        for (int j = 1; j <= n; ++j)
          if (getf(j) == limit)
            edge[j][limit] = INF;
        sel[limit] = 1;
        for (int j = 1; j <= n; ++j)
          if (edge[sel[limit]][limit] > edge[j][limit])
            sel[limit] = j;
      }
    if (prelimit == limit)
      break;
  }
  for (int i = limit; i > 1; --i)
    sel[from[sel[i]][i]] = sel[i];
}
