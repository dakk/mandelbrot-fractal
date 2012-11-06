#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#define ALG_MELBOURN	1
#define ALG_JULIA		2

typedef struct
{
	int algorithm;
	int *data;
	int dx;
	int dy;
	unsigned cl_start;
	int cl_end;
	int levels;
	double reg_x0;
	double reg_x1;
	double reg_y0;
	double reg_y1;
	
} request_t;


void mandelbrot_fract_algorithm(request_t);
void zoom(double, request_t *);
void move(double, double, request_t *);
void setpos(int, int, request_t *);

#endif
