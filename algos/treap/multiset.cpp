mt19937 rng(0);

struct vertex {
  int heap = rng(), val, rnd = rng();
  int sz = 1, sum;
  vertex *lf = nullptr, *rg = nullptr;

  vertex(int x) : val(x), sum(x) {}

  friend int get_sz(vertex *v) {
    return v ? v->sz : 0;
  }

  friend int get_sum(vertex *v) {
    return v ? v->sum : 0;
  }

  vertex *update() {
    sz = get_sz(lf) + 1 + get_sz(rg);
    sum = get_sum(lf) + val + get_sum(rg);
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

pair<vertex *, vertex *> split(vertex *v, int x, int rnd) {
  if (!v) return {v, v};
  if (pair{v->val, v->rnd} < pair{x, rnd}) {
    auto [lf, rg] = split(v->rg, x, rnd);
    v->rg = lf;
    return {v->update(), rg};
  } else {
    auto [lf, rg] = split(v->lf, x, rnd);
    v->lf = rg;
    return {lf, v->update()};
  }
}

void insert(vertex *&a, vertex *b) {
    if (!a) {
        a = b;
        return;
    }
    if (a->heap > b->heap) {
        if (pair{a->val, a->rnd} < pair{b->val, b->rnd}) {
            insert(a->rg, b);
        } else {
            insert(a->lf, b);
        }
        a->update();
    } else {
        auto [lf, rg] = split(a, b->val, b->rnd);
        b->lf = lf;
        b->rg = rg;
        a = b->update();
    }
}

void join(vertex *&a, vertex *b) {
    auto dfs = [&](auto dfs, vertex *b) -> void {
        if (!b) return;
        vertex *lf = b->lf;
        vertex *rg = b->rg;
        b->lf =  b->rg = nullptr;
        b = b->update();
        insert(a, b);
        dfs(dfs, lf);
        dfs(dfs, rg);
    };
    dfs(dfs, b);
}

pair <vertex*, vertex*> split_sz(vertex *v, int k) {
    if (!v) return {v, v};
    if (k <= get_sz(v->lf)) {
        auto [l, r] = split_sz(v->lf, k);
        v->lf = r;
        return {l, v->update()};
    }
    else {
        auto [l, r] = split_sz(v->rg, k - get_sz(v->lf) - 1);
        v->rg = l;
        return {v->update(), r};
    }
}
