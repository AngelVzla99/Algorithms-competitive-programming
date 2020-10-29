//https://github.com/mhunicken/icpc-team-notebook-el-vasito/blob/b69d2d6e9ad7c2a8e00b9a5f2dd1eead0da588f2/graphs/centroid.cpp#L9

vector<int> G[MAXN]; int n;
bool tk[MAXN]; // already selected as a centroid
int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f) {
    szt[x] = 1;
    for (auto y : G[x])if (y != f && !tk[y])szt[x] += calcsz(y, x);
    return szt[x];
}
void cdfs(int x = 0, int f = -1, int sz = -1) { // O(nlogn)
    if (sz < 0)sz = calcsz(x, -1);
    for (auto y : G[x])if (!tk[y] && szt[y] * 2 >= sz) {
            szt[x] = 0; cdfs(y, f, sz); return;
        }
    tk[x] = true; fat[x] = f;
    for (auto y : G[x])if (!tk[y])cdfs(y, x);
}
void centroid() {memset(tk, false, sizeof(tk)); cdfs();}
