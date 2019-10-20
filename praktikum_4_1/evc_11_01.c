// вычислительный модуль
#include "task_11_01.h"

#define _A(matrix, len, row, col) (matrix + len * row)[col]
#define L(matrix, len, row, col) (matrix + len * row)[col]
#define R(matrix, len, row, col) (matrix + len * row)[col]

// печать матрицы n * n
void print_m2(int n, double * A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*lf", 13, _A(A, n, i, j));
        } printf("\n");
    } printf("\n");
}

int evc_11_01(int n, int max_iterations, double epsilon, double * A, double * E, double * tmp, double precision) {

    for (int k = 0; k < 3000; ++k) {

        // отладочная печать
        if (var_for_debug == 1) {
            printf("==============================================");
            printf("\n\t%s %d\n", "Iteration number: ", k + 1);
            printf("==============================================\n");
        }

        for (int i = 0; i < n; ++i) R(tmp, n, 0, i) = _A(A, n, 0, i);

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 == j) {
                    L(tmp, n, i, (i - 1)) = _A(A, n, i, (i - 1)) / R(tmp, n, (i - 1), (i - 1));
                }
                if (i == j || j > i) {
                    R(tmp, n, i, j) = _A(A, n, i, j) - L(tmp, n, i, (i - 1)) * R(tmp, n, (i - 1), j);
                }
            }
        }

        if (var_for_debug == 1) {
            printf("matrix L and R\n");
            print_m2(n, tmp);
        }

        double elem_L = 0;
        double elem_R = 0;

        // перемножаем L и R
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                _A(A, n, i, j) = 0;
                for (int l = 0; l < n; ++l) {

                    if (i == l) elem_L = 1;
                    else if (i - 1 == l) elem_L = L(tmp, n, i, l);
                    else elem_L = 0;

                    if (l > j) elem_R = 0;
                    else elem_R = R(tmp, n, l, j);

                    _A(A, n, i, j) += elem_L * elem_R;
                }
            }
        }

        if (var_for_debug == 1) {
            printf("matrix after multiplication L * R\n");
            print_m2(n, A);
        }
    }

    return 0;
}
