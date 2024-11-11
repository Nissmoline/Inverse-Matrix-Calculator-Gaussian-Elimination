#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> 

using namespace std;

const double EPS = 1e-9;

vector<vector<double>> matrixInverse(vector<vector<double>> A, bool printIntermediate = false) {
    int n = A.size();
    vector<vector<double>> B(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        B[i][i] = 1;

    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivot][i]))
                pivot = j;
        }
        swap(A[i], A[pivot]);
        swap(B[i], B[pivot]);

        if (abs(A[i][i]) < EPS) {
            cout << "Matrix is singular.";
            exit(1);
        }

        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            for (int k = 0; k < n; k++) {
                B[j][k] -= factor * B[i][k];
            }
        }

        if (printIntermediate) {
            cout << "\nIntermediate matrix A:" << endl;
            for (const auto& row : A) {
                for (double val : row) {
                    cout << setw(12) << val << ' ';
                }
                cout << endl;
            }

            cout << "\nIntermediate matrix B:" << endl;
            for (const auto& row : B) {
                for (double val : row) {
                    cout << setw(12) << val << ' ';
                }
                cout << endl;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double factor = A[j][i] / A[i][i];
            for (int k = 0; k < n; k++) {
                B[j][k] -= factor * B[i][k];
            }
        }
        double factor = A[i][i];
        for (int k = 0; k < n; k++) {
            B[i][k] /= factor;
        }
    }

    return B;
}

void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << val << ' ';
        }
        cout << endl;
    }
}

vector<vector<double>> calculateResidualMatrix(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> residualMatrix(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double element = 0.0;
            for (int k = 0; k < n; k++) {
                element += A[i][k] * B[k][j];
            }
            if (i == j) {
                residualMatrix[i][j] = element - 1;
            }
            else {
                residualMatrix[i][j] = element;
            }
        }
    }

    return residualMatrix;
}
int main() {
    setlocale(LC_ALL, "");
    vector<vector<double>> A = {
    {3.1, 2.8, 1.9},
    {1.9, 3.1, 2.1},
    {7.5, 3.8, 4.8} };

    vector<vector<double>> inverse = matrixInverse(A, true);

    cout << "\nInverse matrix:" << std::scientific << endl;
    printMatrix(inverse);

    vector<vector<double>> residualMatrix = calculateResidualMatrix(A, inverse);
    cout << "\nResidual matrix:" << std::scientific << endl;
    printMatrix(residualMatrix);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;

}