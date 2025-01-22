auto dfs = [&](auto self, int u, int v) -> int
{
    int ans = 0;
    for (auto i : adj[u])
    {
        if (i == v)
            continue;
        // jai shree ram
    }
    return ans;
};
vb vis(n + 1, false);
vi start(n + 1, 0), end(n + 1, 0);
auto dfs_time = [&](auto self, int u, int v) -> void
{
    vis[u] = true;
    start[u] = ++ttt;
    for (auto i : adj[u])
    {
        if (!vis[i])
        {
            self(self, i, u);
        }
    }
    end[u] = ++ttt;
};
auto bfs = [&](int u) -> void
{
    qi q;
    q.push(u);
    vb vis(n + 1, false);
    vi depth(n + 1, 0);
    vis[u] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto i : adj[u])
        {
            if (!vis[i])
            {
                vis[i] = true;
                depth[i] = depth[u] + 1;
                q.push(i);
            }
        }
    }
};

struct DSU
{
    std::vector<int> f, siz;

    DSU() {}
    DSU(int n)
    {
        init(n);
    }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x)
    { // O(2*n)
        while (x != f[x])
        {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            return false;
        }
        if (siz[x] < siz[y])
        {
            swap(x, y);
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }
};
// initialize DSU dsu(n);
// dsu.merge(u, v);
// dsu.same(u, v);
// dsu.size(u);