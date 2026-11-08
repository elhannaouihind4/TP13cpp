#include <iostream>
using namespace std;

template <typename T, int N, int M>
class Matrice {
private:
    T data[N][M];

public:
    // Constructeur par défaut : initialise tous les éléments à 0
    Matrice() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = 0;
            }
        }
    }

    // Constructeur avec une liste d'initialisation
    Matrice(T valeurs[N][M]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = valeurs[i][j];
            }
        }
    }

    // Surcharge de l'opérateur +
    Matrice operator+(const Matrice& autre) const {
        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] = data[i][j] + autre.data[i][j];
            }
        }

        return resultat;
    }

    // Surcharge de l'opérateur -
    Matrice operator-(const Matrice& autre) const {
        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] = data[i][j] - autre.data[i][j];
            }
        }

        return resultat;
    }

    // Multiplication de deux matrices
    template <int P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {
        Matrice<T, N, P> resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                resultat.data[i][j] = 0;

                for (int k = 0; k < M; k++) {
                    resultat.data[i][j] += data[i][k] * autre.data[k][j];
                }
            }
        }

        return resultat;
    }

    // Autoriser l'accès aux données entre matrices de tailles différentes
    template <typename U, int L, int C>
    friend class Matrice;

    // Surcharge de l'opérateur <<
    friend ostream& operator<<(ostream& os, const Matrice& mat) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                os << mat.data[i][j] << "\t";
            }
            os << endl;
        }

        return os;
    }
};

int main() {

    cout << " MATRICES D'ENTIERS " << endl;

    int a[2][2] = {
        {1, 2},
        {3, 4}
    };

    int b[2][2] = {
        {5, 6},
        {7, 8}
    };

    Matrice<int, 2, 2> A(a);
    Matrice<int, 2, 2> B(b);

    cout << "\nMatrice A :" << endl;
    cout << A;

    cout << "\nMatrice B :" << endl;
    cout << B;

    cout << "\nA + B :" << endl;
    cout << A + B;

    cout << "\nA - B :" << endl;
    cout << A - B;

    cout << "\nA * B :" << endl;
    cout << A * B;


    cout << "\n MATRICES DE DOUBLE " << endl;

    double x[2][2] = {
        {1.5, 2.5},
        {3.5, 4.5}
    };

    double y[2][2] = {
        {2.0, 1.0},
        {1.0, 2.0}
    };

    Matrice<double, 2, 2> X(x);
    Matrice<double, 2, 2> Y(y);

    cout << "\nMatrice X :" << endl;
    cout << X;

    cout << "\nMatrice Y :" << endl;
    cout << Y;

    cout << "\nX + Y :" << endl;
    cout << X + Y;

    cout << "\nX * Y :" << endl;
    cout << X * Y;


    cout << "\n MULTIPLICATION 2x3 PAR 3x2 " << endl;

    int c[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int d[3][2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    Matrice<int, 2, 3> C(c);
    Matrice<int, 3, 2> D(d);

    cout << "\nMatrice C :" << endl;
    cout << C;

    cout << "\nMatrice D :" << endl;
    cout << D;

    cout << "\nC * D :" << endl;
    cout << C * D;

    return 0;
}
