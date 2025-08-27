mt19937 rng(0);

using ptr = int32_t;

struct vertex {
    ptr lf = 0, rg = 0;
    int32_t heap = rng(), rnd = rng(), sz = 1;
    int val, sum = 0;

    vertex(int x = 0) : val(x), sum(x) {}
};

vector <vertex> mem;

ptr new_vertex(int x) {
    mem.app(vertex(x));
    return (int)mem.size()-1;
}

ptr update(ptr v) {
    mem[v].sz = mem[mem[v].lf].sz + 1 + mem[mem[v].rg].sz;
    mem[v].sum = mem[mem[v].lf].sum + mem[v].val + mem[mem[v].rg].sum;
    return v;
}

ptr merge(ptr l, ptr r) {
    if (!l || !r) return l ^ r;
    if (mem[l].heap > mem[r].heap) {
        mem[l].rg = merge(mem[l].rg, r);
        return update(l);
    } else {
        mem[r].lf = merge(l, mem[r].lf);
        return update(r);
    }
}

pair<ptr, ptr> splitkey(ptr v, int x, int32_t rnd) {
    if (!v) return {v, v};
    if (pair{mem[v].val, mem[v].rnd} < pair{x, rnd}) {
        auto [lf, rg] = splitkey(mem[v].rg, x, rnd);
        mem[v].rg = lf;
        return {update(v), rg};
    } else {
        auto [lf, rg] = splitkey(mem[v].lf, x, rnd);
        mem[v].lf = rg;
        return {lf, update(v)};
    }
}

void insert(ptr &a, ptr b) {
    if (!a) {
        a = b;
        return;
    }
    if (mem[a].heap > mem[b].heap) {
        if (pair{mem[a].val, mem[a].rnd} < pair{mem[b].val, mem[b].rnd}) {
            insert(mem[a].rg, b);
        } else {
            insert(mem[a].lf, b);
        }
        update(a);
    } else {
        auto [lf, rg] = splitkey(a, mem[b].val, mem[b].rnd);
        mem[b].lf = lf;
        mem[b].rg = rg;
        a = update(b);
    }
}

void join(ptr &a, ptr b) {
    auto dfs = [&](auto dfs, ptr b) -> void {
        if (!b) return;
        ptr lf = mem[b].lf;
        ptr rg = mem[b].rg;
        mem[b].lf = mem[b].rg = 0;
        insert(a, update(b));
        dfs(dfs, lf);
        dfs(dfs, rg);
    };
    dfs(dfs, b);
}

pair <ptr, ptr> splitsz(ptr v, int k) {
    if (!v) return {v, v};
    if (k <= mem[mem[v].lf].sz) {
        auto [l, r] = splitsz(mem[v].lf, k);
        mem[v].lf = r;
        return {l, update(v)};
    } else {
        auto [l, r] = splitsz(mem[v].rg, k - mem[mem[v].lf].sz - 1);
        mem[v].rg = l;
        return {update(v), r};
    }
}

int32_t main() {
    mem = {vertex()};
    mem[0].sz = 0;
}

//54a637
