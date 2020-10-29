const int n_states = 2;

struct Matrix {
    ll mat[n_states][n_states];
    Matrix(ll val) {
        FOR(i, 0, n_states) FOR(j, 0, n_states) {
            mat[i][j] = val;
        }
    }
    Matrix operator*(Matrix &other) {
        Matrix ret(0);
        FOR(k, 0, n_states) FOR(i, 0, n_states) FOR(j, 0, n_states) {
            ret.mat[i][j] += mat[i][k] * other.mat[k][j];
        }
        return ret;
    }
};

Matrix bin_exp(Matrix b, ll e) {
    Matrix prod(0);
    FOR(i, 0, n_states) {
        prod.mat[i][i] = 1;
    }
    while (e > 0) {
        if (e & 1)
            prod = prod * b;
        b = b * b;
        e >>= 1;
    }
    return prod;
}