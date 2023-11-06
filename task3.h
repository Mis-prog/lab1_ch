//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <random>
//#include <fstream>
//using namespace std;
//const double PI = 3.141592653589793;
//double func(double x) {
//    return x * x * acos(0.9 * x);
//}
//
//double ConRaz(int a, int b, vector<double> x, vector<double> y)
//{
//    if (b - a != 1)
//    {
//        return (ConRaz(a, b - 1, x, y) - ConRaz(a + 1, b, x, y)) / (x[a] - x[b]);
//    }
//    else
//    {
//        return (y[a] - y[b]) / (x[a] - x[b]);
//    }
//}
//
//double NewtonPoly(double x0, vector<double> x, vector<double> y, int n)
//{
//    double sum = y[0];
//    for (int k = 1; k <= n; k++)
//    {
//        double comp = ConRaz(0, k, x, y);
//        for (int i = 0; i < k; i++)
//        {
//            comp = comp * (x0 - x[i]);
//        }
//        sum = sum + comp;
//    }
//    return sum;
//}
//void nodeFillEquals(vector<double>& x, vector<double>& y, int n) {
//    double a = 0, b = 1;
//    double h = (b - a) / n;
//    x[0] = a;
//    y[0] = func(x[0]);
//    for (int i = 1; i < n; i++) {
//        x[i] = x[i - 1] + h;
//        y[i] = func(x[i]);
//    }
//
//}
//int main() {
//    setlocale(LC_ALL, "RUS");
//    double n = 32, a = 0, b = 1;
//    vector <double> x, y;
//    double otr = (b - a) / n;
//    double temp_x = a;
//    for (double i = 0; i <= n; i++)
//    {
//        x.push_back(temp_x);
//        y.push_back(func(temp_x));
//        temp_x += otr;
//    }
//    nodeFillEquals(x, y, n);
//    for (double i = 0; i <= n; i++)
//    {
//        cout << "Newton " << NewtonPoly(x[i], x, y, n) << endl;
//        cout << "Погрешность многочлена Ньютона " << abs(func(x[i]) - NewtonPoly(x[i], x, y, n)) << endl;
//        cout << endl;
//    }
//
//
//}



//double devided_diff(int count,vector<double> &DevidedDiffs,vector<double> &X,vector<double> &Y) {
//    if (DevidedDiffs.size() != count) {
//        double buffer_of_devideddiff = 0;
//        for (int i = 0; i <= count; i++) {
//            double Delitel = 1;
//            for (int j = 0; j <= count; j++) {
//                if (i != j) Delitel *= X[i] - X[j];
//            }
//            buffer_of_devideddiff += Y[i] / Delitel;
//        }
//        DevidedDiffs.push_back(buffer_of_devideddiff);
//        return(DevidedDiffs[count - 1]);
//    }
//    else return DevidedDiffs[count - 1];
//}
//
//void task3_main(int n0) {
//    vector<double> x(n0, 0), y(n0, 0), diff;
//    nodeFillEquals(x, y, n0);
//    for (int i = 0; i < n0; i++) {
//        cout << i << " " << devided_diff(i, diff, x, y) << endl;
//    }
//}


double Newton(double x, int n0, vector<double> &x_arr, vector<double> &y_arr){
    double sum = y_arr[0];
    for(int i = 1; i < n0; ++i){

        double F = 0;
        for(int j = 0; j <= i; ++j){

            double den = 1;
            for(int k = 0; k <= i; ++k)
                if (k != j)
                    den *= (x_arr[j] - x_arr[k]);
            F += y_arr[j]/den;
        }

        for(int k = 0; k < i; ++k)
            F *= (x - x_arr[k]);
        sum += F;
    }
    return sum;
}

void task_main3(int n0){

}