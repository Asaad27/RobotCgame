
#include "constantes.h"
#include "jeu.h"
#include "sdl.h"
#include "fichiers.h"
#define Sds SDL_Surface

int p =0, i = 0, j = 0;
int X = 0, Y = 0;
int objdet = VIDE;
int chemin = 0;
int inventaire[3] = { VIDE };
//int Ti1Zone2[11] = {2,3,4,5,6,7,8,9,10,11,12,13}
//int Ti2Zone2[9]={3,4,5,6,7,8,9,10,11,12}
int signalobj = NEUTRE;
int anciennedir = 0;
int dir = BAS;
int cartedir[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };
int flagChemin = 0;


void jouer(SDL_Surface* ecran)
{
	Sds* pousseeON, * pousseeoff;
	Sds* robot[4] = { NULL };
	Sds* carre = NULL, * objectif = NULL, * robotActuel = NULL,
		* arrierePlan = NULL, * rect = NULL, * neutreobj = NULL, * mauvobj = NULL, * bonobj = NULL, * dirup = NULL, * dirdown = NULL, * dirleft = NULL, * dirright = NULL, * dirrightup = NULL, * dirrightdown = NULL, * dirleftup = NULL, * dirleftdown = NULL, * halfcrossdown = NULL, * halfcrossup = NULL, * halfcrossright = NULL, * halfcrossleft = NULL, * cross = NULL;
	SDL_Rect position, positionJoueur, posdetint, posdetobj, posinv, possignalobj, pousseepos;
	SDL_Event event;

	bool continuer = true, objectifsRestants = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };


	posdetint.x = LARGEUR_FENETRE - 200;			//position initale du robot
	posdetint.y = 4;

	posdetobj.x = 184;
	posdetobj.y = 466;

	posinv.y = 466;

	possignalobj.x = 250;
	possignalobj.y = 475;
	// Chargement des images, icones...
	pousseeON = chargerImage("ressources/pousseeon.png");
	pousseeoff = chargerImage("ressources/pousseeoff.png");
	arrierePlan = chargerImage("ressources/arrierePlan.png");
	carre = chargerImage("ressources/carre.png");
	objectif = chargerImage("ressources/objectif.png");
	rect = chargerImage("ressources/rect.png");
	robot[BAS] = chargerImage("ressources/robot_bas.gif");
	robot[GAUCHE] = chargerImage("ressources/robot_gauche.gif");
	robot[HAUT] = chargerImage("ressources/robot_haut.gif");
	robot[DROITE] = chargerImage("ressources/robot_droite.gif");
	neutreobj = chargerImage("ressources/neutre_obj.png");
	mauvobj = chargerImage("ressources/mauv_obj.png");
	bonobj = chargerImage("ressources/bon_obj.png");
	dirup = chargerImage("ressources/dirup.png");
	dirdown = chargerImage("ressources/dirdown.png");
	dirleft = chargerImage("ressources/dirleft.png");
	dirright = chargerImage("ressources/dirright.png");
	dirrightup = chargerImage("ressources/dirrightup.png");
	dirrightdown = chargerImage("ressources/dirrightdown.png");
	dirleftup = chargerImage("ressources/dirleftup.png");
	dirleftdown = chargerImage("ressources/dirleftdown.png");
	halfcrossdown = chargerImage("ressources/halfcrossdown.png");
	halfcrossup = chargerImage("ressources/halfcrossup.png");
	halfcrossright = chargerImage("ressources/halfcrossright.png");
	halfcrossleft = chargerImage("ressources/halfcrossleft.png");
	cross = chargerImage("ressources/cross.png");

	robotActuel = robot[BAS];															// le robot sera dirigé vers le bas au départ
																						// Chargement du niveau
	if (!chargerMap(carte))
		exit(EXIT_FAILURE);																// On arrête le jeu si on n'a pas pu charger le niveau

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)												// Recherche de la position du robot au départ
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j] == ROBOT)													// Si le robot se trouve à cette position sur la carte
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
				X = positionJoueur.x;
				Y = positionJoueur.y;
			}
		}
	}

	SDL_EnableKeyRepeat(100, 100);														// Activation de la répétition des touches
	while (continuer)
	{
		SDL_WaitEvent(&event);															//traitement des entrees de l'utilisateur
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				continuer = 0;
				break;

			case SDLK_UP:
				anciennedir = dir;
				dir = HAUT;
				if (chemin == 1)
				{
					if (cartedir[X][Y] == 0)
						cartedir[X][Y] = getdir(anciennedir, dir);

					else if (cartedir[X][Y] == DIRLEFT || cartedir[X][Y] == DIRRIGHT)
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if (cartedir[X][Y] == DIRLEFTDOWN && cartedir[X - 1][Y] == 0)
					{
						cartedir[X][Y] = DIRHALFCROSSRIGHT;
					}
					else if (cartedir[X][Y] == DIRRIGHTDOWN && cartedir[X + 1][Y] == 0)
					{
						cartedir[X][Y] = DIRHALFCROSSLEFT;
					}
					else if (cartedir[X][Y] == DIRHALFCROSSDOWN || cartedir[X][Y] == DIRHALFCROSSUP || cartedir[X][Y] == DIRHALFCROSSLEFT || cartedir[X][Y] == DIRHALFCROSSRIGHT)
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if ((cartedir[X - 1][Y] != 0 && cartedir[X][Y] == DIRLEFTDOWN) || (cartedir[X + 1][Y] != 0 && cartedir[X][Y] == DIRRIGHTDOWN))
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if (cartedir[X - 1][Y] != 0 && cartedir[X + 1][Y] != 0 && cartedir[X][Y - 1] != 0)
					{
						cartedir[X][Y] = DIRCROSS;
					}
				}
				robotActuel = robot[HAUT];
				deplacerJoueur(carte, &positionJoueur, HAUT);
				break;

			case SDLK_DOWN:
				anciennedir = dir;
				dir = BAS;
				if (chemin == 1)
				{
					if (cartedir[X][Y] == 0)
						cartedir[X][Y] = getdir(anciennedir, dir);
					else if (cartedir[X][Y] == DIRLEFT || cartedir[X][Y] == DIRRIGHT)
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if (cartedir[X][Y] == DIRRIGHTUP && cartedir[X + 1][Y] == 0)
					{
						cartedir[X][Y] = DIRHALFCROSSLEFT;
					}
					else if (cartedir[X][Y] == DIRLEFTUP && cartedir[X - 1][Y] == 0)
					{
						cartedir[X][Y] = DIRHALFCROSSRIGHT;
					}
					else if (cartedir[X][Y] == DIRHALFCROSSDOWN || cartedir[X][Y] == DIRHALFCROSSUP || cartedir[X][Y] == DIRHALFCROSSLEFT || cartedir[X][Y] == DIRHALFCROSSRIGHT)
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if ((cartedir[X][Y] == DIRRIGHTUP && cartedir[X + 1][Y] != 0) || (cartedir[X - 1][Y] == DIRLEFTUP && cartedir[X - 1][Y] != 0))
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if (cartedir[X + 1][Y] != 0 && cartedir[X - 1][Y] != 0 && cartedir[X][Y - 1] != 0)
					{
						cartedir[X][Y] = DIRCROSS;
					}
				}
				robotActuel = robot[BAS];
				deplacerJoueur(carte, &positionJoueur, BAS);
				break;

			case SDLK_RIGHT:
				anciennedir = dir;
				dir = DROITE;

				if (chemin == 1)
				{
					if (cartedir[X][Y] == 0)
						cartedir[X][Y] = getdir(anciennedir, dir);

					else if (cartedir[X][Y] == DIRUP || cartedir[X][Y] == DIRDOWN)
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if (cartedir[X][Y] == DIRRIGHTUP && cartedir[X][Y + 1] == 0)
					{
						cartedir[X][Y] = DIRHALFCROSSUP;
					}
					else if (cartedir[X][Y] == DIRRIGHTDOWN && cartedir[X][Y - 1] == 0)
					{
						cartedir[X][Y] = DIRHALFCROSSDOWN;
					}
					else if (cartedir[X][Y] == DIRHALFCROSSDOWN || cartedir[X][Y] == DIRHALFCROSSUP || cartedir[X][Y] == DIRHALFCROSSLEFT || cartedir[X][Y] == DIRHALFCROSSRIGHT)
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if ((cartedir[X][Y] == DIRLEFTUP && cartedir[X][Y + 1] != 0) || (cartedir[X][Y] == DIRLEFTDOWN && cartedir[X][Y - 1] != 0))
					{
						cartedir[X][Y] = DIRCROSS;
					}
					else if (cartedir[X][Y + 1] != 0 && cartedir[X - 1][Y] != 0 && cartedir[X][Y - 1] != 0)
					{
						cartedir[X][Y] = DIRCROSS;
					}
				}
				robotActuel = robot[DROITE];
				deplacerJoueur(carte, &positionJoueur, DROITE);
				break;

			case SDLK_LEFT:
				anciennedir = dir;
				dir = GAUCHE;
				if (chemin == 1)
				{
					if (cartedir[X][Y] == 0)
						cartedir[X][Y] = getdir(anciennedir, dir);
					else if (cartedir[X][Y] == DIRUP || cartedir[X][Y] == DIRDOWN)
						cartedir[X][Y] = DIRCROSS;
					else if (cartedir[X][Y] == DIRLEFTUP && cartedir[X][Y + 1] == 0)
						cartedir[X][Y] = DIRHALFCROSSUP;
					else if (cartedir[X][Y] == DIRLEFTDOWN && cartedir[X][Y - 1] == 0)
						cartedir[X][Y] = DIRHALFCROSSDOWN;
					else if (cartedir[X][Y] == DIRHALFCROSSDOWN || cartedir[X][Y] == DIRHALFCROSSUP || cartedir[X][Y] == DIRHALFCROSSLEFT || cartedir[X][Y] == DIRHALFCROSSRIGHT)
						cartedir[X][Y] = DIRCROSS;
					else if ((cartedir[X][Y] == DIRRIGHTUP && cartedir[X][Y + 1] != 0) || (cartedir[X][Y] == DIRRIGHTDOWN && cartedir[X][Y - 1] != 0))
						cartedir[X][Y] = DIRCROSS;
					else if (cartedir[X][Y + 1] != 0 && cartedir[X + 1][Y] != 0 && cartedir[X][Y - 1] != 0)
						cartedir[X][Y] = DIRCROSS;

				}
				robotActuel = robot[GAUCHE];
				deplacerJoueur(carte, &positionJoueur, GAUCHE);
				break;

			case SDLK_p:
				if (!p)
					p = 1;
				else
					p = 0;
				break;

			case SDLK_r:
				recupererobjet(carte, &positionJoueur);
				break;

			case SDLK_d:
				deposerobjet(carte, &positionJoueur);
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));	// Effacement de l'écran
		SDL_BlitSurface(arrierePlan, NULL, ecran, NULL);
		// Placement des objets à l'écran
		objectifsRestants = 0;

		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;
				switch (cartedir[i][j])
				{
				case DIRUP:
					SDL_BlitSurface(dirup, NULL, ecran, &position);
					break;
				case DIRDOWN:
					SDL_BlitSurface(dirdown, NULL, ecran, &position);
					break;
				case DIRLEFT:
					SDL_BlitSurface(dirleft, NULL, ecran, &position);
					break;
				case DIRRIGHT:
					SDL_BlitSurface(dirright, NULL, ecran, &position);
					break;

				case DIRRIGHTUP:
					SDL_BlitSurface(dirrightup, NULL, ecran, &position);
					break;
				case DIRRIGHTDOWN:
					SDL_BlitSurface(dirrightdown, NULL, ecran, &position);
					break;
				case DIRLEFTUP:
					SDL_BlitSurface(dirleftup, NULL, ecran, &position);
					break;
				case DIRLEFTDOWN:
					SDL_BlitSurface(dirleftdown, NULL, ecran, &position);
					break;

				case DIRHALFCROSSDOWN:
					SDL_BlitSurface(halfcrossdown, NULL, ecran, &position);
					break;
				case DIRHALFCROSSUP:
					SDL_BlitSurface(halfcrossup, NULL, ecran, &position);
					break;
				case DIRHALFCROSSLEFT:
					SDL_BlitSurface(halfcrossleft, NULL, ecran, &position);
					break;
				case DIRHALFCROSSRIGHT:
					SDL_BlitSurface(halfcrossright, NULL, ecran, &position);
					break;
				case DIRCROSS:
					SDL_BlitSurface(cross, NULL, ecran, &position);
					break;

				}

			}
		}


		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch (carte[i][j])
				{
				case CARRE:
					SDL_BlitSurface(carre, NULL, ecran, &position);
					break;
				case RECT:
					SDL_BlitSurface(rect, NULL, ecran, &position);
					break;
				case DISQUE:
					SDL_BlitSurface(objectif, NULL, ecran, &position);
					objectifsRestants = 1;
					break;
				}
			}
		}


		if (!objectifsRestants)
			continuer = 0;

		// On place le robot à la bonne position
		position.x = positionJoueur.x * TAILLE_BLOC;
		position.y = positionJoueur.y * TAILLE_BLOC;
		X = positionJoueur.x;
		Y = positionJoueur.y;

		switch (signalobj)
		{
		case NEUTRE:
			SDL_BlitSurface(neutreobj, NULL, ecran, &possignalobj);
			break;

		case BON:
			SDL_BlitSurface(bonobj, NULL, ecran, &possignalobj);
			break;

		case MAUV:
			SDL_BlitSurface(mauvobj, NULL, ecran, &possignalobj);
			break;
		}

		switch (objdet)
		{
		case CARRE:
			SDL_BlitSurface(carre, NULL, ecran, &posdetobj);
			break;

		case RECT:
			SDL_BlitSurface(rect, NULL, ecran, &posdetobj);
			break;

		case DISQUE:
			SDL_BlitSurface(objectif, NULL, ecran, &posdetobj);
			break;

		case VIDE:
			SDL_BlitSurface(NULL, NULL, ecran, &posdetobj);
			break;
		}

		for (i = 0; i < 3; i++)
		{
			posinv.x = 297 + 67 * i;
			switch (inventaire[i])
			{
			case CARRE:
				SDL_BlitSurface(carre, NULL, ecran, &posinv);
				break;

			case RECT:
				SDL_BlitSurface(rect, NULL, ecran, &posinv);
				break;

			case DISQUE:
				SDL_BlitSurface(objectif, NULL, ecran, &posinv);
				break;

			case VIDE:
				SDL_BlitSurface(NULL, NULL, ecran, &posinv);
				break;
			}
		}

		pousseepos.x = 0;
		pousseepos.y = HAUTEUR_FENETRE + 245;
		SDL_BlitSurface(robotActuel, NULL, ecran, &position);
		if (p == 0)													//activation ou desactivtion du mode poussee
		{
			SDL_SetAlpha(pousseeoff, SDL_SRCALPHA, 70);
			SDL_BlitSurface(pousseeoff, NULL, ecran, &pousseepos);

		}
		else
		{
			SDL_SetAlpha(pousseeON, SDL_SRCALPHA, 70);
			SDL_BlitSurface(pousseeON, NULL, ecran, &pousseepos);
		}
		SDL_Flip(ecran);
	}
	// Désactivation de la répétition des touches (remise à 0)
	SDL_EnableKeyRepeat(0, 0);
	// Libération des surfaces chargées
	SDL_FreeSurface(carre);
	SDL_FreeSurface(objectif);
	SDL_FreeSurface(rect);

	for (i = 0; i < 4; i++)
		SDL_FreeSurface(robot[i]);
}

void recupererobjet(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect* pos)			//fonction de recuperation des objets
{
	int obj = carte[pos->x][pos->y];
	cleardir();
	if (obj != DISQUE)
	{
		return;
	}
	chemin = 1;

	if (inventaire[0] == VIDE)
	{
		inventaire[0] = carte[pos->x][pos->y];
		carte[pos->x][pos->y] = VIDE;
		signalobj = NEUTRE;
		objdet = VIDE;

	}

	else if (inventaire[1] == VIDE)
	{
		inventaire[1] = carte[pos->x][pos->y];
		carte[pos->x][pos->y] = VIDE;
		signalobj = NEUTRE;
		objdet = VIDE;
	}

	else if (inventaire[2] == VIDE)
	{
		inventaire[2] = carte[pos->x][pos->y];
		carte[pos->x][pos->y] = VIDE;
		signalobj = NEUTRE;
		objdet = VIDE;
	}
}

void deposerobjet(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect* pos)
{
	if (carte[pos->x][pos->y] == VIDE)
	{
		if (inventaire[2] != VIDE)
		{
			carte[pos->x][pos->y] = inventaire[2];
			inventaire[2] = VIDE;
		}
		else if (inventaire[1] != VIDE)
		{
			carte[pos->x][pos->y] = inventaire[1];
			inventaire[1] = VIDE;
		}
		else if (inventaire[0] != VIDE)
		{
			carte[pos->x][pos->y] = inventaire[0];
			inventaire[0] = VIDE;
		}
	}
	if (inventaire[0] == VIDE && inventaire[1] == VIDE && inventaire[2] == VIDE)
		chemin = 0;
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect* pos, int direction)
{
	bool flag1, flag2;
	switch (direction)
	{
	case HAUT:
		if (pos->y - 1 < 0) // Si le robot dépasse l'écran, on arrête
			break;
		if (p)
		{
			flag1 = (carte[pos->x][pos->y - 1] == CARRE || carte[pos->x][pos->y - 1] == DISQUE || carte[pos->x][pos->y - 1] == RECT);
			flag2 = (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == CARRE || carte[pos->x][pos->y - 2] == DISQUE || carte[pos->x][pos->y - 2] == RECT);
			if (flag1 && flag2)
				break;
			// on verifie la possibilite du deplacement du joueur
			// On verifie le deplacement des disques
			deplacerObjet(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);
		}

		objdet = carte[pos->x][pos->y - 1];
		if (objdet == DISQUE)
			signalobj = BON;
		else if (objdet != VIDE)
			signalobj = MAUV;
		else
			signalobj = NEUTRE;
		pos->y--; // On fait monter le robot
		break;

	case BAS:
		if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
			break;

		if (p == 1)
		{
			if ((carte[pos->x][pos->y + 1] == CARRE || carte[pos->x][pos->y + 1] == DISQUE || carte[pos->x][pos->y + 1] == RECT) &&
				(pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == CARRE || carte[pos->x][pos->y + 2] == DISQUE || carte[pos->x][pos->y + 2] == RECT))
				break;
			deplacerObjet(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
		}
		objdet = carte[pos->x][pos->y + 1];

		if (objdet == DISQUE)
			signalobj = BON;
		else if (objdet != VIDE)
			signalobj = MAUV;
		else
			signalobj = NEUTRE;
		pos->y++;
		break;

	case GAUCHE:
		if (pos->x - 1 < 0)
			break;
		if (p)
		{
			if ((carte[pos->x - 1][pos->y] == CARRE || carte[pos->x - 1][pos->y] == DISQUE || carte[pos->x - 1][pos->y] == RECT) &&
				(pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == CARRE || carte[pos->x - 2][pos->y] == DISQUE || carte[pos->x - 2][pos->y] == RECT))
				break;
			deplacerObjet(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
		}
		objdet = carte[pos->x - 1][pos->y];
		if (objdet == DISQUE)
			signalobj = BON;
		else if (objdet != VIDE)
			signalobj = MAUV;
		else
			signalobj = NEUTRE;
		pos->x--;
		break;
	case DROITE:
		if (pos->x + 1 >= NB_BLOCS_LARGEUR)
			break;
		if (p)
		{
			if ((carte[pos->x + 1][pos->y] == CARRE || carte[pos->x + 1][pos->y] == DISQUE || carte[pos->x + 1][pos->y] == RECT) &&
				(pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == CARRE || carte[pos->x + 2][pos->y] == DISQUE || carte[pos->x + 2][pos->y] == RECT))
				break;
			deplacerObjet(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
		}
		objdet = carte[pos->x + 1][pos->y];
		if (objdet == DISQUE)
			signalobj = BON;
		else if (objdet != VIDE)
			signalobj = MAUV;
		else
			signalobj = NEUTRE;
		pos->x++;
		break;
	}

	if (inventaire[0] == VIDE && inventaire[1] == VIDE && inventaire[2] == VIDE)
	{
		for (int k = 3; k < 13; k++)
		{
			if ((pos->x == k && pos->y == 7) || (pos->x == k && pos->y == 6) || (pos->x == 2 && pos->y == 6) || (pos->x == 1 && pos->y == 7) || (pos->x == 13 && pos->y == 6) || (pos->x == 14 && pos->y == 7))
			{
				chemin = 0;
				flagChemin = 1;
				break;
			}
		}
	}

	if (flagChemin == 1)
	{
		for (int k = 3; k < 13; k++)
		{
			if ((pos->x == k && pos->y == 2) || (pos->x == 2 && pos->y == 2) || (pos->x == 2 && pos->y == 1) || (pos->x == 13 && pos->y == 1))
			{
				cleardir();
				flagChemin = 0;
			}
		}
	}
}

void deplacerObjet(int* premiereCase, int* secondeCase)
{
	int i = X;
	int j = Y;
	if (*premiereCase == DISQUE)
	{
		*secondeCase = *premiereCase;
		*premiereCase = VIDE;
		for (int k = 3; k < 13; k++)
		{
			if ((i == k && j == 7) || (i == k && j == 6) || (i == 2 && j == 6) || (i == 1 && j == 7) || (i == 13 && j == 6) || (i == 14 && j == 7))
			{
				chemin = 0;
				flagChemin = 1;
				break;
			}
			else
				chemin = 1;
		}
	}
}

int getdir(int olddir, int nowdir)
{
	if (olddir == HAUT && nowdir == BAS)
		return DIRUP;
	else if (olddir == GAUCHE && nowdir == DROITE)
		return DIRLEFT;
	else if (olddir == HAUT && nowdir == HAUT)
		return DIRUP;
	else if (olddir == BAS && nowdir == BAS)
		return DIRDOWN;
	else if (olddir == GAUCHE && nowdir == GAUCHE)
		return DIRLEFT;
	else if (olddir == DROITE && nowdir == DROITE)
		return DIRRIGHT;
	else if (olddir == DROITE && nowdir == HAUT)
		return DIRRIGHTUP;
	else if (olddir == DROITE && nowdir == BAS)
		return DIRRIGHTDOWN;
	else if (olddir == GAUCHE && nowdir == HAUT)
		return DIRLEFTUP;
	else if (olddir == GAUCHE && nowdir == BAS)
		return DIRLEFTDOWN;
	else if (olddir == HAUT && nowdir == DROITE)
		return DIRLEFTDOWN;
	else if (olddir == HAUT && nowdir == GAUCHE)
		return DIRRIGHTDOWN;
	else if (olddir == BAS && nowdir == DROITE)
		return DIRLEFTUP;
	else if (olddir == BAS && nowdir == GAUCHE)
		return DIRRIGHTUP;
}

void cleardir()
{
	int i, j;
	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			cartedir[i][j] = 0;
		}
	}
}
