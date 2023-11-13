// CHMlab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// 6 вариант
#include <iostream>
#include <vector>
#include <cmath>
#include <random>	
#include <fstream>
// test	
using namespace std;
const double PI = 3.141592653589793;

double func(double x) {
	return sin(x)+x*cos(x);
}

/*double funcZdvig(double x) {
	return sin(x + PI) + (x + PI) * cos(x + PI);
}*/

double LagranzhPoly(double x0, vector<double> x, vector<double> y, int  n) {
	double result = 0;
	for (int i = 0; i <= n; i++) {
		double temp = y[i];
		for (int j = 0; j <= n; j++) {
			if (j != i) temp = temp * (x0 - x[j]) / (x[i] - x[j]);
			//cout << temp << "    " << (x[i] - x[j]) << "    " << (x0 - x[j]) << "\n";
		}
		result += temp;
	}
	return result;
}

void Ex1() {

	vector <double> x;
	vector <double> y_funk;
	vector <double> y_lagrange;
	vector <double> raz_vect;
	double a = 0;
	double b = 2 * PI;
	int best_n = -1;
	double best_raz = -1;

	ofstream fout;
	fout.open("DeltaN.txt");

	ofstream graphout;
	graphout.open("Graphic.txt");

	for (int n = 1; n < 16; n++) {

		double otr = (b - a) / double(n);
		double temp_x = a;
		for (int i = 0; i <= n; i++)
		{
			x.push_back(temp_x);
			y_funk.push_back(func(temp_x));
			temp_x += otr;
		}
		for (int i = 0; i <= n; i ++)
		{
			y_lagrange.push_back(LagranzhPoly(x[i], x, y_funk, n));
			cout << "x = " << x[i] << ";  y_funk = " << y_funk[i] << ";  y_lagrange=  " << y_lagrange[i] << "\n";
		}
		//cout << " \n";
		double h1 = (b - a) / 100000;
		temp_x = a;
		double raz = 0;
		for (int i = 0; i <= 100000; i++) {
			if (raz < abs(func(temp_x) - LagranzhPoly(temp_x, x, y_funk, n)))
			{
				raz = abs(func(temp_x) - LagranzhPoly(temp_x, x, y_funk, n));
			}	
			temp_x += h1;
		}
		if (n == 1)
		{
			best_n = 1;
			best_raz = raz;
		}
		else if (best_raz > raz)
		{
			best_n = n;
			best_raz = raz;
		}
		cout << "n = " << n << "; pogresh= " << raz << "\n";
		fout << n  << "," << raz << "\n";
		x.clear();
		y_funk.clear();
		y_lagrange.clear();
	}
	//////////////////////////////////////
	double otr = (b - a) / double(best_n);
	double temp_x = a;
	for (int i = 0; i <= best_n; i++)
	{
		x.push_back(temp_x);
		y_funk.push_back(func(temp_x));
		temp_x += otr;
	}
	double h1 = (b - a) / 10000, raz;
	temp_x = a;

	for (int i = 0; i < 10000; i++) {
		graphout << temp_x << "," << abs(func(temp_x) - LagranzhPoly(temp_x, x, y_funk, best_n)) << "\n";
		temp_x += h1;
	}
	cout << "best razn n =" << best_n << " " << best_raz;
}
// n0 = 15
void Ex2() {
	double temp_x=0,a=0,b= 2*PI;
	int n0 = 15;
	double otr = (b - a) /n0;
	vector <double> x, y,y_lagrange;
	for (int i = 0; i < n0; i++) {
		temp_x = (b + a) / 2 + (b - a) / 2 * cos(PI * double(2*i + 1) / double(2 * n0));
		x.push_back(temp_x);
		y.push_back(func(temp_x));
	}
	for (int i = 0; i < n0; i++)
	{
		y_lagrange.push_back(LagranzhPoly(x[i], x, y, n0-1));
		cout << x[i] << " " << y[i] << "  lagrange " << y_lagrange[i] << "\n";
	}
	double h1 = (b - a) / 100000;
	temp_x = a;
	double raz = 0;
	for (int i = 0; i <= 100000; i++) {
		if (raz < abs(func(temp_x) - LagranzhPoly(temp_x, x, y, n0-1)))
			raz = abs(func(temp_x) - LagranzhPoly(temp_x, x, y, n0-1));
		temp_x += h1;
	}
	cout << "pogresh\t" << raz << "\n";

}

double ConRaz(int a, int b, vector<double> x, vector<double> y)
{
	if (b - a != 1)
	{
		return (ConRaz(a, b - 1, x, y) - ConRaz(a + 1, b, x, y)) / (x[a] - x[b]);
	}
	else
	{
		return (y[a] - y[b]) / (x[a] - x[b]);
	}
}

double NewtonPoly(double x0, vector<double> x, vector<double> y, int n)
{
	double sum = y[0];
	for (int k = 1; k <= n; k++)
	{
		double comp = ConRaz(0, k, x, y);
		for (int i = 0; i < k; i++)
		{
			comp = comp * (x0 - x[i]);
		}
		sum = sum + comp;
	}
	return sum;
}

void Ex3() {
	double n = 15,a=0,b=2*PI;
	vector <double> x, y;
	double otr = (b - a) / double(n);
	double temp_x = a;
	for (int i = 0; i <= n; i++)
	{
		x.push_back(temp_x);
		y.push_back(func(temp_x));
		temp_x += otr;
	}
	for (int i = 0; i <= n; i++)
	{
		cout << "Lagranzh " << LagranzhPoly(x[i], x, y, n) << endl;
		cout << "Newton " << NewtonPoly(x[i], x, y, n) << endl;
		cout << "Погрешность многочлена Лагранжа: " << abs(func(x[i]) - LagranzhPoly(x[i], x, y,n)) << endl;
		cout << "Погрешность многочлена Ньютона " << abs(func(x[i]) - NewtonPoly(x[i], x, y, n)) << endl;
		cout << endl;
	}
}

double Ex4(int n , int ver)
{
	double a = 0, b = 2 * PI;
	vector <double> x, y, delta, a_koef, b_koef;
	double temp_sum = 0;
	int N = 2 * n + 1;
	for (int i = 1; i <= N; i++)
	{
		double x_temp = PI*(i-1)/ double (n+1)  - PI;
		x.push_back(x_temp);
		y.push_back(func(x_temp + PI));
		temp_sum += y[i-1];
	}

	a_koef.push_back(temp_sum / N);
	b_koef.push_back(0);
	for (int k = 1; k <= n; k++)
	{
		double tempa = 0, tempb = 0;
		for (int i = 0; i <= 2 * n; i++)
		{
			double kx = k * x[i];
			tempa += y[i] * cosl(kx);
			tempb += y[i] * sinl(kx);
		}
		a_koef.push_back( 2. / N * tempa);
		b_koef.push_back( 2. / N * tempb);
	}
	double maxraz = 0;
	if (ver == 0)
	{
		// result
		
		for (int i = 0; i <= 2*n; i++)
		{
			double res = a_koef[0];
			for (int k = 1; k < n; k++)
			{
				res += a_koef[k] * cosl( k * x[i]) + b_koef[k] * sinl(k * x[i]);
			}
			double absToday = abs(res - y[i]);
			if (absToday > maxraz)
			{
				maxraz = absToday;
			}
			//cout << res << "   and real one " << y[i] <<" " <<  x[i] + PI  << "\n";
			x[i] += PI;
		}
	}
	
	if (ver == 1)
	{	
		ofstream graphout;
		graphout.open("PointsEx4.txt");
		for (int i = 0; i <= 2 * n; i++)
		{
			double res = a_koef[0];
			for (int k = 1; k < n; k++)
			{
				res += a_koef[k] * cosl(k * x[i]) + b_koef[k] * sinl(k * x[i]);
			}
			double absToday = abs(res - y[i]);
			if (absToday > maxraz)
			{
				maxraz = absToday;
			}
			//cout << res << "   and real one " << y[i] <<" " <<  x[i] + PI  << "\n";
			x[i] += PI;
			graphout << x[i] << "," << absToday << endl;
		}
	}
	cout << "max raz = " << maxraz << "\n";
	a_koef.clear();
	b_koef.clear();
	x.clear();
	y.clear();
	return maxraz;
}
void Ex4_Point3()
{ 
	int flag = -1;
	int n = 500;
	while (flag != 1)
	{
		double temp = Ex4(n, 0);
		if (temp <= 0.001)
			flag = 1;
		else
			n += 350;
	}
	cout << " your n is " << n;
	Ex4(n, 1);
}

double T(double x, int n)
{
	if (n == 1)
	{
		return x;
	}
	else if (n == 0)
	{
		return 1.0;
	}
	else
	{
		return 2.0 * x * T(x, n - 1) - T(x, n - 2);
	}
}
double P(vector<double>& p, double x, int n)
{
	double sum = 0.0;
	for (int i = 0; i <= n; i++)
	{
		sum += p[i] * pow(x - PI, i);
	}
	return sum;
}
double Q(int n, double x, vector<double>& p) {
	double a = 0,b = 2 * PI;
	double sum;
	sum = P(p, x, n + 1) - p[n+1] * pow(2, -1 - 2 * n) * pow(b - a, n + 1) * T((2 * x - a - b) / (b - a), n + 1);
	return sum;
}
void Ex5() {
	// taylor series must be 26
	vector <double> p(26);
	p[0] = -PI;p[1] = -2;p[2] = 1.570796327;p[3] = 0.6666666667;p[4] = -0.1308996939;
	p[5] = -0.05000000000;p[6] = 0.004363323131;p[7] = 0.00158730158;p[8] = -0.00007791648447;p[9] = -0.00002755731922;p[10] = 8.657387163 * pow(10,-7);
	p[11] = 3.006253006*pow(10,-7);p[12] = -6.558626640*pow(10,-9);p[13] = -2.248266137*pow(10,-9);p[14] = 3.603641011*pow(10,-11);p[15] = 1.22354619*pow(10,-11);
	p[16] = -1.501517088*pow(10,-13);p[17] = -5.060623058*pow(10,-14);p[18] = 4.90691858*pow(10,-16);p[19] = 1.64412704*pow(10,-16);p[20] = -1.291294365*pow(10,-18);
	p[21] = -4.306047034*pow(10,-19);p[22] = 2.795009448*pow(10,-21);p[23] = 9.283608410*pow(10,-22);p[24] = -5.063422913*pow(10,-24);p[25] = -1.676207074*pow(10,-24);
	double a = 0, b = 2 * PI, delta = 0.00001;
	double h = (b - a) / 10000;
	double ourdelta=0,n=25;
	while (ourdelta<=delta)
	{	n--;
		for (int i = 0; i <= 1000; i++) {
			double x = a + i * h;
			if (abs(func(x) - Q(n, x, p)) > ourdelta) ourdelta = abs(func(x) - Q(n, x, p));
		}
		cout << "n: " << n << " delta: " << ourdelta << endl;
		
	}

	ofstream graphout;
	graphout.open("PointsEx5.txt");
	for (int i = 0; i <= 1000; i++) {
		double x = a + i * h;
		graphout << x << "," << abs(func(x) - Q(n, x, p)) << endl;
	}

}

double Ex6( int n, int var)
{ 
	// x from 0 to n -1
	double start = 0, end = 2 * PI;

	vector <double> x, y_funk, h;
	double otr = (end - start) / double(n);
	double temp_x = start;
	for (int i = 0; i <= n; i++)
	{
		x.push_back(temp_x);
		y_funk.push_back(func(temp_x));
		temp_x += otr;
	}
	h.push_back(0);
	for (int i = 1; i <= n; i++)
	{
		h.push_back(x[i] - x[i - 1]);
	}

	vector <double> P(n + 1, { 0 });
	vector <double> Q(n + 1, { 0 });
	vector <double> c(n + 1, { 0 });
	vector <double> altha(n + 1, { 0 });
	vector <double> betta(n + 1, { 1 }); 
	vector <double> gamma(n + 1, { 0 });
	vector <double> omega(n + 1, { 0 });

	for (int i = 2; i <= n; i++) // прямой ход 
	{
		altha[i-1] = h[i - 1];
		betta[i-1] = -2 * (h[i] + h[i - 1]);
		gamma[i-1] = h[i];
		omega[i-1] = 3 * ((y_funk[i] - y_funk[i - 1]) / h[i] - (y_funk[i - 1] - y_funk[i - 2]) / h[i - 1]);
	}
	for (int i = 1 ; i <= n; i++) // прямой ход 
	{
		P[i] = (- gamma[i - 1] / (altha[i - 1] * P[i - 1] - betta[ i - 1]));
		Q[i] = (omega[i - 1] - altha[i - 1] * Q[i - 1]) / (altha[ i - 1] * P[i - 1] - betta[i - 1]);
	}
	for (int i = n - 1; i > 0; i--) // обратный ход 
	{
		c[i] = P[i + 1] * c[i + 1] + Q[i + 1];
	}
	// мы получили все Ci теперь осталось вычислить каждое а,б, ц и подставить.
	vector <double> a, b, d;
	a.push_back(0);
	b.push_back(0);
	d.push_back(0);
	for (int i = 1; i < n; i++)
	{
		a.push_back(y_funk[i-1]);
		b.push_back( (y_funk[i] - y_funk[i-1])/h[i] - h[i] * (c[i+1] +2 * c[i]) / 3);
		d.push_back( (c[i + 1] - c[i]) / (3 * h[i]) );	
	}
	a.push_back(y_funk[n-1]);
	b.push_back( (y_funk[n] - y_funk[n - 1]) / h[n] - 2 * h[n] * c[n] / 3);
	d.push_back(- c[n] / (3 * h[n]));

	int kol = 10000;
	double pogr_otr = (end - start) / kol;
	vector<double> x_pogr, y_pogr_funk, y_pogr_splain;
	int flag = 1;

	//ofstream fout;
	//fout.open("Ex6_graphic.txt");
	double max_raz = 0;
	for (int i = 0; i < kol; i++)
	{
		x_pogr.push_back(start + pogr_otr * i);
		y_pogr_funk.push_back(func(x_pogr[i]));
		
		if (x_pogr[i] <= x[flag])
		{
			double delta_x = x_pogr[i] - x[flag - 1];
			y_pogr_splain.push_back(a[flag] + b[flag] * delta_x + c[flag] * delta_x * delta_x + d[flag]* delta_x* delta_x* delta_x);
		}
		else
		{
			flag++;
			double delta_x = x_pogr[i] - x[flag - 1];
			y_pogr_splain.push_back(a[flag] + b[flag] * delta_x + c[flag] * delta_x * delta_x + d[flag] * delta_x * delta_x * delta_x);
		}
		if (abs(y_pogr_funk[i] - y_pogr_splain[i]) > max_raz)
		{
			max_raz = abs(y_pogr_funk[i] - y_pogr_splain[i]);
		}
		//cout << "x = " << x_pogr[i] << " " << "y= " << y_pogr_funk[i] << "  " << "y_splain =  " << y_pogr_splain[i] << "\n";
		//fout << x_pogr[i] << "," << y_pogr_funk[i] << ","  << y_pogr_splain[i] << "\n";
	}
	x_pogr.push_back(end);
	y_pogr_funk.push_back(func(x_pogr[kol]));
	y_pogr_splain.push_back(end);

	if (var == 1)
	{
		ofstream foutN;
		foutN.open("Ex6_Mistake.txt");
		for (int i = 0; i < x_pogr.size(); i++)
		{
			foutN << x_pogr[i] << "," << abs(y_pogr_funk[i] - y_pogr_splain[i]) << "\n";
		}
	}

	if (abs(y_pogr_funk[n] - y_pogr_splain[n]) > max_raz)
	{
		max_raz = abs(y_pogr_funk[n] - y_pogr_splain[n]);
	}

	return max_raz;
}
void Ex6_point2()
{
	double pogr = 0.00001;
	int n = 1;
	double actual_pogr = Ex6(n,0);
	vector<double> Grap_of_pogr;
	Grap_of_pogr.push_back(actual_pogr);

	while (actual_pogr > pogr)
	{
		n++;
		actual_pogr = Ex6(n,0);
		Grap_of_pogr.push_back(actual_pogr);
	}
	Ex6(n, 1);
	ofstream fout;
	fout.open("Ex6_Point2_graphic.txt");

	for (int i = 0; i < Grap_of_pogr.size(); i++)
	{
		fout << i << "," << Grap_of_pogr[i] << '\n';
	}
	cout << "n is  " << n << " max raz is " << actual_pogr;

}

int main()
{

	setlocale(LC_CTYPE, "Russian");
	//Ex1();
	//Ex2();
	//Ex3();
	//Ex4(30);
	//Ex4_Point3();
	//Ex5();
	//Ex6(30);
	Ex6_point2();
	
	return 0;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
