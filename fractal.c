#include <malloc.h>
#include <stdio.h>
#include "complex.h"
#include "sdlrender.h"
#include "algorithms.h"


int main(int argc, char **argv)
{
	int x,y;
	
	request_t req;
	req.dx = 640;
	req.dy = 480;
	req.cl_start = -1431749881;
	req.cl_end = 0x00FFFF00;
	req.levels = 90;
	req.reg_x0 = -2;
	req.reg_x1 = 2;
	req.reg_y0 = -2;
	req.reg_y1 = 2;
	req.data = (int *) malloc(sizeof(int) * req.dx * req.dy);
	
	zoom(0.1, &req);
	//move(-.5, -.5, &req);
	for(x = 0; x < req.dx; x++)
		for(y = 0; y < req.dy; y++)
			req.data[y * req.dx + x] = 0;
			
			
	//mandelbrot_fract_algorithm(req);
	
	sdlrender(req);
	//render_big("tmp/big", 1024, 768, 0.1, req);
	return 0;
}
