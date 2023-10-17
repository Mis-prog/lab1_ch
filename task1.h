#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <fstream>
#include <cstdlib>

using namespace std;

double acos_foo(double x) {
    return x * x * acos(0.9 * x);
}

double lagrange(vector<double> &x, vector<double> &y, double _x,int n) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double P = 1.0;

        for (int j = 0; j < n; j++)
            if (j != i)
                P *= (_x - x[j]) / (x[i] - x[j]);

        result += P * y[i];
    }
    return result;
}

void nodeFillEquals(vector<double> &x,vector<double> &y,int n){
    double a=0,b=1;
    double h = (b - a) / n;
    x[0] = a;
    y[0] = acos_foo(x[0]);
    for (int i = 1; i < n; i++) {
        x[i] = x[i - 1] + h;
        y[i] = acos_foo(x[i]);
    }

}

double checkAccuracy(vector<double>& x, vector<double>& y,int n) {
    double a = 0, b = 1;
    double h_accurace = (b - a) / 100000.0;
    double sup = -1000, diff, current = 0;
    while (current<=b) {
        diff = abs(acos_foo(current) - lagrange(x, y, current,n));
        if (diff > sup) {
            sup = diff;
        }
        current += h_accurace;
    }
    return sup;
}

int task1_1(int n){
    int bestNode=0;
    double current_rasn=0,best_rasn=1000;
    vector<double> x(n, 0), y(n, 0);
    ofstream out1;
    out1.open("task1.txt");
    for (int i = 1; i < n; i++) {
        nodeFillEquals(x,y,i);
        current_rasn=checkAccuracy(x,y,i);
        out1 << i << " " << current_rasn << endl;
        if (current_rasn<best_rasn){
            best_rasn=current_rasn;
            bestNode=i;
        }
    }
    out1.close();
    return bestNode;
}

void task1_2(int n) {
    ofstream out2;
    out2.open("task1_2.txt");
    double a = 0, b = 1;
    vector<double> x(n, 0), y(n, 0);
    nodeFillEquals(x,y, n);
    double h_accurace = (b - a) / 100000.0;
    double x_current = 0;
    while (x_current<b){
        out2 << x_current << " " << abs(acos_foo(x_current)- lagrange(x,y,x_current,n)) << endl;
        x_current+=h_accurace;
    }
    out2.close();
}

void task1_main(int n) {
    int n0=task1_1(n);
    cout << "n0=" << n0 << endl;
    task1_2(32);
    system("D:/5sem/numerical/Lab1/plotTask1.py");
}

