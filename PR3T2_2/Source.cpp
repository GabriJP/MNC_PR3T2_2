#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <mkl.h>
int main(int argc, char *argv[]){
	double A[25] = {
		1, 2, 0, 0, 0,
		3, 4, 5, 0, 0,
		0, 6, 7, 8, 0,
		0, 0, 9, 10, 11,
		0, 0, 0, 12, 13 };
	double Ab[20] = {
		0, 0, 0, 0, 0,
		0, 2, 5, 8, 11,
		1, 4, 7, 10, 13,
		3, 6, 9, 12, 0 };
	double B[5] = { 1, 2, 3, 4, 5 };
	double X[5];
	int pivot[5];
	int result;
	memcpy(X, B, 5 * sizeof(double));
	result = LAPACKE_dgesv(LAPACK_ROW_MAJOR, 5, 1, A, 5, pivot, X, 1);
	if (result != 0){
		fprintf(stderr, "Fallo en dgesv: %d\n", result);
		return 1;
	}
	printf("Solucion general:\n");
	for (int i = 0; i < 5; i++) printf("%lf\n", X[i]);
	result = LAPACKE_dgbsv(LAPACK_ROW_MAJOR, 5, 1, 1, 1, Ab, 5, pivot, B, 1);
	if (result != 0){
		fprintf(stderr, "Fallo en dgbsv: %d\n", result);
		return 1;
	}
	printf("\n\nSolucion en bandas:\n");
	for (int i = 0; i < 5; i++) printf("%lf\n", B[i]);
	std::getchar();
	return 0;
}