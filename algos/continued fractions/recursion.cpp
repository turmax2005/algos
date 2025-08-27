int cnt (int n, int k, int b, int d)
{
  if (k == 0) return (b / d) * n;
  if (k >= d || b >= d) {
    return (k / d) * n * (n - 1) / 2 + (b / d) * n + cnt(n, k % d, b % d, d);
  }
  return cnt((k * n + b) / d, d, (k * n + b) % d, k);
}

//11a6a0
