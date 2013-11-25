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
 cpFloat  x;
 cpFloat y;
 cpShape *shape;
 cpBody *body;
 char lettre;
} Boule;


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

