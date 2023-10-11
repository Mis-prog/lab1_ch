#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <fstream>
#include <cstdlib>

using namespace std;

double foo(double x){
    return x*x*acos(0.9*x);
}

double lagrange(vector<double>& x, vector<double>& y, double _x)
{
    double result = 0.0;

    for (int i = 0; i < x.size(); i++)
    {
        double P = 1.0;

        for (int j = 0; j < x.size(); j++)
            if (j != i)
                P *= (_x - x[j])/ (x[i] - x[j]);

        result += P * y[i];
    }

    return result;
}

double task1(int n){
    double a=0,b=1;
    double h=(b-a)/n;
    vector<double> x(n,0),y(n,0);
    x[0]=a;y[0]=foo(x[0]);
    for (int i=1;i<n;i++){
        x[i]=x[i-1]+h;
        y[i]=foo(x[i]);
    }
    double h_accurace=(b-a)/100000.0;
    double sup=-10000,diff=0,current=0;
    for (int i=0;i<100000;i++){
        diff=abs(foo(current)- lagrange(x,y,current));
        if (diff>sup){
            sup=diff;
        }
        current+=h_accurace;
    }
    return sup;
}
double task1_2(int n);

void task1_main(int n) {
//    ofstream out1;
//    out1.open("task1.txt");
//    for (int i = 1; i < n; i++) {
//        out1 << i << " " << task1(i) << endl;
//    }
//    out1.close();
//   system("D:/5sem/numerical/Lab1/plot.py");
    task1_2(17);
}

double task1_2(int n){
    ofstream out2;
    out2.open("task1_2.txt");
    double a=0,b=1;
    double h=(b-a)/n;
    vector<double> x(n,0),y(n,0);
    x[0]=a;y[0]=foo(x[0]);
    for (int i=1;i<=n;i++){
        x[i]=x[i-1]+h;
        y[i]=foo(x[i]);
    }
    double h_accurace=(b-a)/100000.0;
    double x_current=0;
    for (int i=0;i<100000;i++){
        out2 << x_current << " " << abs(foo(x_current)- lagrange(x,y,x_current)) << endl;
        x_current+=h_accurace;
    }
    out2.close();
}