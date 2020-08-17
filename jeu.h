//cet en-tete contient les fonction utilisées dans le jeu
#ifndef DEF_JEU
#define DEF_JEU

#include "sdl.h"

void jouer(SDL_Surface* ecran);														//fonction principale du jeu
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect* pos, int direction);	//deplace le joueur
void deplacerObjet(int* premiereCase, int* secondeCase);							//deplace un objet sur lequel on met par la suite des conditions
void recupererobjet(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect* pos);					//recupere l'objet
void deposerobjet(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect* pos);					//depose l'objet
int getdir(int olddir,int nowdir);													//cree le chemin
void cleardir();																	//efface le chemin
#endif
