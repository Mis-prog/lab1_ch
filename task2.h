//const double PI = acos(-1.0);
//
//void nodeFillNotEquals(vector<double>& x, vector<double>& y){
//    int a=0,b=1;
//    for (int i=0;i<x.size();i++){
//        x[i]=(b+a)/2.0+((b-a)/2.0)*cos((PI*(2.0*i+1))/(2.0*x.size()));
//        y[i]= acos_foo(x[i]);
//    }
//}
//
//void task2_main(int n0){
//    vector<double> x(n0,0),y(n0,0);
//    nodeFillNotEquals(x, y);
//    ofstream out2_1;
//    out2_1.open("task2.txt");
//    for (int i = 1; i < n0; i++) {
//        out2_1 << i << " " << checkAccuracy(x,y) << endl;
//    }
//    out2_1.close();
//}
