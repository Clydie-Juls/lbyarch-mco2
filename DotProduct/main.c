#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x64dotfunc(int n, double *a, double *b, double* sDot);

void cDotProduct(int n, double a[], double b[], double* sDot) {
	double result = 0.0;
	for (int i = 0; i < n; i++) {
		result += a[i] * b[i];
	}
	*sDot = result;
}

void testCKernel(int n) {
	// Setting up vectors a and b
	double* a = malloc(n * sizeof(double));
	double* b = malloc(n * sizeof(double));

	// Use constant values to make this checkable
	double aValue = (double)rand() / RAND_MAX;
	double bValue = (double)rand() / RAND_MAX;

	for (int i = 0; i < n; i++) {
		a[i] = aValue;
	}

	for (int i = 0; i < n; i++) {
		b[i] = bValue;
	}

	double sDot = 0;
	double avgTimeTaken = 0.0;
	for (int i = 0; i < 20; i++) {
		clock_t start = clock();
		cDotProduct(n, a, b, &sDot);
		clock_t end = clock();

		double timeTaken = (end - start) * 1000.0 / CLOCKS_PER_SEC;
		avgTimeTaken += timeTaken;
	}

	double expectedValue = aValue * bValue * n;

	printf("Expected sDot value: %lf \n", expectedValue);
	printf("sDot value using C method: %lf \n", sDot);
	printf("Average time taken with C method: %lfms\n", avgTimeTaken / 20.0f);

	// Account for floating point error
	if ((int) sDot == (int) expectedValue) {
		printf("The C kernel output is correct (accounting for floating point error).\n");
	} else {
		printf("The C kernel output is incorrect.\n");
	}

	free(a);
	free(b);
}

void testAsmKernel(int n) {
	// Setting up vectors a and b
	double* a = malloc(n * sizeof(double));
	double* b = malloc(n * sizeof(double));

	for (int i = 0; i < n; i++) {
		a[i] = (double)rand() / RAND_MAX;
	}

	for (int i = 0; i < n; i++) {
		b[i] = (double)rand() / RAND_MAX;
	}

	double sDot = 0;
	double avgTimeTaken = 0.0;
	for (int i = 0; i < 20; i++) {
		clock_t start = clock();
		cDotProduct(n, a, b, &sDot);
		clock_t end = clock();

		double timeTaken = (end - start) * 1000.0 / CLOCKS_PER_SEC;
		avgTimeTaken += timeTaken;
	}

	double expectedValue;
	cDotProduct(n, a, b, &expectedValue);

	printf("Expected sDot value (via cDotProduct()): %lf \n", expectedValue);
	printf("sDot value using asm method: %lf \n", sDot);
	printf("Average time taken with asm method: %lfms\n", avgTimeTaken / 20.0f);

	if (sDot == expectedValue) {
		printf("The x86 kernel output is correct.\n");
	} else {
		printf("The x86 kernel output is incorrect.\n");
	}

	free(a);
	free(b);
}

int main() {
	srand(time(NULL));

	// Getting number of elements
	int n;
	printf("input number of elements: ");
	scanf_s("%d", &n);

	testCKernel(n);
	printf("\n");
	testAsmKernel(n);

	printf("\nDone");
	return 0;
}
