
#ifndef DEF_EDITEUR
#define DEF_EDITEUR

#include "sdl.h"

void editeur(SDL_Surface* ecran);
int chercheRobotMap(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]); /*calcul le nombre de robots présents dans la carte, et ce
                                                                    afin de pouvoir mettre une position initiale */
SDL_Rect flecheDroite(int *objetActuel, SDL_Rect posselector);
SDL_Rect flecheGauche(int *objetActuel, SDL_Rect posselector);
#endif
