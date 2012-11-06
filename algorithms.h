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
