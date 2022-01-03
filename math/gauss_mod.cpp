// https://codeforces.com/contest/1616/submission/141444001
typedef int Long;
pair< Long, vector<Long> > Gauss_MOD_SLAE(vector< vector<Long> > &A, Long mod) {
    Long n = A.size();
    Long m = A[0].size() - 1;
    vector<Long> where(m, -1);
    for (Long col = 0, row = 0; col < m && row < n; col++) {
        Long sel = row;
        for (Long i = row; i < n; i++) {
            if (A[i][col] != 0) {
                sel = i;
                break;
            }
        }
        if (A[sel][col] == 0) continue;
        for (Long i = col; i <= m; i++) swap(A[sel][i], A[row][i]);
        where[col] = row;
        for (Long i = row + 1; i < n; i++) {
            Long c = (A[i][col] * A[row][col]) % mod;
            if (c == 0) continue;
            for (Long j = col; j <= m; j++) {
                A[i][j] -= (A[row][j] * c) % mod;
                A[i][j] %= mod;
                if (A[i][j] < 0) A[i][j] += mod;;
            }
        }
        row++;
    }

    vector<Long> X(m, 0);
    for (Long j = m - 1; j >= 0; j--) {
        if (where[j] != -1) {
            Long b = A[where[j]][m];
            for (Long k = m - 1; k > j; k--) {
                b -= (X[k] * A[where[j]][k]) % mod;
                b %= mod;
                if (b < 0) b += mod;
            }
            X[j] = (b * A[where[j]][j]) % mod;
        }
    }
    for (Long i = 0; i < n; i++) {
        Long sum = 0;
        for (Long j = 0; j < m; j++) {
            sum += (X[j] * A[i][j]) % mod;
            sum %= mod;
        }
        if (A[i][m] != sum) return make_pair(0, X);
    }
    for (Long i = 0; i < m; i++) {
        if (where[i] == -1) return make_pair(INF, X);
    }
    return make_pair(1, X);
}
