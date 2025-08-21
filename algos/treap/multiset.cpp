mt19937 rng(0);

struct vertex {
  int heap = rng(), val;
  int sz = 1, cnt = 1;
  vertex *lf = nullptr, *rg = nullptr;

  vertex(int x, int cnt) : val(x), cnt(cnt), sz(cnt) {}

  friend int get_sz(vertex *v) {
    return v ? v->sz : 0;
  }

  vertex *update() {
    sz = get_sz(lf) + cnt + get_sz(rg);
    return this;
  }
};

vertex *merge(vertex *l, vertex *r) {
  if (!l) return r;
  if (!r) return l;
  if (l->heap < r->heap) {
    r->lf = merge(l, r->lf);
    return r->update();
  } else {
    l->rg = merge(l->rg, r);
    return l->update();
  }
}

pair<vertex *, vertex *> split(vertex *v, int x) {
  if (!v) return {v, v};
  if (v->val < x) {
    auto [lf, rg] = split(v->rg, x);
    v->rg = lf;
    return {v->update(), rg};
  } else {
    auto [lf, rg] = split(v->lf, x);
    v->lf = rg;
    return {lf, v->update()};
  }
}

vertex *add(vertex *v, int x, int cnt) {
  auto [l, mr] = split(v, x);
  auto [m, r] = split(mr, x + 1);
  if (m == nullptr) {
    m = new vertex(x, cnt);
  } else {
    m->cnt += cnt;
    if (m->cnt == 0) m = nullptr; else m->update();
  }
  return merge(l, merge(m, r));
}

vertex *insert(vertex *a, vertex *b) {
    if (!a) return b;
    if (a->heap > b->heap) {
        if (a->val < b->val) {
            a->rg = insert(a->rg, b);
            return a->update();
        } else {
            a->lf = insert(a->lf, b);
            return a->update();
        }
    } else {
        auto [lf, rg] = splitkey(a, b->val, b->rnd);
        b->lf = lf;
        b->rg = rg;
        return b->update();
    }
}

vertex *join(vertex *a, vertex *b) {
    auto dfs = [&](auto dfs, vertex *b) -> void {
        if (!b) return;
        vertex *lf = b->lf;
        vertex *rg = b->rg;
        b->lf =  b->rg = nullptr;
        b = b->update();
        a = insert(a, b);
        dfs(dfs, lf);
        dfs(dfs, rg);
    };
    dfs(dfs, b);
    return a;
}
