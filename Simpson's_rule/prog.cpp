#include <iostream>
#include <vector>
#include <windows.h>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

double func(int, double);
double simpson(int, int, double*);
std::pair <double, double> get_ab (int);

int main () {

    SetConsoleOutputCP(CP_UTF8);

    cout << "Выберите функцию для интегрирования:" << endl;
    cout << "1. f(x) = x^2, x ∈ [-5; 5];" << endl;
    cout << "2. f(x) = sin^2(x), x ∈ [-π; π];" << endl;
    cout << "3. f(x) = sin2x + cos7x + 8, x ∈ [-π; π];" << endl;
    cout << "4. f(x) = 2x^4 + x^3 + 2x^2 + 3x + 24, x ∈ [-1; 3];" << endl;
    cout << "5. f(x) = ln(x^2 + 1) + sin(x/3) + 17, x ∈ [-100; 100];" << endl;
    cout << "6. f(x) = 5^x + sin(x) + x + 11, x ∈ [-π; π];" << endl;
    cout << "7. f(x) = x^5 + 2x^4 + 3x^3 + 4x^2 + 5x + 6, x ∈ [-7; 7];" << endl;

    int choose, steps;
    double R, res;
    cin >> choose;

    cout << "Введите число шагов разбиения:" << endl;
    cin >> steps;

    res = simpson(choose, steps, &R);
    cout << "Значение интеграла: " << res << endl;
    cout << "Остаточный член: " << R << endl;

}

double func(int choose, double x) {
    switch (choose) {
        case 1:
            return x * x;
        case 2:
            return pow(sin(x), 2);
        case 3:
            return sin(2 * x) + cos(7 * x) + 8;
        case 4:
            return 2 * pow(x, 4) + pow(x, 3) + 2 * pow(x, 2) + 3 * x + 24;
        case 5:
            return log(x * x + 1) + sin(x/3) + 17;
        case 6:
            return pow(5, x) + sin(x) + x + 11;
        case 7:
            return pow(x, 5) + 2 * pow(x, 4) + 3 * pow(x, 3) + 4 * x * x + 5 * x + 6;
        default:
            return -1;
    }
}

std::pair <double, double> get_ab (int choose) {
    if (choose == 1) return std::pair<double, double>(-5, 5);
    else if (choose == 2 || choose == 3 || choose == 6) return std::pair<double, double>(-M_PI, M_PI);
    else if (choose == 4) return std::pair<double, double>(-1, 3);
    else if (choose == 5) return std::pair<double, double>(-100, 100);
    else if (choose == 7) return std::pair<double, double>(-7, 7);
    else return std::pair<double, double>(0, 0);
}

double simpson(int choose, int steps, double *R) {
    double a = get_ab(choose).first,
        b = get_ab(choose).second,
        delta, ret, s1, s2, def, max_def = 0;

    delta = (b - a) / steps;
    s1 = a;
    s2 = a + delta;
    ret = 0;


    for (int i = 0; i < steps; i++) {
        ret += (s2 - s1) / 6 * (func(choose, s1) + 4 * func(choose, (s1 + s2) / 2) + func(choose, s2));
        s1 = s2;
        s2 += delta;
        def = abs(func(choose, s1 + 2 * delta) - 4 * func(choose, s1 + delta) + 6 * func(choose, s1) - 4 * func(choose, s1 - delta) + func(choose, s1 - 2 * delta));
        if (def > max_def) max_def = def;
    }

    *R = - (b - a) * pow(delta, 4) / 180 * max_def;

    return ret;
}
