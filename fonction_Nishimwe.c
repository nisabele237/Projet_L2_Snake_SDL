#include"fonction_Nishimwe.h"

int init_LudoNi(SDL_Window **fenetreNi, SDL_Renderer **RendererNi) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return -1;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_PNG ) == 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;        
    }

    *fenetreNi = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1200, 500, SDL_WINDOW_SHOWN);
    if (*fenetreNi == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    *RendererNi = SDL_CreateRenderer(*fenetreNi, -1, SDL_RENDERER_ACCELERATED);
    if (*RendererNi == NULL) {
        fprintf(stderr, "Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*fenetreNi);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
        if (TTF_Init() == -1) {
        SDL_Log("Erreur d'initialisation de SDL_ttf : %s", TTF_GetError());
        SDL_Quit();
        return -1;
    }
    return 0;
}

int init_TextureNi(SDL_Texture **TextureNi, SDL_Renderer **RendererNi) {
    *TextureNi = SDL_CreateTexture(*RendererNi, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 100, 100);
    if (*TextureNi == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture: %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}


int init_ImagesNi(SDL_Renderer **RendererNi, SDL_Texture **TextureNi, char *imageNi) {
    SDL_Surface *image = IMG_Load(imageNi);
    if (image == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image: %s\n", IMG_GetError());
        return -1;
    }

    *TextureNi = SDL_CreateTextureFromSurface(*RendererNi, image);
    SDL_FreeSurface(image);
    
    if (*TextureNi == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture à partir de l'image: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}
int ChargerTextureNi(SDL_Renderer **Renderer, SDL_Texture *Texture[],char *nom_fichier,int n){
    for(int i=0;i<n;i++){
        if(init_ImagesNi(Renderer,&Texture[i],nom_fichier)!=0)
        return  0;
    }
    return 1;
}

int ChargerTextureNi2(SDL_Renderer **Renderer, SDL_Texture *Texture[],char *nom_fichier[5],int n){
    for(int i=0;i<n;i++){
        if(init_ImagesNi(Renderer,&Texture[i],nom_fichier[i])!=0)
        return  0;
    }
    return 1;
}
SDL_Texture* ChargerTexturePionNi(SDL_Renderer **RendererNi, char *nom) {
    SDL_Surface *image = IMG_Load(nom);
    
    if (image == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image %s: %s\n", nom, IMG_GetError());
        return NULL;
    }

    SDL_Texture *TextureNi = SDL_CreateTextureFromSurface(*RendererNi, image);
    SDL_FreeSurface(image);  // Libérer la surface après avoir créé la texture
    
    if (TextureNi == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture à partir de l'image %s: %s\n", nom, SDL_GetError());
        return NULL;
    }
    
    return TextureNi;
}
void barre_chargement() {
    SDL_Window *fenetre = NULL;
    SDL_Renderer *Rend = NULL;
    init_LudoNi(&fenetre, &Rend);
    //Load image
    SDL_Rect b3 = {600, 200, 200, 120};
    SDL_Texture *Te1 = ChargerTexturePionNi(&Rend, "load.png");
    // Téléchargement de l'image
    SDL_RenderClear(Rend);
    SDL_Texture *Te = ChargerTexturePionNi(&Rend, "Logo.jpeg");
    SDL_RenderCopy(Rend, Te, NULL, NULL);
    SDL_RenderCopy(Rend, Te1, NULL, &b3);
    SDL_Rect b1 = {20, 430, 1180, 30};
    SDL_SetRenderDrawColor(Rend, 0, 0, 0, 255);
    SDL_RenderFillRect(Rend, &b1);

    SDL_Rect b2 = {20, 430, 0, 30};
    for (int i = 0; i < 1180; i++) {
        SDL_SetRenderDrawColor(Rend, 255, 0, 255, 255);
        SDL_RenderFillRect(Rend, &b2);
        b2.w += 1;  
        SDL_RenderPresent(Rend);  
        SDL_Delay(10);  
    }

    SDL_RenderPresent(Rend); 
    //SDL_Delay(500);

    SDL_DestroyTexture(Te);
    SDL_DestroyRenderer(Rend);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    IMG_Quit();
}
SnakeNi insertTete1Ni(SnakeNi l,SDL_Rect rectNi,SDL_Renderer **RendererNi,SDL_Texture *Texture){
  //creation de la cellule
    SnakeNi cel=malloc(sizeof(Snake));
    cel->bdNi.x=rectNi.x;
    cel->bdNi.y=rectNi.y;
    cel->bdNi.w=rectNi.w;
    cel->bdNi.h=rectNi.h;
    SDL_RenderCopy(*RendererNi,Texture,NULL,&cel->bdNi);
    cel->suivant=l;
    l=cel;
    return l;
}
SnakeNi insertTeteNi(SnakeNi l,SDL_Rect rectNi,SDL_Renderer **RendererNi,SDL_Texture *Texture){
  
     if(l==NULL){
   return insertTete1Ni(l,rectNi,RendererNi,Texture);
}
SnakeNi t;
t=malloc(sizeof(Snake));
    t->bdNi.x=rectNi.x;
    t->bdNi.y=rectNi.y;
    t->bdNi.w=rectNi.w;
    t->bdNi.h=rectNi.h;
    SDL_RenderCopy(*RendererNi,Texture,NULL,&t->bdNi);
     t->suivant=NULL;

SnakeNi inter=l;
while(inter->suivant!=NULL){
    inter=inter->suivant;
}
inter->suivant=t;
return l;
}

void ScoreNi(SDL_Renderer **renderer,  int score) {
    SDL_Color Color = {0, 0, 200, 255};  // Couleur du texte


    TTF_Font *font = TTF_OpenFont("font/OpenSans-Italic.ttf", 30);
    if (!font) {
        SDL_Log("Erreur de chargement de la police : %s", TTF_GetError());
        return;  // Ne pas détruire le renderer ici car on ne l'a pas créé dans cette fonction
    }
    char scoretext[10];
    sprintf(scoretext,"Score : %d",score);
    // Créer la surface à partir du texte
    SDL_Surface *surface1 = TTF_RenderText_Solid(font, scoretext, Color);
    if (surface1) {
        // Créer la texture à partir de la surface
        SDL_Texture *texture1 = SDL_CreateTextureFromSurface(*renderer, surface1);
        if (texture1) {  // Vérifier si la texture a été créée avec succès
            SDL_Rect Position_Nom = {1001, 30, surface1->w, surface1->h}; 

            // Dessiner la texture
            SDL_RenderCopy(*renderer, texture1, NULL, &Position_Nom);
            SDL_DestroyTexture(texture1);  
        }
    }

    SDL_FreeSurface(surface1);
    TTF_CloseFont(font);
}

void OverNi(SDL_Renderer **renderer,char over[]){
    SDL_Color Color = {255, 0, 0, 255};  // Couleur du texte


    TTF_Font *font = TTF_OpenFont("font/OpenSans-Italic.ttf", 30);
    if (!font) {
        SDL_Log("Erreur de chargement de la police : %s", TTF_GetError());
        return;  
    }
   
    SDL_Surface *surface1 = TTF_RenderText_Solid(font,over, Color);
    if (surface1) {
       
        SDL_Texture *texture1 = SDL_CreateTextureFromSurface(*renderer, surface1);
        if (texture1) { 
            SDL_Rect Position_Nom = {1001,70, surface1->w, surface1->h}; 

            // Dessiner la texture
            SDL_RenderCopy(*renderer, texture1, NULL, &Position_Nom);
            SDL_DestroyTexture(texture1);  
        }
    }

    SDL_FreeSurface(surface1);
    TTF_CloseFont(font);
    SDL_Delay(2000);
}
void plateauNi(SDL_Renderer **RendererNi){
    SDL_Rect Logo={450,0,300,50};
    SDL_Texture *logot=ChargerTexturePionNi(RendererNi,"LOGO.png");
    SDL_RenderCopy(*RendererNi,logot,NULL,&Logo);

}

void initJeuNi(SDL_Renderer **RendererNi){
// gestion du serpent(cote front)
 SDL_Rect R1={50,300,cote,cote};
 SDL_Rect R2={80,300,cote,cote};
 SDL_Rect R3={110,300,cote,cote};
 SDL_Rect R4={140,300,cote,cote};
 //serpent initial(visible)
TR[0]=ChargerTexturePionNi(RendererNi,"boule.png");
TR[1]=ChargerTexturePionNi(RendererNi,"boule.png");
TR[2]=ChargerTexturePionNi(RendererNi,"boule.png");
TR[3]=ChargerTexturePionNi(RendererNi,"boule.png");
TR[4]=ChargerTexturePionNi(RendererNi,"boule.png");
SDL_RenderCopy(*RendererNi,TR[0],NULL,&R1);
SDL_RenderCopy(*RendererNi,TR[1],NULL,&R2);
SDL_RenderCopy(*RendererNi,TR[2],NULL,&R4);
SDL_RenderCopy(*RendererNi,TR[3],NULL,&R3);
SDL_RenderCopy(*RendererNi,TR[4],NULL,&fruit);
// Incorporation dans le serpent
SerpentNi=insertTeteNi(SerpentNi,R1,RendererNi,TR[0]);
SerpentNi=insertTeteNi(SerpentNi,R2,RendererNi,TR[1]);
SerpentNi=insertTeteNi(SerpentNi,R4,RendererNi,TR[2]);
SerpentNi=insertTeteNi(SerpentNi,R3,RendererNi,TR[0]);
}


void genererfruit(SDL_Renderer **RendererNi) {
    srand(time(NULL));
    fruit.x = (rand() % (longueur / cote)) * cote;
    fruit.y = (rand() % (largeur / cote)) * cote;

    // Vérifier que le fruit n'est pas sur le serpent
    SnakeNi tmp = SerpentNi;
    while (tmp) {
        if (tmp->bdNi.x == fruit.x && tmp->bdNi.y == fruit.y) {
            genererfruit(RendererNi); 
            return;
        }
        tmp = tmp->suivant;
    }
}

void affichageNi(SDL_Renderer **RendererNi){

    SnakeNi tmp=SerpentNi;

    SDL_Texture *tex=ChargerTexturePionNi(RendererNi,"boule.png");
    while(tmp!=NULL){
        SDL_RenderCopy(*RendererNi,tex,NULL,&tmp->bdNi);
        tmp=tmp->suivant;
    }
   SDL_RenderCopy(*RendererNi,tex,NULL,&fruit);

}
void  echanger(int *x,int *y){
    int a;

    a=*x;
    *x=*y;
    *y=a;
}
//verifier si la tete du serpent touche son corps
int verifNi(SDL_Renderer **RenderNi){

    SDL_Rect k=SerpentNi->bdNi;

    SnakeNi interNi=SerpentNi->suivant;
    
    while(interNi->suivant!=NULL){  
         if(interNi->bdNi.x==k.x && interNi->bdNi.y==k.y) {
            return 1;
        }       
        interNi=interNi->suivant;            
    }
    return 0;
}
  void deplacement_droite(SDL_Renderer **RendererNi){
   if(SDL_HasIntersection(&SerpentNi->bdNi,&fruit)){
     SDL_Texture *tex=ChargerTexturePionNi(RendererNi,"boule.png");
        genererfruit(RendererNi);
        SerpentNi=insertTeteNi(SerpentNi,fruit,RendererNi,tex);
        score++;
        
    }
    SDL_Rect k=SerpentNi->bdNi,inter;
    SnakeNi interNi=SerpentNi->suivant;
    SerpentNi->bdNi.x+=30;
    while(interNi->suivant!=NULL){  
        inter.x=k.x;
        k.x=interNi->bdNi.x;
        interNi->bdNi.x=inter.x;
        inter.y=k.y;
        k.y=interNi->bdNi.y;
        interNi->bdNi.y=inter.y;
        interNi=interNi->suivant; 
   
    }
    echanger(&k.x,&interNi->bdNi.x);
    echanger(&k.y,&interNi->bdNi.y);
        if (verifNi(RendererNi)) {
       OverNi(RendererNi,"GAME OVER");
       printf("Game over\n");
        return;  
    }
    SDL_Delay(30);
    affichageNi(RendererNi);

 
}

void  deplacement_gauche(SDL_Renderer **RendererNi){
       if(SDL_HasIntersection(&SerpentNi->bdNi,&fruit)){
     SDL_Texture *tex=ChargerTexturePionNi(RendererNi,"boule.png");
        genererfruit(RendererNi);
        SerpentNi=insertTeteNi(SerpentNi,fruit,RendererNi,tex);
        score++;
   }
    SDL_Rect k=SerpentNi->bdNi,inter;
    SnakeNi interNi=SerpentNi->suivant;
    SerpentNi->bdNi.x-=30;
    while(interNi->suivant!=NULL){  
        inter.x=k.x;
        k.x=interNi->bdNi.x;
        interNi->bdNi.x=inter.x;
        inter.y=k.y;
        k.y=interNi->bdNi.y;
        interNi->bdNi.y=inter.y;
        interNi=interNi->suivant;       
    }
    echanger(&k.x,&interNi->bdNi.x);
    echanger(&k.y,&interNi->bdNi.y);
        if (verifNi(RendererNi)) {
         OverNi(RendererNi,"GAME OVER");
         printf("Game over\n");
        return;  // Tu peux ajouter une action pour arrêter le jeu ici
    }
    SDL_Delay(30);
    affichageNi(RendererNi);    

}
void  deplacement_haut(SDL_Renderer **RendererNi){
       if(SDL_HasIntersection(&SerpentNi->bdNi,&fruit)){
     SDL_Texture *tex=ChargerTexturePionNi(RendererNi,"boule.png");
        genererfruit(RendererNi);
        SerpentNi=insertTeteNi(SerpentNi,fruit,RendererNi,tex);
        score++;
   }
    SDL_Rect k=SerpentNi->bdNi,inter;
    SnakeNi interNi=SerpentNi->suivant;
    SerpentNi->bdNi.y-=30;
    while(interNi->suivant!=NULL){  
        inter.y=k.y;
        k.y=interNi->bdNi.y;
        interNi->bdNi.y=inter.y;
        
           inter.x=k.x;
        k.x=interNi->bdNi.x;
        interNi->bdNi.x=inter.x;
        interNi=interNi->suivant;            
    }
    echanger(&k.y,&interNi->bdNi.y);
    echanger(&k.x,&interNi->bdNi.x);
        if (verifNi(RendererNi)) {
        OverNi(RendererNi,"GAME OVER");
        printf("Game over\n");
        return;  
    }
    SDL_Delay(30);
    affichageNi(RendererNi);
}
void  deplacement_bas(SDL_Renderer **RendererNi){
       if(SDL_HasIntersection(&SerpentNi->bdNi,&fruit)){
     SDL_Texture *tex=ChargerTexturePionNi(RendererNi,"boule.png");
        genererfruit(RendererNi);
        SerpentNi=insertTeteNi(SerpentNi,fruit,RendererNi,tex);
        score++;
   }
    SDL_Rect k=SerpentNi->bdNi,inter;
    SnakeNi interNi=SerpentNi->suivant;
    SerpentNi->bdNi.y+=30;
    while(interNi->suivant!=NULL){  
        inter.y=k.y;
        k.y=interNi->bdNi.y;
        interNi->bdNi.y=inter.y;
        
           inter.x=k.x;
        k.x=interNi->bdNi.x;
        interNi->bdNi.x=inter.x;
        interNi=interNi->suivant;            
    }
    echanger(&k.y,&interNi->bdNi.y);
    echanger(&k.x,&interNi->bdNi.x);
    if (verifNi(RendererNi)) {
        OverNi(RendererNi,"GAME OVER");
        printf("Game over\n");
        return; 
        
    }
    SDL_Delay(30);
    affichageNi(RendererNi);
}
void deplacement(SDL_Renderer **RendererNi) {
    switch (direction) {
        case DROITE:
            deplacement_droite(RendererNi);
            break;
        case GAUCHE:
            deplacement_gauche(RendererNi);
            break;
        case HAUT:
            deplacement_haut(RendererNi);
            break;
        case BAS:
            deplacement_bas(RendererNi);
            break;
    }
}


//Si le serpent touche les frontieres
int GameOverNi(SDL_Renderer **RendererNi){
  if (SerpentNi->bdNi.x < 0 || SerpentNi->bdNi.x >= 1170 || 
        SerpentNi->bdNi.y < 0 || SerpentNi->bdNi.y >= 470) {
            return 1;

    } 


    return 0;
}


void JouerNi(SDL_Renderer **RendererNi, SDL_Window **fenetreNi) {
    SDL_Event event;
    int continuer = 1;
initJeuNi(RendererNi);
while (continuer) {    
        SDL_SetRenderDrawColor(*RendererNi,200,0,255,255);
        SDL_RenderClear(*RendererNi);
        plateauNi(RendererNi);
        affichageNi(RendererNi);
        ScoreNi(RendererNi,score);
        if(GameOverNi(RendererNi)==1){
            OverNi(RendererNi,"GAME OVER");
            printf("Game over\n");
            SDL_Delay(500);
            continuer=0;
        }

        SDL_RenderPresent(*RendererNi);
        while (SDL_PollEvent(&event)) {
        
            switch (event.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;

                case SDL_KEYDOWN:
                     if (event.key.keysym.sym == SDLK_ESCAPE) {
                        continuer = 0;
                    } else if (event.key.keysym.sym == SDLK_RIGHT && direction != GAUCHE) {
                        direction = DROITE;
                    } else if (event.key.keysym.sym == SDLK_LEFT && direction != DROITE) {
                        direction = GAUCHE;
                    } else if (event.key.keysym.sym == SDLK_UP && direction != BAS) {
                        direction = HAUT;
                    } else if (event.key.keysym.sym == SDLK_DOWN && direction != HAUT) {
                        direction = BAS;
                    }
                    break;               

                
            }

        }
        deplacement(RendererNi);
        SDL_Delay(200);
    }
    SDL_DestroyRenderer(*RendererNi);
    SDL_DestroyWindow(*fenetreNi);
    IMG_Quit();
    SDL_Quit();
    
}