struct CoefFunkSpline{
    double a,b,c,d;

    CoefFunkSpline(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}
};

vector<double>&  h_set(vector<double>& x,vector<double>& y){
    vector<double> h;
    h.push_back(0);
    for (int i=1;i<=x.size();i++){
        h.push_back(x[i]-x[i-1]);
        cout << h[i] << endl;
    }
    return h;
}


void task6_main(int n0){
    vector<double> x(n0,0),y(n0,0);
    nodeFillEquals(x,y,n0);
    vector<double> h= h_set(x,y);
}