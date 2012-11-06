#include "complex.h"

complex_t complex_sum(complex_t a, complex_t b)
{
	complex_t c;
	c.imaginary = a.imaginary + b.imaginary;
	c.real = a.real + b.real;
	
	return c;
}


complex_t complex_sub(complex_t a, complex_t b)
{
	complex_t c;
	c.imaginary = a.imaginary - b.imaginary;
	c.real = a.real - b.real;
	
	return c;
}
 


complex_t complex_quad(complex_t n)
{
	complex_t r;
		
	//r.imaginary = n.imaginary;
	//r.real = (n.real * n.real - n.imaginary * n.imaginary) + 2;
	
	r.imaginary = 2 * n.imaginary * n.real;
	r.real =  (n.real * n.real) - (n.imaginary * n.imaginary);
	
	return r;
}
