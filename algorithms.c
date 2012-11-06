/*
 * Mandelbrot fractal rendering with SDL
 * Copyright (C) 2012  Davide Gessa
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "algorithms.h"
#include "complex.h"
#include <stdio.h>
#include <string.h>

/*
 * Effettua un render catastrofico del frattale
 *  x e y sono le dimensioni delle singole celle, step e' lo step di 
 *  avanzamento, piu' e' basso, maggiore e' il dettaglio
 */
void render_big(char *name, int x, int y, double step, request_t req)
{
	char nf[1024];
	request_t current = req;
	current.reg_x0 = -2;
	current.reg_y0 = -2;
	current.reg_x1 = -2 + step;
	current.reg_y1 = -2 + step;
	
	int l = 0;
	int c = 0;
	
	while(current.reg_y0 < 2)
	{
		// Nuovo nome
		sprintf(nf, "%s_%d_%d.bmp", name, l, c);
		
		// Fa lo screen
		fract2bmp(nf, current, x, y);
		printf("writed %s\n", nf);
		
		//printf("%f %f %f %f\n", current.reg_x0, current.reg_x1, current.reg_y0, current.reg_y1);
		
		// Aggiorna le coordinate x
		current.reg_x0 += step;
		current.reg_x1 += step;
		c++;
		
		// Se arriviamo alla x massima, azzeriammo la x e scendiamo giu'
		if(current.reg_x0 >= 2)
		{
			l++; c = 0;
			current.reg_x0 = -2;
			current.reg_x1 = -2 + step;
			current.reg_y0 += step;
			current.reg_y1 += step;
		}
	}
	
	
	
}

/*
 * Pulisce la bitmap
 */
void clear(request_t *req)
{
	int x,y;
	for(x = 0; x < req->dx; x++)
		for(y = 0; y < req->dy; y++)
			req->data[y * req->dx + x] = 0;	
}


/*
 * Zoom in/out 
 */
void zoom(double value, request_t *req)
{
	double v = value;
	
	//if((req->reg_x1 * req->reg_x1 / req->reg_x1  >= 1.0) || (value < 0))
	//{
		req->reg_x0 = req->reg_x0 + v;
		req->reg_y0 = req->reg_y0 + v;
		req->reg_x1 = req->reg_x1 - v;
		req->reg_y1 = req->reg_y1 - v;
	/*}
	else
	{
		req->reg_x0 = req->reg_x0 - req->reg_x0/4;
		req->reg_y0 = req->reg_y0 - req->reg_x0/4;
		req->reg_x1 = req->reg_x1 + req->reg_x0/4;
		req->reg_y1 = req->reg_y1 + req->reg_x0/4;
	}*/
	
	//printf("x0 %f   y0 %f  x1 %f  y1 %f\n", req->reg_x0, req->reg_y0, req->reg_x1, req->reg_y1);

}


/*
 * Cambia la sezione corrente di rendering
 */
void move(double x, double y, request_t *req)
{
	req->reg_x0 = req->reg_x0 + x;
	req->reg_y0 = req->reg_y0 + y;
	req->reg_x1 = req->reg_x1 + x;
	req->reg_y1 = req->reg_y1 + y;
	//printf("x0 %f   y0 %f  x1 %f  y1 %f\n", req->reg_x0, req->reg_y0, req->reg_x1, req->reg_y1);
}



/*
 * Posiziona in xy
 */
void setpos(int x, int y, request_t *req)
{
	// 2 -> dx 
	// -2 -> 0
	// 0 -> dx / 2
	
	// 4 -> dx
	// 0 -> 0
	// 2 -> dx/2
	// x : new = dx : 4
	// new = x * 4 / dx
	double dif = req->reg_x1 - req->reg_x0;
	//(req->reg_x1 * req->reg_x1 / req->reg_x1) - (req->reg_x0 * req->reg_x0 / req->reg_x0);
	
	double newx = x * 4 / req->dx - dif / 2;	
	double newy = y * 4 / req->dy - dif / 2;	
	
	req->reg_x0 = newx;
	req->reg_y0 = newy;
	req->reg_x1 = newx + dif;
	req->reg_y1 = newy + dif;
}


/*
 * Algoritmo d mandelbrot
 */
void mandelbrot_fract_algorithm(request_t req)
{
	clear(&req);
	
    long x,y,d,i;
    double real_x,real_y;
    complex_t z,c,temp;
 
	double agg_temp;
    agg_temp=req.reg_y1;
    req.reg_y1=req.reg_y0*(-1);
    req.reg_y0=agg_temp*(-1);

	
	// Per tutta la dimensione dell'immagine
    for(x=0; x < req.dx; x++)
    {
        real_x = ((req.reg_x1-req.reg_x0)/req.dx)*x+req.reg_x0;
        for(y=0;y<req.dy;y++)
        {
            real_y = ((req.reg_y1 - req.reg_y0) / req.dy) * y + req.reg_y0;          
    
            c.real = real_x;
            c.imaginary = real_y;
            z.real = 0;
            z.imaginary = 0;
            d = 0;
            for(i=0;i<req.levels;i++)
            {
                if((z.real*z.real)+(z.imaginary*z.imaginary) > 4)
                {
                    d = i;
                    break;
                }
                temp.real = z.real;
                temp.imaginary = z.imaginary;
                z.real = (temp.real*temp.real) - (temp.imaginary*temp.imaginary) + c.real;
                z.imaginary = (temp.real*temp.imaginary)*2 + c.imaginary;
            }
            
            if(d == 0) req.data[y * req.dx + x] = 0;                     
            else req.data[y * req.dx + x] = req.cl_start + (char) d * 0x100 + (char) d * 0x10000+  (char) d * 0x1000000;
        }
    }
}

