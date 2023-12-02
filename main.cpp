#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task6.h"



int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n=1;
    while (n!=0){
        switch (n) {
            case 1:
                task1_main(32);
                cin >> n;
                break;
            case 2:
                task2_main(32);
                cin >> n;
                break;
            case 3:
                task3_main(32);
                cin >> n;
                break;
            case 6:
                task6_main(5808);
                break;
        }
    }
    return 0;
}
