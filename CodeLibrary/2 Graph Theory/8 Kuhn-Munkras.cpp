int n;
using Type = int;
const Type INF = 1LL << 60;

Type cost[N][N], lx[N], ly[N], slack[N];
int prev[N], match[N];
bool vy[N];

void augment(int root) {
  std::fill(vy + 1, vy + n + 1, false);
  std::fill(slack + 1, slack + n + 1, INF);
  int py;
  match[py = 0] = root;
  do {
    vy[py] = true;
    int x = match[py], yy = 0;
    Type delta = INF;
    for (int y = 1; y <= n; y++) {
      if (!vy[y]) {
        if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
          slack[y] = lx[x] + ly[y] - cost[x][y];
          prev[y] = py;
        }
        if (slack[y] < delta) {
          delta = slack[y];
          yy = y;
        }
      }
    }
    for (int y = 0; y <= n; y++) {
      if (vy[y]) {
        lx[match[y]] -= delta;
        ly[y] += delta;
      } else {
        slack[y] -= delta;
      }
    }
    py = yy;
  } while (match[py] != -1);
  do {
    int pre = prev[py];
    match[py] = match[pre];
    py = pre;
  } while (py);
}

int KM() {
  for (int i = 1; i <= n; i++) {
    lx[i] = ly[i] = -INF;
    match[i] = -1;
    for (int j = 1; j <= n; j++) {
      lx[i] = std::max(lx[i], cost[i][j]);
    }
  }
  int answer = 0;
  for (int root = 1; root <= n; root++) {
    augment(root);
  }
  for (int i = 1; i <= n; i++) {
    answer += lx[i];
    answer += ly[i];
    // printf("%d %d\n", match[i], i);
  }
  return answer;
}