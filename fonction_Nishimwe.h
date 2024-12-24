#ifndef FONCTION_NISHIMWE
#define FONCTION_NISHIMWE
#include <stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<unistd.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<time.h>
#define cote 50
#define largeur 500
#define longueur 1200
#define MAX_NAME_LENGTH 20
enum Direction { DROITE, GAUCHE, HAUT, BAS };
static enum Direction direction = DROITE;
//definition de la structure permettant de gerer le serpent
 struct Snake{
    SDL_Rect bdNi;
    struct Snake *suivant;
    
};
typedef struct Snake Snake;
typedef struct Snake *SnakeNi;
static SnakeNi SerpentNi;// Serpent en lui meme
static  SDL_Rect  fruit={800,300,cote,cote};// fruits a manger
static int score=0;
static SDL_Texture *TR[5]={NULL};
SnakeNi insertTeteNi(SnakeNi l,SDL_Rect rectNi,SDL_Renderer **RendererNi,SDL_Texture *Texture);
void initJeuNi(SDL_Renderer **RendererNi);
int ChargerTextureNi(SDL_Renderer **Renderer, SDL_Texture *Texture[],char *nom_fichier,int n);
int init_TextureNi(SDL_Texture **TextureNi,SDL_Renderer **RendereNi);
int init_ImagesNi(SDL_Renderer **RendererNi,SDL_Texture **TextureNi,char *image);
SDL_Texture* ChargerTexturePionNi(SDL_Renderer  **RendererNi, char *nom);
int init_LudoNi(SDL_Window **fenetreNi, SDL_Renderer **RendererNi);
void affichageNi(SDL_Renderer **RendererNi);
void deplacement_droite(SDL_Renderer **RendererNi);
void  echanger(int *x,int *y);
void plateauNi(SDL_Renderer **RendererNi);
void JouerNi(SDL_Renderer **RendererNi, SDL_Window **fenetreNi);
void barre_chargement();
void ScoreNi(SDL_Renderer **renderer,  int score);
void OverNi(SDL_Renderer **renderer,char over[]);
SnakeNi insertTete1Ni(SnakeNi l,SDL_Rect rectNi,SDL_Renderer **RendererNi,SDL_Texture *Texture);
void  deplacement_haut(SDL_Renderer **RendererNi);
void  deplacement_bas(SDL_Renderer **RendererNi);
void  deplacement_gauche(SDL_Renderer **RendererNi);
void deplacement(SDL_Renderer **RendererNi);
int GameOverNi(SDL_Renderer **RendererNi);
int verifNi(SDL_Renderer **RenderNi);
#endif