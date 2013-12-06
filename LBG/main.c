/* 
 * File:   main.c
 * Author: Alex
 *
 * Created on 25 octobre 2013, 13:50
 */
 
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include <chipmunk/chipmunk.h>
#include <time.h>
#include "main.h"

#define TAILLE_MAX 1000

boolean chercherMot(char *mot){
  
    FILE *entree;
    entree=fopen("dico.txt","r");
    char buff[sizeof(mot)];
    do{
       fscanf(entree,"%s",buff); 
       if(strcmp(buff,mot)){
           fclose(entree);
           return TRUE;
       } 
    }while(!feof(entree)&& strcmp(buff,mot)!=0);
    fclose(entree);
    return FALSE;
}

//couper string
char *couperString(char *s,int taille, int index){
    char *newString=NULL;
    
    if(s!NULL){
        newString=malloc(sizeof(*newString)*((taille+2)));
        if(newString!=NULL){
            int i;
            for(i=index;i<(taille+index);i++){
                newString[i-index]=s[i];
            }
            newString[i-index]="\0";
        }
        else{
            exit(EXIT_FAILURE);
        }
    }
    return newString;
}

char* algo_1( char* chaine)
{
    
 char *res=NULL;
 for(int i=sizeof(chaine);i>0;i--){
     for(int j=0;j<sizeof(chaine);j++)
        if(i+j<sizeof(chaine)){
        res=couperString(chaine,j,i);
        if(res!=NULL){
            if(chercherMot(res)){
            return res;    
            }
        }
     }
     return res;
 }
}

 void analyserLettres(int x1, int y1, int x2, int y2){
     cpBB unCpBB;
     char result[50];
     int n=0;
     for(int i=0;i<50;i++)
    { 
        unCpBB=cpBBNewForCircle(cpv(lesBoules[i].y, lesBoules[i].x ),lesBoules[i].radius);
        int intersected=cpBBIntersectsSegment(unCpBB, cpv(x1,y1),cpv(x2,y2));;
        //printf("\n %c",*lesBoules[i].lettre);
        if(intersected==1 && lesBoules[i].del==FALSE)
        {
            //on passe a true si mot trouver...algo dico
            lesBoules[i].del=TRUE;
            cpSpaceRemoveShape(espace,lesBoules[i].shape);
            cpSpaceRemoveBody(espace,lesBoules[i].body);
            //result[n]=lesBoules[i].lettre;
            n++;
        }
        
    }

 }

boolean UpdateEvents(Input* in)
{
	SDL_Event event;
	int draw=0;
	while(1)
	{
	    SDL_PollEvent(&event);
		switch (event.type)
		{
        case SDL_MOUSEMOTION:
			in->mousex=event.motion.x;
			in->mousey=event.motion.y;
			in->mousexrel=event.motion.xrel;
			in->mouseyrel=event.motion.yrel;
			xFin=in->mousexrel;
			yFin=in->mouseyrel;
			break;
		case SDL_MOUSEBUTTONDOWN:
            x=event.motion.x;
            y=event.motion.y;
            draw=1;
			in->mousebuttons[event.button.button]=1;
			break;
		case SDL_MOUSEBUTTONUP:
			in->mousebuttons[event.button.button]=0;
			if(draw){
                    xFin=event.motion.x;
                    yFin=event.motion.y;
                    lineRGBA(ecran,
                             x,
                             y,
                             xFin,
                             yFin,
                             0,100,255,255);
                    draw=0;
			}
                        analyserLettres(x,y, xFin,yFin);
            SDL_Flip(ecran);
            return TRUE;
			break;
		default:
            return FALSE;
            break;
		}
	}
}

 boolean tracerLigne(){
    Input *inputLigne;
    boolean test=UpdateEvents(inputLigne);
    if(test)return TRUE;
    else return FALSE;
}
 

 
void pause() {
    int continuer = 1;
    SDL_Event event;
    while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT: continuer = 0;
        }
    }
}
/**
 * Init
 */
cpSpace *init(){
    // cpVect is a 2D vector and cpv() is a shortcut for initializing them.
  cpVect gravity = cpv(50, 0);
  
  // Create an empty space.
  espace = cpSpaceNew();
  cpSpaceSetGravity(espace, gravity);
  
  // Add a static line segment shape for the ground.
  // We'll make it slightly tilted so the ball will roll off.
  // We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
  cpShape *ground = cpSegmentShapeNew(espace->staticBody, cpv(420, 0), cpv(420, 640), 0);
  cpShape *murGauche = cpSegmentShapeNew(espace->staticBody, cpv(0, 10), cpv(470, 10), 0);
  cpShape *murDroit = cpSegmentShapeNew(espace->staticBody, cpv(0, 630), cpv(470, 630), 0);
  cpShapeSetFriction(ground, 0.5);
  cpShapeSetFriction(murGauche, 1);
  cpShapeSetFriction(murDroit, 1);
  cpSpaceAddShape(espace, ground);
  cpSpaceAddShape(espace, murGauche);
  cpSpaceAddShape(espace, murDroit);
  
  
  return espace;  
}


char* genChar(){
    char* tabChar[50]={"E","E","E","E","E","E","S","S","S","S","A","A","A","A","T","T","T","I","I","I","I","N","N","N","R","R","R","U","U","L","L","L","O","O","D","C","P","M","V","Q","F","B","G","H","J","X","Y","Z","W","K"};
    char* lettre=tabChar[rand()% 50];
    return lettre;
}

Boule creerBoule()
{   
  cpFloat radius = rand() % 16 + 25;// radius entre 25 et 40
  cpFloat mass =  rand() % 3 + 1;// masse entre 1 et 3;
  
  cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  

  cpBody *ballBody = cpSpaceAddBody(espace, cpBodyNew(mass, moment));
  cpBodySetPos(ballBody, cpv(0, 310));
  
  cpShape *ballShape = cpSpaceAddShape(espace, cpCircleShapeNew(ballBody, radius, cpvzero));
  cpShapeSetFriction(ballShape, -0.2);
  Boule laBoule={radius, cpBodyGetPos(ballBody).x,0,rand() % 136 + 150,rand() % 136 + 100,rand() % 136 + 50,255,ballShape,ballBody, genChar(),FALSE};
  return laBoule;

  }
void initLesBoules(){
    for(int i=0;i<50;i++){        
                lesBoules[i]=creerBoule(espace); 
                };
}

void initPolice(){
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
  police = TTF_OpenFont("imagine_font.ttf", 20);
}

void affichage(){
    
    cpFloat timeStep = 1.0/60.0;
      SDL_Color white={255,255,255};
          for(cpFloat time = 0; time < 25; time += timeStep){
              SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
              for(int i=0;i<50;i++){
                  if(lesBoules[i].del==FALSE){
                 cpVect pos = cpBodyGetPos(lesBoules[i].body);
                 cpVect vel = cpBodyGetVel(lesBoules[i].body);
    
                 rectangleColor(ecran,10, 0, 630, 420,SDL_MapRGB(ecran->format,255,255,255));
                 circleRGBA(ecran, pos.y, pos.x, lesBoules[i].radius, lesBoules[i].r,lesBoules[i].g,lesBoules[i].b,lesBoules[i].a); 
                 filledCircleRGBA(ecran,pos.y,pos.x,lesBoules[i].radius, lesBoules[i].r,lesBoules[i].g,lesBoules[i].b,lesBoules[i].a);
                 
                 //lettre
                 
                 SDL_Surface *lettre= TTF_RenderText_Solid(police, lesBoules[i].lettre, white);
                 SDL_Rect position;
                 position.y=pos.x;
                 position.x=pos.y;
                 lesBoules[i].x=pos.x;
                 lesBoules[i].y=pos.y;
                 SDL_BlitSurface(lettre, NULL, ecran, &position);
                  }
                 
                 //affichage points
                 SDL_Color white={255,255,255};
                 SDL_Surface *points=TTF_RenderText_Solid(police,"Score:" , white);
                 SDL_Rect position_points;
                 position_points.y=435;
                 position_points.x=10;
                 SDL_BlitSurface(points, NULL, ecran, &position_points);
               }

                 
              cpSpaceStep(espace, timeStep);
              SDL_Flip(ecran);
          }
 SDL_Flip(ecran);
}


/*
 * main
 */
int main(int argc, char** argv) {


    espace=init();
    SDL_Event event;
    int continuer=1;
    SDL_Init(SDL_INIT_VIDEO);
    ecran=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


    
    //char* fichier_dico = "dico.txt";
    //algo_1(fichier_dico, "asdfarbre");
    if (ecran == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
     
    SDL_WM_SetCaption("Letter Boule Game !", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
    initPolice();
    initLesBoules(espace);
    boolean refresh=TRUE;
    while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT: continuer = 0;
        }
        
        if(refresh)
        {
            affichage();
            refresh=FALSE;
        }    
        SDL_Flip(ecran);
        refresh=tracerLigne();
        
        SDL_Flip(ecran);
    }   
    
    cpSpaceFree(espace);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
  
    return (EXIT_SUCCESS);
}
