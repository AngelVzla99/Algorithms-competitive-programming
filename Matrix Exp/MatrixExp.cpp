struct Matrix { // struct para exp de matrices
    long double m[2][2] = {{0, 0}, {0, 0}};
    Matrix operator *(const Matrix &other) {
        Matrix prod;
        FOR(i, 0, 2) FOR(j, 0, 2) FOR(k, 0, 2) {
            prod.m[i][k] += m[i][j] * other.m[j][k];
        }
        return prod;
    }
};

Matrix bin_pow(Matrix x, int k) {
    Matrix prod;
    FOR(i, 0, 2) {
        prod.m[i][i] = 1;
    }
    while (k > 0) {
        if (k & 1) {
            prod = prod * x;
        }
        x = x * x;
        k >>= 1;
    }
    return prod;
}