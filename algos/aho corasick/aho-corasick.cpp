struct node{
  int next[alpha] = {}, link[alpha] = {};
  int suf = 0;
  ll visited = 0, ans = 0;
  vector<int> term;
  node() {}
};

vector<node> mem;

int get_next(int nd, char c) {
  if (!mem[nd].next[c - a]) { mem[nd].next[c - a] = mem.size(); mem.emplace_back(); }
  return mem[nd].next[c - a];
}

void find(string s, vector<string> t) {
  mem.reserve(1e6 + 100);mem.clear();
  mem.emplace_back();mem.emplace_back();
  // 0th element is nullptr, 1st is the root
  int q = t.size();
  for (int j = 0; j < q; ++j) {
    int cur = 1;
    for (char c : ts[j]) cur = get_next(cur, c);
    mem[cur].term.push_back(j);
  }
  vector<int> bfs_order;
  queue<int> bfs;
  {
      node &root = mem[1];
      root.suf = 1;
      for (char c = a; c < a + alpha; ++c) {
          root.link[c - a] = (root.next[c - a] ? root.next[c - a] : 1);
      }
      bfs.push(1);
  }
  while (!bfs.empty()) {
    int cur_idx = bfs.front();
    bfs.pop();
    node &cur = mem[cur_idx];
    bfs_order.push_back(cur_idx);
    for (char c = a; c < a + alpha; ++c) {
      int nxt_idx = cur.next[c - a];
      if (!nxt_idx) continue;
      node &nxt = mem[nxt_idx];
      nxt.suf = (cur_idx == 1 ? 1 : mem[cur.suf].link[c - a]);
      for (char c = a; c < a + alpha; ++c) {
        nxt.link[c - a] = (nxt.next[c - a] ? nxt.next[c - a] : mem[nxt.suf].link[c - a]);
      }
      bfs.push(nxt_idx);
    }
  }
  // do something
}