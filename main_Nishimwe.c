#include "fonction_Nishimwe.h"
int main(){
    SDL_Window *fenetreNi=NULL;
    SDL_Renderer *RendererNi=NULL;
    //barre_chargement();
    init_LudoNi(&fenetreNi,&RendererNi);
    JouerNi(&RendererNi,&fenetreNi);
    return 0;
}