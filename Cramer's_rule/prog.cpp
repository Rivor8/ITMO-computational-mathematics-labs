#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;

typedef std::vector <std::vector <double>> _matrix; // Объявление типа для матриц
typedef std::vector <double> _vec; // Объявление типа для векторов

_matrix init_matrix(int, int);    // Функция для создания матрицы
void print_matrix(_matrix);       // Функция для вывода матрицы
double det(_matrix);              // Функция для нахождения определителя
_matrix cramer(_matrix, _matrix); // Функция для решения СЛАУ

int main()
{

    SetConsoleOutputCP(CP_UTF8);

    int n;
    cout << "Введите количество уравнений:";
    cin >> n;
    _matrix a = init_matrix(n, n);
    _matrix b = init_matrix(n, 1);
    cout << "Введите матрицу коэффициентов" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Строка " << i + 1 << ":";
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    cout << "Введите вектор правых частей:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> b[i][0];
    }
    cout << "Результат:" << endl;
    print_matrix(cramer(a, b));


    return 0;
}

_matrix init_matrix(int row, int col) {
    return _matrix(row, _vec(col));
}

void print_matrix(_matrix m) {
    for (auto i : m) {
        for (auto j : i) {
            cout << j << '\t';
        }
        cout << endl;
    }
}

double det(_matrix m) {
    if (m.size() == 1) {
        return m[0][0];
    }
    else {
        double sum = 0.0;
        for (int i = 0; i < m.size(); i++) {
            _matrix tmp = init_matrix(m.size() - 1, m.size() - 1);
            for (int row = 0; row < tmp.size(); row++) {
                for (int col = 0; col < tmp.size(); col++) {
                    if (col >= i) tmp[row][col] = m[row + 1][col + 1];
                    else tmp[row][col] = m[row + 1][col];
                }
            }
            sum += det(tmp) * pow(-1, i) * m[0][i];
        }
        if (abs(sum) <= 1e-7)
            return 0;

        return sum;
    }
}

_matrix cramer(_matrix a, _matrix b) {
    _matrix x = init_matrix(a.size(), 1);
    double d = det(a);
    if (d == 0) {
        cout << "СЛАУ невозможно решить методом Крамера." << endl;
        return init_matrix(1, 1);
    }
    for (int i = 0; i < a.size(); i++) {
        _matrix tmp = init_matrix(a.size(), a.size());
        tmp = a;
        for (int j = 0; j < a.size(); j++) {
            tmp[j][i] = b[j][0];
        }
        x[i][0] = det(tmp) / d;
    }
    return x;
}