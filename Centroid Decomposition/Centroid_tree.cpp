// Solo es una guia, varia mucho dependiendo del problema

int v;
vi G[MAXN];
bool is_centroid[MAXN];
int sz[MAXN];
int father[MAXN];

int dfs_sz(int x, int f = -1) {
	sz[x] = 1;
	for (auto y : G[x]) {
		if (y == f || is_centroid[y])
			continue;
		sz[x] += dfs_sz(y, x);
	}
	return sz[x];
}

int dfs_cd(int x, int cent_sz, int f = -1) {
	for (auto y : G[x]) {
		if (y == f || is_centroid[y])
			continue;
		if (sz[y] > cent_sz / 2)
			return dfs_cd(y, cent_sz, x);
	}
	return x;
}


void cent_descomp(int x, int f = -1) {
	int cent_sz = dfs_sz(x);
	int centroid = dfs_cd(x, cent_sz);
	is_centroid[centroid] = true;
	father[centroid] = f;
	for (auto y : G[centroid]) {
		if (is_centroid[y])
			continue;
		cent_descomp(y, centroid);
	}
}
