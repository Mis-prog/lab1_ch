const double PI = acos(-1.0);

void nodeFillNotEquals(vector<double>& x, vector<double>& y){
    int a=0,b=1;
    for (int i=0;i<x.size();i++){
        x[i]=(b+a)/2.0+((b-a)/2.0)*cos((PI*(2.0*i+1))/(2.0*x.size()));
        y[i]= acos_foo(x[i]);
    }
}

void task2(int n0){
    vector<double> x(n0,0),y(n0,0);
    nodeFillNotEquals(x, y);
    ofstream out2_1;
    out2_1.open("task2.txt");
    double a=0,b=1;
    double h_accurace = (b - a) / 100000.0;
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
    rasnNotEquals=sup;
}

void task2_main(int n0){
    task2(n0);
    cout << rasnEquals << " " << rasnNotEquals;
}
