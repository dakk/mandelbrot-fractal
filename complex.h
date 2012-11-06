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
