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
#include "sdlrender.h"
#include <SDL.h>
#include <SDL_ttf.h>


/*
 * Salva il frattale su bmp
 */
void fract2bmp(char *fn, request_t req, int x, int y)
{
	// Crea una copia della richiesta
	request_t nr = req;
	
	// Impostiamo le dimensioni
	nr.dx = x;
	nr.dy = y;
	//nr.data = (int *) malloc(sizeof(int) * nr.dx * nr.dy);
	
	// Generiamo la mappa dei bit
	//mandelbrot_fract_algorithm(nr);

	// Salviamo su un surface
	SDL_Surface *temp;
	//temp = SDL_SetVideoMode(nr.dx, nr.dy, 32, SDL_HWSURFACE);
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE, nr.dx, nr.dy, 32, 0, 0, 0, 0);
                                  
	nr.data = temp->pixels;
	mandelbrot_fract_algorithm(nr);
	
	// Salviamo iil surface su bmp
    SDL_SaveBMP(temp, fn);	
	
	// Liberiamo la memoria
	SDL_FreeSurface(temp);
	//free(nr.data);
}



/*
 * Visualizza un testo sullo schermo
 */
void sdl_draw_text(SDL_Surface *screen, TTF_Font *font, int color, char *text, SDL_Rect rcDest)
{	
	SDL_Color cl = {color};
	SDL_Surface *sText = TTF_RenderText_Solid(font, text, cl);
	SDL_BlitSurface(sText, NULL, screen, &rcDest);
	SDL_FreeSurface(sText); 
}


/*
 * Scrive un pixel sullo schermo
 */
void sdl_draw_pixel(int data, SDL_Surface *screen, int x, int y, int dx)
{
    unsigned *mem;
    unsigned cl;  
 
    //cl = SDL_MapRGB(screen->format, (data), 255, 255);
  
    mem = (unsigned*) screen->pixels  + y * dx + x;
    *mem = data;
}


/*
 * Disegna l'intera immagine su schermo
 */
void sdl_draw_surface(SDL_Surface *screen, request_t req)
{	
    int x, y;
	
    for(x = 1; x < req.dx; x++) 
    {
        for(y = 1; y < req.dy; y++) 
        {
			//printf("%d %d %d\n", x, y, data[y * dx + x]);
			sdl_draw_pixel(req.data[y * req.dx + x], screen, x, y, req.dx);
        }
    } 	
}



/*
 * Visualizza l'help sullo schermo
 */
void show_help(SDL_Surface *screen, TTF_Font *font, int color)
{
	{
		SDL_Rect rc = { 10, 10, 100, 25 };
		sdl_draw_text(screen, font, color, "+/- : zoom in / zoom out", rc);
	}
	{
		SDL_Rect rc = { 10, 25, 100, 40 };
		sdl_draw_text(screen, font, color, "up/down/left/right : 2d movement", rc);
	}
	{
		SDL_Rect rc = { 10, 40, 100, 55 };
		sdl_draw_text(screen, font, color, "5/6/7/8 : change color", rc);
	}
	{
		SDL_Rect rc = { 10, 55, 100, 70 };
		sdl_draw_text(screen, font, color, "s : create screen.bmp screenshoot", rc);
	}
	{
		SDL_Rect rc = { 10, 70, 100, 85};
		sdl_draw_text(screen, font, color, "h : show / hide this help", rc);
	}
}


/*
 * Interfaccia e mainloop
 */
void sdlrender(request_t req)
{
	// Variabili sdl
    SDL_Surface *screen;
    SDL_Event event;
    TTF_Font* font;
	SDL_Surface *cursor; 

	// Variabili di stato per il loop
    int exit = 0;
	int help = 1;
	
	// Coordinate mouse
	int mx = 30;
	int my = 30;

	// Carichiamo le cose necessarie
    if(	SDL_Init(SDL_INIT_VIDEO) < 0 || 
		!(screen = SDL_SetVideoMode(req.dx, req.dy, 32, SDL_HWSURFACE)) ||
		TTF_Init() || 
		(font = TTF_OpenFont("data/FreeSans.ttf", 14)) == NULL ||
		!(cursor = SDL_LoadBMP("data/cursor.bmp"))) 
    {
        SDL_Quit();
        return;
    }

	// Impostiamo un titolo
	SDL_WM_SetCaption("Mandelbrot fractal rendering (gessadavide@gmail.com)", NULL );

	
	// Main loop
	while(!exit)
	{	
	    if(SDL_MUSTLOCK(screen)) if(SDL_LockSurface(screen) < 0) continue;

		// Cancelliamo lo schermo
		SDL_FillRect(SDL_GetVideoSurface(), NULL, 0);
		
		// Disegnamo su schermo il frattale
		sdl_draw_surface(screen, req);
		
		// Se l'help e' attivo, disegnamolo
		if(help)
			show_help(screen, font, 1-req.cl_start+255);
		
		
		// Display cursor
		SDL_Rect offset;
		offset.x = mx - 2;
		offset.y = my - 2;
		//SDL_BlitSurface(cursor, NULL, screen, &offset ); 
		
		// Sblocchiamo lo schermo
		if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
		
		// Scriviamo la surface nell'hardware video
		SDL_Flip(screen);
  
		// Nome dello screen
		char fn[1024];
		
		// Analisi degli eventi
		while(SDL_PollEvent(&event)) 
		{   
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				// Zoom In
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					setpos(mx, my, &req);
					zoom(0.1, &req);
					mandelbrot_fract_algorithm(req); 
				}
				
				// Zoom Out
				else if(event.button.button == SDL_BUTTON_RIGHT)
				{
					zoom(-0.1, &req);
					mandelbrot_fract_algorithm(req); 
				}
				
			}   
			
			// Mouse mosso
			else if(event.type == SDL_MOUSEMOTION)
			{
				mx = event.button.x; 
				my = event.button.y; 
				
				
				//printf("%d %d\n",mx,my);
				
			}
			
			// Tastiera
			else if(event.type == SDL_KEYDOWN)
				switch(event.key.keysym.sym)
				{
					case SDLK_h:
						help = !help; 
						break;
	
					case SDLK_s:
						strcpy(fn, "screen");
						//strcat(fn, screen);
						strcat(fn, ".bmp");
						fract2bmp(fn, req, 1024, 768);
						break;
							
					case SDLK_UP:
						move(0, 0.1, &req);
						mandelbrot_fract_algorithm(req); 
						break;
									
					case SDLK_RIGHT:
						move(0.1, 0, &req);
						mandelbrot_fract_algorithm(req); 
						break;
									
					case SDLK_DOWN:
						move(0, -0.1, &req);
						mandelbrot_fract_algorithm(req); 
						break;
									
					case SDLK_LEFT:		
						move(-0.1, 0, &req);
						mandelbrot_fract_algorithm(req); 
						break;

					case SDLK_PLUS:
						zoom(0.1, &req);
						mandelbrot_fract_algorithm(req); 
						break;
						
					case SDLK_MINUS:
						zoom(-0.1, &req);
						mandelbrot_fract_algorithm(req); 
						break;
							
					// Hard Color Change
					case SDLK_5:
						req.cl_start = req.cl_start - 0xFFFF;
						req.cl_end = req.cl_end - 0xFFFF;
						mandelbrot_fract_algorithm(req); 
						break;

					case SDLK_6:
						req.cl_start = req.cl_start - 0xFFF;
						req.cl_end = req.cl_end - 0xFFF;
						mandelbrot_fract_algorithm(req); 
						break;
						
					case SDLK_7:
						req.cl_start = req.cl_start + 0xFFF;
						req.cl_end = req.cl_end + 0xFFF;
						mandelbrot_fract_algorithm(req); 
						break;
							
					case SDLK_8:
						req.cl_start = req.cl_start + 0xFFFF;
						req.cl_end = req.cl_end + 0xFFFF;
						mandelbrot_fract_algorithm(req); 
						break;
							
					case SDLK_ESCAPE:
						exit = 1;
						break;
				}
		}
	}

	// Deinizializziamo sdl
    SDL_Quit();
}
