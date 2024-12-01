#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x64dotfunc(int n, double *a, double *b, double* sDot);


int main() {
	// getting number of vectors
	int n;
	printf("input number of vectors: ");
	scanf_s("%d", &n);

	// setting up vector a and b
	double* a = malloc(n * sizeof(float));
	double* b = malloc(n * sizeof(float));
	double sDot = 0;

	for (int i = 0; i < n; i++) {
		a[i] = 2;
	}

	for (int i = 0; i < n; i++) {
		b[i] = 3;
	}

	// asemmbly method
	double avgTimeTaken;
	for (int i = 0; i < 20; i++) {
		clock_t start = clock();
		x64dotfunc(n, a, b, &sDot);
		clock_t end = clock();
		double timeTaken = (end - start) * 1000 / CLOCKS_PER_SEC;
		avgTimeTaken += timeTaken;
	}

	printf("sDot value using assembly method: %lf", sDot);
	printf("Average time taken with assembly method: %lf", avgTimeTaken / 20.0f);
	avgTimeTaken = 0;


	// C method
	for (int i = 0; i < 20; i++) {
		clock_t start = clock();
		sDot = dotProduct(a, b, n);
		clock_t end = clock();
		double timeTaken = (end - start) * 1000 / CLOCKS_PER_SEC;
		avgTimeTaken += timeTaken;
	}

	printf("sDot value using C method: %lf", sDot);
	printf("Average time taken with C method: %lf", avgTimeTaken / 20.0f);


	free(a);
	free(b);
	return 0;
}


double dotProduct(double a[], double b[], int n) {
	double result = 0.0;
	for (int i = 0; i < n; i++) {
		result += a[i] * b[i];
	}
	return result;
}