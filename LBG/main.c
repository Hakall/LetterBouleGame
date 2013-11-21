/* 
 * File:   main.c
 * Author: Alex
 *
 * Created on 25 octobre 2013, 13:50
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


/**
 * 
 * dessiner pixel
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to set
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
 
    switch(bpp) {
    case 1:
        *p = pixel;
        break;
 
    case 2:
        *(Uint16 *)p = pixel;
        break;
 
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
 
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

/**
 * tracerCercle
 */
 void tracerCercle(SDL_Surface *ecran, int rayon, int x_centre, int y_centre, Uint32 couleur){
        int x, y, m ;
        x = 0 ;
        y = rayon ;            // on se place en haut du cercle 
        m = 5-4*rayon ;       // initialisation
        while( x <= y){      // tant qu'on est dans le second octant
                putpixel(ecran,x+x_centre, y+y_centre, couleur);
                putpixel(ecran,y+x_centre, x+y_centre , couleur);
                putpixel(ecran,-x+x_centre, y+y_centre, couleur);
                putpixel(ecran,-y+x_centre, x+y_centre, couleur);
                putpixel(ecran,x+x_centre, -y+y_centre, couleur);
                putpixel(ecran,y+x_centre, -x+y_centre, couleur);
                putpixel(ecran,-x+x_centre, -y+y_centre, couleur);
                putpixel(ecran,-y+x_centre, -x+y_centre, couleur);
                if( m > 0){ 
                        y=y - 1 ;
                        m=m-8*y ;
                }
                x=x+1;
                m=m+8*x+4 ;
        }
        SDL_Flip(ecran);
  }


/**
 * Affichage fenetre
 */
void pause()
{
    int continuer = 1;
    SDL_Event event;
  
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }

}
/*
 * main
 */
int main(int argc, char** argv) {
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran

    SDL_Init(SDL_INIT_VIDEO);
    
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
    
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE); // On tente d'ouvrir une fenêtre
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_WM_SetCaption("Letter Boule Game v0.1", NULL);
    
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_Flip(ecran);
   
    tracerCercle(ecran, 20,100, 100, SDL_MapRGB(ecran->format, 0, 0, 0));
    
    pause();
  
    SDL_Quit();
  
    return (EXIT_SUCCESS);
}

