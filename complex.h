#ifndef COMPLEX_H
#define COMPLEX_H 

typedef struct
{
	double real;
	double imaginary;	
} complex_t;


complex_t complex_sum(complex_t, complex_t);
complex_t complex_sub(complex_t, complex_t);
complex_t complex_mul(complex_t, complex_t);
complex_t complex_div(complex_t, complex_t);
complex_t complex_pow(complex_t, int);
complex_t complex_quad(complex_t);

#endif
