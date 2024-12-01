#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern double dotfunc(int n, double a, double b, double* sdot);


int main() {
	int n;
	printf("input number of vectors: ");
	scanf("%d ", &n);

	double* a = malloc(n * sizeof(float));
	double* b = malloc(n * sizeof(float));
	double* sDot = NULL;

	for (int i = 0; i < n; i++) {
		printf("enter vector a %d value: ", i + 1);
		scanf("%lf", a + i);
	}

	for (int i = 0; i < n; i++) {
		printf("enter vector b %d value: ", i + 1);
		scanf("%lf", b + i);
	}



	free(a);
	free(b);

	return 0;
}