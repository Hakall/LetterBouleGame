/* 
 * File:   main.h
 * Author: Alex
 *
 * Created on 22 novembre 2013, 14:40
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct Boule {
 int  radius;
 cpFloat  x;
 cpFloat y;
 Uint8 r;
 Uint8 g;
 Uint8 b;
 Uint8 a;
 cpShape *shape;
 cpBody *body;
 char *lettre;
 boolean del;
} Boule;

Boule lesBoules[50]={0,0,0,0,0,0,0,NULL,NULL,NULL};


SDL_Surface *ecran = NULL;

cpSpace *espace= NULL;

TTF_Font *police = NULL;

int score=0;

int nbBoules=50;

int x,y,xFin,yFin=0;;

typedef struct
{
    int mousex,mousey;
    int mousexrel,mouseyrel;
    char mousebuttons[8];
        char quit;
} Input;

        
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

