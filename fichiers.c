
#include "sdl.h"
#include "constantes.h"
#include "fichiers.h"

int chargerMap(int niveau[][NB_BLOCS_HAUTEUR])						//charge la carte sauvegardee par l'utilisateur
{
	FILE* fichier = NULL;
	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR] = { 0 };
	int i = 0, j = 0, k = 0;

	fichier = fopen("niveaux.lvl", "r");							//la carte est sauvegardee dans un fichier
	if (fichier == NULL)	
		return 0;

	fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR, fichier);

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			switch (ligneFichier[k])
			{
				case '0':
					niveau[i][j] = 0;
					break;
				case '1':
					niveau[i][j] = 1;
					break;
				case '2':
					niveau[i][j] = 2;
					break;
				case '3':
					niveau[i][j] = 3;
					break;
				case '4':
					niveau[i][j] = 4;
					break;
				case '5':
					niveau[i][j] = 5;
					break;
			}
			k++;
		}

	}
	fclose(fichier);
	return 1;
}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR])		//Sauvegarde la carte dans un fichier
{
	FILE* fichier = NULL;
	int i = 0, j = 0;

	fichier = fopen("niveaux.lvl", "w");
	if (fichier == NULL)
		return 0;

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			fprintf(fichier, "%d", niveau[i][j]);
	}

	fclose(fichier);
	return 1;
}
