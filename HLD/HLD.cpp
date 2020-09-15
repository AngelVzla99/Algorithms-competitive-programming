// code for HLD
int heavy[MAXN];
void dfs_heavy(int x, int f = -1) {
    heavy[x] = -1;
    int mx = -1;
    for (auto aux : G[x]) {
        int y = aux.F, c = aux.S;
        if (y == f)
            continue;
        if (sz[y] > mx) {
            mx = sz[y];
            heavy[x] = y;
        }
    }
    for (auto aux : G[x]) {
        if (aux.F == f)
            continue;
        dfs_heavy(aux.F, x);
    }
}

int head[MAXN], start[MAXN];
int paths[MAXN];
int pos;
void hld() {
    for (int i = 0, pos = 0; i < n; ++i) {
        if (father[i] == -1 || heavy[father[i]] != i) {
            for (int j = i; j != -1; j = heavy[j])
            {
                head[j] = i;
                start[j] = pos; paths[pos] = weight[j];
                pos++;
            }
        }
    }
}

int query(int a, int b) { // query para max en este caso
    int res = 0;
    while (head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]]) {
            swap(a, b);
        }
        res = max(res, STQ(start[head[a]], start[a] + 1).val);
        a = father[head[a]];
    }
    if (depth[a] > depth[b])
        swap(a, b);
    if (a != b)
        res = max(res, STQ(start[a] + 1, start[b] + 1).val); // aqui es start[a] + 1 porque la query es sobre edges
    return res;
}