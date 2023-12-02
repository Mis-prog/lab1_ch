#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

double acos_foo(double x) {
    return x * x * acos(0.9 * x);
}

double lagrange(vector<double> &x, vector<double> &y, double _x, int n) {
    double result = 0.0;

    for (int i = 0; i <= n; i++) {
        double P = 1.0;

        for (int j = 0; j <= n; j++)
            if (j != i)
                P *= (_x - x[j]) / (x[i] - x[j]);

        result += P * y[i];
    }
    return result;
}

void nodeFillEquals(vector<double> &x, vector<double> &y, int n) {
    double a = 0, b = 1;
    double h = (b - a) / n;
    x[0] = a;
    y[0] = acos_foo(x[0]);
    for (int i = 1; i <= n; i++) {
        x[i] = x[i - 1] + h;
        y[i] = acos_foo(x[i]);
    }
}

double checkAccuracy(vector<double> &x, vector<double> &y, int n) {
    double a = 0, b = 1;
    double h_accurace = (b - a) / (double) 10e5;
    double sup = -1000, diff, current = 0;
    while (current <= b) {
        diff = abs(acos_foo(current) - lagrange(x, y, current, n));
        if (diff > sup) {
            sup = diff;
        }
        current += h_accurace;
    }
    return sup;
}

int task1_1(int n) {
    int bestNode = 0;
    double current_rasn = 0, best_rasn = 1000;
    vector<double> x(n + 1, 0), y(n + 1, 0);
    ofstream out1_1;
    out1_1.open("task1_1.txt");
    for (int i = 1; i <= n; i++) {
        nodeFillEquals(x, y, i);
        current_rasn = checkAccuracy(x, y, i);
        out1_1 << i << " " << current_rasn << endl;
        if (current_rasn < best_rasn) {
            best_rasn = current_rasn;
            bestNode = i;
        }
    }
    out1_1.close();
    return bestNode;
}

double task1_2(int n) {
    ofstream out1_2;
    out1_2.open("task1_2.txt");
    double a = 0, b = 1;
    vector<double> x(n + 1, 0), y(n + 1, 0);
    nodeFillEquals(x, y, n);
    double h_accurace = (b - a) / (double) 1e5;
    double x_current = 0, diff, sup = -1000;
    while (x_current < b) {
        diff = abs(acos_foo(x_current) - lagrange(x, y, x_current, n));
        out1_2 << x_current << " " << diff << endl;
        if (diff > sup) {
            sup = diff;
        }
        x_current += h_accurace;
    }
    out1_2.close();
    return sup;
}

void result(){
    string line;
    ifstream in("result.txt");
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            std::cout << line << std::endl;
        }
    }
    in.close();
}


void task1_main(int n) {
    int n0 = task1_1(n);
    cout << "n0=" << n0 << endl;
    ofstream out_res;
    out_res.open("result.txt");
    out_res << "Интерполяция Лагранжем(равномерная сетка): " << task1_2(n) << endl;
    out_res.close();
    result();
    system("python D:/5sem/numerical/Lab1/plot_1.py");
}