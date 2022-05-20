#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

using std::cout;
using std::cin;
using std::vector;

using _matrix = vector <vector <double>>;
_matrix init_matrix(int, int);

double det(vector<vector<double>>);

double dot_product (vector<double>, vector<double>);
vector<double> vector_product (_matrix);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int n, choose;
    cout << "Введите 1 для векторного произведения, 2 для скалярного\n";
    cin >> choose;
    cout << "Размер векторов:\n";
    cin >> n;

    if (choose == 1) {
        if (n < 3) {
            cout << "Невозможно найти векторное произведение\n";
            return 0;
        }
        _matrix mt = init_matrix(n - 1, n);
        for (int i = 0; i < n - 1; i++) {
            cout << "Вектор " << i + 1 << "\n";
            for (int j = 0; j < n; j++)
                cin >> mt[i][j];
        }
        cout << "Векторное произведение:\t";
        for (double el : vector_product(mt))
            cout << el << " ";
        cout << "\n";
    }
    else {
        vector<double> a(n), b(n);

        cout << "Вектор 1:\n";
        for (int i = 0; i < n; i++)
            cin >> a[i];

        cout << "Вектор 2:\n";
        for (int i = 0; i < n; i++)
            cin >> b[i];

        cout << "Скалярное произведение:\t" << dot_product(a, b) << "\n";
    }

    return 0;
}

double dot_product (vector<double> vec1, vector<double> vec2) {
    double ret;
    for (int i = 0; i < vec1.size(); i++)
        ret += vec1[i] * vec2[i];
    return ret;
}

vector<double> vector_product (_matrix mt) {
    int n = mt.size();
    vector<double> ret(n + 1);
    for (int i = 0; i < n + 1; i++) {
        _matrix tmp = mt;
        for (int j = 0; j < n; j++) {
            tmp[j].erase(tmp[j].begin() + i);
        }
        ret[i] = pow(-1, i) * det(tmp);
    }
    return ret;
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

_matrix init_matrix(int row, int col) {
    return _matrix(row, vector<double> (col));
}