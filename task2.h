const double PI = acos(-1.0);

void nodeFillNotEquals(vector<double>& x, vector<double>& y,int n0){
    int a=0,b=1;
    for (int i=0;i<n0;i++){
        x[i]=(b+a)/2.0+((b-a)/2.0)*cos((PI*(2.0*i+1))/(2.0*n0));
        y[i]= acos_foo(x[i]);
    }
}

double task2(int n0){
    vector<double> x(n0,0),y(n0,0);
    nodeFillNotEquals(x, y,n0);
    ofstream out2_1;
    out2_1.open("task2.txt");
    double a=0,b=1;
    double h_accurace = (b - a) / (double)1e5;
    double x_current = 0;
    double diff,sup=-1000;
    while (x_current<=b){
        diff=abs(acos_foo(x_current)- lagrange(x,y,x_current,n0));
        out2_1 << x_current << " " << diff << endl;
        if (diff>sup){
            sup=diff;
        }
        x_current+=h_accurace;
    }
    out2_1.close();
    return sup;
}

void task2_main(int n0){
    vector<double> x(n0,0),y(n0,0);
    nodeFillNotEquals(x, y, n0);
    cout << "Неравномерная сетка: " << task2(32)<< endl;
    x.resize(n0+1);y.resize(n0+1);
    nodeFillEquals(x,y,n0);
    cout << "Равномерная сетка: " << checkAccuracy(x,y,32);
}
