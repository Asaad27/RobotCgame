//cet en-tete contient des constantes utilisees par le programme

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define TAILLE_BLOC         32 // Taille d'un bloc (carr�) en pixels
#define NB_BLOCS_LARGEUR    16
#define NB_BLOCS_HAUTEUR    8
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR


enum { HAUT, BAS, GAUCHE, DROITE };
enum { VIDE, PLEIN, CARRE, DISQUE, RECT, ROBOT};
enum {NODIR,DIRUP, DIRDOWN,DIRLEFT,DIRRIGHT,DIRCROSS, DIRLEFTUP,DIRLEFTDOWN,DIRRIGHTUP,DIRRIGHTDOWN, DIRHALFCROSSDOWN,DIRHALFCROSSUP,DIRHALFCROSSLEFT,DIRHALFCROSSRIGHT};
enum { NEUTRE, MAUV, BON };

#endif
