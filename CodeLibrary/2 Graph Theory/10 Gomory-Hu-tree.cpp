void divide(int l, int r) {
  if (l == r)
    return;
  random_shuffle(a + l, a + r + 1);
  for (int i = 0; i < mcnt; i += 2)
    e[i].f = e[i ^ 1].f = (e[i].f + e[i ^ 1].f) / 2;
  s = a[l], t = a[r];
  E[m++] = (edge){s, t, -dinic()};

  int lp = l, rp = r;
  while (lp < rp) {
    while (lp < rp && ~d[a[lp]])
      ++lp;
    while (lp < rp && !~d[a[rp]])
      --rp;
    if (lp < rp) {
      swap(a[lp], a[rp]);
      ++lp, --rp;
    }
  }
  divide(l, lp - 1);
  divide(rp + 1, r);
}