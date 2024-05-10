#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
#include <mutex>
using namespace std;

mutex mtx; // переменная класса mytex

void operation(string namethread, const int n, const double* arr1, const double* arr2, const char oper) { 

    mtx.lock(); // с этого момента выполнять функцию может лишь единственный поток одновременно
    for (int i = 0; i < n; ++i) {

        this_thread::sleep_for(chrono::milliseconds(10)); // ожидание 10 милисекунд

        if (oper == '*') {
            cout << namethread << " - umnogenie: " << arr1[i] << " * " << arr2[i] << " = " << arr1[i] * arr2[i] << endl;
        }
        else

            if (oper == '+') {
                cout << namethread << " - slogenie: " << arr1[i] << " + " << arr2[i] << " = " << arr1[i] + arr2[i] << endl;
            }

            else if (oper == 'r') {
                cout << namethread << " - random: " << rand() % 10 + 1 << endl;
            }
    }
    mtx.unlock(); 
}

int main() {

    srand(time(0)); // задание точки в системе для функции рандом

    const int n1 = 20;
    const int n2 = 25;
    const int n3 = 30;

    double arr1[n3];
    double arr2[n3];

    for (int i = 0; i < n1; ++i) {
        arr1[i] = rand() % 10 + 1;
        arr2[i] = rand() % 10 + 1;
    }

    thread thread1(operation, "thread1", n1, arr1, arr2, '*'); // в поток помещаем функцию и аргументы к ней
    thread thread2(operation, "thread2", n2, arr1, arr2, '+');
    thread thread3(operation, "thread3", n3, nullptr, nullptr, 'r'); // в данном случае arr1 и arr2 использоваться не будут, по этому nullptr

    thread1.join(); // ожидаем каждый поток
    thread2.join();
    thread3.join();

    cout << "Finally end!!!" << endl;
}

