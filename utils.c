#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>
#include "utils.h"

inline double S(double x){
	if (fabs(x)<1e-10) return 0; else return x;
}

void print_times(struct timespec ts0, struct timespec ts1, clock_t c0, clock_t c1){
	printf("\tTime (WALL): %f\tTime (clock): %f\n", \
		(float) (ts1.tv_sec-ts0.tv_sec) + (float) (ts1.tv_nsec -ts0.tv_nsec)/1e9, \
		(float)(c1-c0)/CLOCKS_PER_SEC);
}

double vec_norm(double complex *a, int sz){
	int i;
	double res;

	res=0.;
	for (i=0; i<sz; i++){
		res += creal((a[i])*conj(a[i]));
	}
	return sqrt(res);
}

void norm(double complex *a, int sz){
	int i;
	double nor;

	nor = vec_norm(a, sz);

	for (i=0; i<sz; i++){
		a[i] /= nor;
	}

}

//norm-2 of the diff between 2 vectors
double diff_norm(double complex *a, double complex *b, int sz){
	int i;
	double complex *v, res;

	v = (double complex*) malloc(sz*sizeof(double complex));
	for (i=0; i<sz; i++){
		v[i] = (a[i]-b[i]);///(b[i]);
	}

	res = vec_norm(v, sz);
	free (v);
	//return vec_norm(a, sz);
	return creal(res)/vec_norm(b,sz);
}

void print_vec(double *vec, int sz){
	int i;

	if (sz<10){
		printf("  [ ");
		for (i=0; i<sz; i++) printf("% .4g, ", S(vec[i]));
		printf("\b\b ]\n");
	} else {
		printf("  [\n");
		for (i=0; i<5; i++) printf("    % .4g,\n", S(vec[i]));
		printf("    ...\n");
		for (i=sz-5; i<sz-1; i++) printf("    % .4g,\n", S(vec[i]));
		i=sz-1;
		for (i=sz-5; i<sz; i++) printf("    % .4g\n", S(vec[i]));
		printf("  ]\n");
	}
}

void print_cvec(complex double *vec, int sz){
	int i;

	if (sz<=10){
		printf("  [ ");
		for (i=0; i<sz; i++) printf("% .4g + % .4g I, ", S(creal(vec[i])), S(cimag(vec[i])));
		printf("\b\b ]\n");
	} else {
		printf("  [\n");
		for (i=0; i<3; i++) printf("    % .4g + % .4g I,\n", S(creal(vec[i])), S(cimag(vec[i])));
		printf("    ...\n");
		for (i=sz-3; i<sz-1; i++) printf("    % .4g + % .4g I,\n", S(creal(vec[i])), S(cimag(vec[i])));
		i=sz-1;
		printf("    % .4g + % .4g I\n", S(creal(vec[i])), S(cimag(vec[i])));
		printf("  ]\n");
	}
}
