

vector<double> &coef(vector<double> &x, vector<double> &y, int n0) {
    vector<vector<double>> coeff(n0, vector<double>(n0, 0));
    vector<double> a(n0, 0);
    for (int i = n0 - 1; i >= 0; i--) {
        coeff[i][0] = y[i + 1] - y[i];
    }
    for (int j = 1; j < n0; j++) {
        for (int i = n0 - 1 - j; i >= 0; i--) {
            coeff[i][j] = coeff[i + 1][j - 1] - coeff[i][j - 1];
        }
    }
    double start = 0, end = 1;
    double h = (end - start) / n0;
    int factorial = 1;
    for (int i = 1; i <= n0; i++) {
        a[i - 1] = coeff[0][i - 1] / (i * factorial * pow(h, i));
    }
    return a;
}

double Newton(vector<double> &x, vector<double> &y, vector<double> &a, int n0, double _x) {
    double result = y[0];
    for (int i = 1; i <= n0; i++) {
        for (int j = 0; j < i; j++) {
            result += a[i - 1] * (_x - x[j]);
        }
    }
    return result;
}

void task3_main(int n0) {
    vector<double> x(n0 + 1, 0), y(n0 + 1, 0), a;
    nodeFillEquals(x, y, n0);
    a = coef(x, y, n0);
    cout << Newton(x, y, a, 32, 0.2);
}