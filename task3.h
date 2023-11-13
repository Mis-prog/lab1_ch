

double DevidedDiff(int count,vector<double> &DevidedDiffs,vector<double> &X,vector<double> &Y) {
    if (DevidedDiffs.size() != count) {
        double buffer_of_devideddiff = 0;
        for (int i = 0; i <= count; i++) {
            double Delitel = 1;
            for (int j = 0; j <= count; j++) {
                if (i != j) Delitel *= X[i] - X[j];
            }
            buffer_of_devideddiff += Y[i] / Delitel;
        }
        DevidedDiffs.push_back(buffer_of_devideddiff);
        return(DevidedDiffs[count - 1]);
    }
    else return DevidedDiffs[count - 1];
}

void NewTonEval(int gridsize, vector<double>& X, vector<double>& Y, vector<double>& XN, vector<double>& YN, double& max) {
    double summ_of_Newton = 0;
    double product_of_Newton = 1;
    vector<double> DevidedDiffs(0);
    for (int i = 0; i < gridsize; i++) {
        summ_of_Newton = 1;
        for (int j = 1; j < XN.size(); j++) {
            product_of_Newton = 1;
            for (int k = 0; k < j; k++) {
                product_of_Newton *= (X[i] - XN[k]);
            }
            summ_of_Newton += DevidedDiff(j, DevidedDiffs, XN, YN) * product_of_Newton;
        }
        if (abs(Y[i] - summ_of_Newton) > max) {
            max = abs(Y[i] - summ_of_Newton);
        }
    }
}
void NewTon(int deg) {
    int count = deg + 1;
    double max = 0;
    vector<double> X;
    vector<double> Y;
    vector<double> XN;
    vector<double> YN;

    NewTonEval(1e5, X, Y, XN, YN, max);


    cout << "max: " << max << "|||| deg: " << deg << endl;


}
