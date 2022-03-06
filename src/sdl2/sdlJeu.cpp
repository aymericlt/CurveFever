#include "sdlJeu.h"
#include <cassert>

#define fps 20
#define window_width 1280
#define window_height 720
#define TAILLE_SPRITE 6

//commencer avec une fenetre avec terrain vide et mettre des points à la main dans le main.



// ============= CLASS SDLJEU =============== //

sdlJeu::sdlJeu(unsigned int tailleX, unsigned int tailleY, Couleur couleur1, Couleur couleur2):jeu(tailleX, tailleY, couleur1, couleur2), fenetreJeu(0,90)
{
    //Initialisation de la sdl : 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG)) || (!(IMG_Init(IMG_INIT_JPG)))) {
        cout << "SDL_image could not initialize! SDL_image Error: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Creation de la fenetre : 
    window = SDL_CreateWindow("Curvefever !", 50, 50, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Creation du rendu : 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Initialisation des polices d'écriture
    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    font24 = TTF_OpenFont("data/fonts/cocogoose.ttf", 24);
    if (font24 == NULL)
        font24 = TTF_OpenFont("../data/fonts/cocogoose.ttf", 24);
    if (font24 == NULL) {
            cout << "Erreur lors du chargement de cocogoose.ttf! SDL_TTF Error: " << SDL_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    font32 = TTF_OpenFont("data/fonts/cocogoose.ttf", 32);
    if (font32 == NULL)
        font32 = TTF_OpenFont("../data/fonts/cocogoose.ttf", 32);
    if (font32 == NULL) {
            cout << "Erreur lors du chargement de cocogoose.ttf! SDL_TTF Error: " << SDL_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    font48 = TTF_OpenFont("data/fonts/cocogoose.ttf", 48);
    if (font48 == NULL)
        font48 = TTF_OpenFont("../data/fonts/cocogoose.ttf", 48);
    if (font48 == NULL) {
            cout << "Erreur lors du chargement de cocogoose.ttf! SDL_TTF Error: " << SDL_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    font64 = TTF_OpenFont("data/fonts/cocogoose.ttf", 64);
    if (font64 == NULL)
        font64 = TTF_OpenFont("../data/fonts/cocogoose.ttf", 64);
    if (font64 == NULL) {
            cout << "Erreur lors du chargement de cocogoose.ttf! SDL_TTF Error: " << SDL_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    //Initialisation des couleurs
    blanc.r = 255;
    blanc.g = 255;
    blanc.b = 255;
    blanc.a = 255;

    grisEcriture.r = 216;
    grisEcriture.g = 213;
    grisEcriture.b = 219;
    grisEcriture.a = 255;

    //Chargement des images;
    imageTitreJeu.loadFromFile("data/img/imTitreJeu.png", renderer);
    imageDroiteJeu.loadFromFile("data/img/imDroiteJeu.png", renderer);
    imQuitterPresse.loadFromFile("data/img/imQuitterPresse.png", renderer);
    imQuitter.loadFromFile("data/img/imQuitter.png", renderer);
    imRecommencerPresse.loadFromFile("data/img/imRecommencerPresse.png", renderer);
    imRecommencer.loadFromFile("data/img/imRecommencer.png", renderer);

    //Chargement des images des tetes de serpents
    for(int i = 0; i < 6; i++)
    {
        string istr = to_string(i);
        string str = "data/img/teteSerpent" + istr + ".png";
        char filename[60];
        strcpy(filename, str.c_str());
        imTeteSerpent[i].loadFromFile(filename, renderer);
    }
    
    gameRunning = false;
    fenetreJeu.couleurJoueurs(jeu);
}

sdlJeu::~sdlJeu()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlJeu::renderCenterText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = 1122/2 - src.w/2 + p_x;
	dst.y = 630/2 - src.h/2 + p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
}

bool sdlJeu::isIn(int x, int y, int w, int h, int souris_x, int souris_y)
{
    return (((souris_x - x) <= w) && ((souris_x - x) >= 0) && ((souris_y - y) <= h) && ((souris_y - y) >= 0)) ;
}

void sdlJeu::renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
}


void sdlJeu::recommencerPartie() {
    //On vide le tableau entièrement
    for (unsigned int i = 0; i < jeu.t.getTailleX(); i++) {
        for (unsigned int j = 0; j < jeu.t.getTailleY(); j++) {
            jeu.t.tabCasesOccupees[i][j] = 0;
        }
    }
    
    //On réinitialise la position des serpents, leur direction et leur état
    jeu.getS1().setTeteX(10);
    jeu.getS1().setTeteY(10);
    jeu.getS1().setVivant(true);
    jeu.getS1().setDirection(0);
    
    
    jeu.getS2().setTeteX(jeu.t.getTailleX() - 10);
    jeu.getS2().setTeteY(jeu.t.getTailleY() - 10);
    jeu.getS2().setVivant(true);
    jeu.getS2().setDirection(180);

}


void sdlJeu::sdlActionsAutomatiques()
{
    //On appelle les actions automatiques de la classe jeu, puis on met à jour le terrain
    jeu.actionsAutomatiquesSDL();
    fenetreJeu.fillSurfaceOnMotion(jeu);
}

void sdlJeu::afficherTeteSerpent(SDL_Renderer* renderer, Serpent S) {
    SDL_Rect dst;
	dst.x = S.getTeteX() * TAILLE_SPRITE - 3.5*TAILLE_SPRITE;
	dst.y = S.getTeteY() * TAILLE_SPRITE - 3.5*TAILLE_SPRITE + 90;
	dst.w = 40;
	dst.h = 40;
    //En fonction de la couleur du serpent, on appelle la fonction qui oriente sa tête avec une image différente, pour que
    //la tête du serpent soit de la même couleur que sa queue
    if(S.getCouleur().getRouge() == 222) SDL_RenderCopyEx(renderer, imTeteSerpent[0].getTexture(), NULL, &dst, S.getDirection() , NULL, SDL_FLIP_NONE);
    if(S.getCouleur().getRouge() == 246) SDL_RenderCopyEx(renderer, imTeteSerpent[1].getTexture(), NULL, &dst, S.getDirection() , NULL, SDL_FLIP_NONE);
    if(S.getCouleur().getVert() == 217) SDL_RenderCopyEx(renderer, imTeteSerpent[2].getTexture(), NULL, &dst, S.getDirection() , NULL, SDL_FLIP_NONE);
    if(S.getCouleur().getVert() == 6) SDL_RenderCopyEx(renderer, imTeteSerpent[3].getTexture(), NULL, &dst, S.getDirection() , NULL, SDL_FLIP_NONE);
    if(S.getCouleur().getRouge() == 248) SDL_RenderCopyEx(renderer, imTeteSerpent[4].getTexture(), NULL, &dst, S.getDirection() , NULL, SDL_FLIP_NONE);
    if(S.getCouleur().getRouge() == 162) SDL_RenderCopyEx(renderer, imTeteSerpent[5].getTexture(), NULL, &dst, S.getDirection() , NULL, SDL_FLIP_NONE);
    
}

void sdlJeu::sdlAff(bool boutonRecommencer, bool boutonQuitter)
{
    //Remplir l'écran de noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Affichage de la fenetre de jeu
    fenetreJeu.draw(renderer);

    //Affichage de la barre du dessus avec le titre
    imageTitreJeu.draw(renderer,0,0);
    imageDroiteJeu.draw(renderer,1122, 90);

    if (boutonRecommencer) imRecommencerPresse.draw(renderer, 1151, 400);
    else imRecommencer.draw(renderer, 1151, 400);

    if (boutonQuitter) imQuitterPresse.draw(renderer, 1151, 600);
    else imQuitter.draw(renderer, 1151, 600);

    //Affichage du score des joueurs
    char txt[4];

    sprintf(txt, "%d", jeu.getS1().getScore());
    renderText(240, 10, txt, font48, grisEcriture);

    sprintf(txt, "%d", jeu.getS2().getScore());
    renderText(1225, 10, txt, font48, grisEcriture);


    //Affichage du texte "Partie en 5 points"
    renderText(1135, 200, "Partie en", font24, grisEcriture);
    renderText(1135, 230, "5 points", font24, grisEcriture);

    //Affichage de la tête de chaque serpent
    afficherTeteSerpent(renderer, jeu.getConstS1());
    afficherTeteSerpent(renderer, jeu.getConstS2());

}

void sdlJeu::sdlBoucle()
{
    gameRunning = true; //Tant que celle valeur est vraie, on reste dans la boucle
    int x, y = 0; // pour les coordonnées de la souris
    bool bouttonQuitter = false;
    bool bouttonRecommencer = false;
    //Quatre booleen qui indiquent quelles touches sont pressees et donc quelles actions faire, de base aucune touche n'est pressee
    bool J1GaucheAppuye = false;
    bool J1DroiteAppuye = false;
    bool J2GaucheAppuye = false;
    bool J2DroiteAppuye = false;


    Uint32 starting_ticks = SDL_GetTicks(), ticks;
    SDL_Event events;

    
    while(gameRunning) //On reste dans la boucle tant que le jeu continu
    {
        if (jeu.getConstS1().getVivant() && jeu.getConstS2().getVivant()) //On entre dans ce if si les deux joueurs sont encore vivants
        {
            ticks = SDL_GetTicks();
            if (ticks - starting_ticks > 1000 / fps) //La fréquence d'entrée dans ce if peut varier en modifiant la valeur fps
            {
                //On appelles les actions automatiques, ce qui met à jour le terrain visuellement
                sdlActionsAutomatiques();

                //En fonctions des touches actuellements pressees jeu.actionClavierSDL va modifier les trajectoires des serpents
                jeu.actionClavierSDL(J1GaucheAppuye, J1DroiteAppuye, J2GaucheAppuye, J2DroiteAppuye);
                starting_ticks = ticks;

                //On regarde si la souris survole l'un des deux boutons
                bouttonRecommencer=isIn(1151, 400, 100, 50, x, y);
                bouttonQuitter=isIn(1151,600,100,50,x,y);

                //On affiche le jeu
                sdlAff(bouttonRecommencer, bouttonQuitter);
                SDL_RenderPresent(renderer);

            }

            while(SDL_PollEvent(&events)) //On met à jour les touches pressees par les joueurs
            {
                switch (events.type) {
                    case SDL_QUIT:
                        gameRunning = false;
                        break;
                    case SDL_KEYDOWN:
                        switch (events.key.keysym.sym) {
                            case SDLK_q:
                                J1GaucheAppuye = true;
                                break;
                            case SDLK_d:
                                  J1DroiteAppuye = true;
                                break;
                            case SDLK_k:
                                J2GaucheAppuye = true;
                                break;
                            case SDLK_m:
                                J2DroiteAppuye = true;
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        switch (events.key.keysym.sym) {
                            case SDLK_q:
                                J1GaucheAppuye = false;
                                break;
                            case SDLK_d:
                                J1DroiteAppuye = false;
                                break;
                            case SDLK_k:
                                J2GaucheAppuye = false;
                                break;
                            case SDLK_m:
                                J2DroiteAppuye = false;
                                break;
                        }
                        break;
                    //On regarde également si la souris à bougé pour gérer les boutons
                    case SDL_MOUSEMOTION:
                        SDL_GetMouseState(&x, &y);
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (bouttonQuitter) {gameRunning=false; exit(0);}
                        if (bouttonRecommencer) //Si le boutons recommencer est selectionné on recommence toute la partie
                        {
                            fenetreJeu.clearSurface();
                            recommencerPartie();
                            J1GaucheAppuye = false;
                            J1DroiteAppuye = false;
                            J2GaucheAppuye = false;
                            J2DroiteAppuye = false;
                            SDL_SetRenderDrawColor(renderer, 20, 20, 50, 255);
                            SDL_RenderClear(renderer);
                            jeu.getS1().augmenterScore(- (jeu.getS1().getScore()));
                            jeu.getS2().augmenterScore(- (jeu.getS2().getScore()));
                        }

                }
            }
        } 
        else if ((jeu.getConstS1().getScore() == 4 && jeu.getConstS1().getVivant()) || (jeu.getConstS2().getScore() == 4 && jeu.getConstS2().getVivant())) //On entre dans ce if si l'un des joueurs à gagné
        {
            if (!jeu.getConstS1().getVivant()) jeu.getS2().augmenterScore(1);      
            else jeu.getS1().augmenterScore(1);
            bool reprendrePartie = false;
            while (!reprendrePartie) 
            {
                ticks = SDL_GetTicks();
                if (ticks - starting_ticks > 1000 / fps)
                {
                    starting_ticks = ticks;

                    bouttonRecommencer=isIn(1151, 400, 100, 50, x, y);
                    bouttonQuitter=isIn(1151,600,100,50,x,y);

                    sdlAff(bouttonRecommencer, bouttonQuitter);
                    if (!jeu.getConstS1().getVivant()) renderCenterText(0, -10, "JOUEUR 2 A GAGNE LA PARTIE", font64, blanc); 
                    else renderCenterText(0, -10, "JOUEUR 1 A GAGNE LA PARTIE", font64, blanc);
                    renderCenterText(0, 40, "Appuyez sur espace pour commencer", font32, blanc);
                    renderCenterText(0, 70, "une nouvelle partie", font32, blanc);
                
                    SDL_RenderPresent(renderer);
                }
                while(SDL_PollEvent(&events)) 
                {
                    if (events.type == SDL_QUIT) 
                    {
                        gameRunning = false;        // Si l'utilisateur a clique sur la croix de fermeture
                        reprendrePartie = true;
                    }
                    else if (events.type == SDL_MOUSEMOTION)
                    {
                        SDL_GetMouseState(&x, &y);
                    }
                    else if (events.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if (bouttonQuitter) {gameRunning=false; exit(0);}
                        if (bouttonRecommencer)
                        {
                            fenetreJeu.clearSurface();
                            reprendrePartie = true;
                            recommencerPartie();
                            J1GaucheAppuye = false;
                            J1DroiteAppuye = false;
                            J2GaucheAppuye = false;
                            J2DroiteAppuye = false;
                            SDL_SetRenderDrawColor(renderer, 20, 20, 50, 255);
                            SDL_RenderClear(renderer);
                            jeu.getS1().augmenterScore(- (jeu.getS1().getScore()));
                            jeu.getS2().augmenterScore(- (jeu.getS2().getScore()));
                        } 
                    }
                    else if (events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_SPACE) 
                    {
                        fenetreJeu.clearSurface();
                        reprendrePartie = true;
                        recommencerPartie();
                        J1GaucheAppuye = false;
                        J1DroiteAppuye = false;
                        J2GaucheAppuye = false;
                        J2DroiteAppuye = false;
                        SDL_SetRenderDrawColor(renderer, 20, 20, 50, 255);
                        SDL_RenderClear(renderer);
                        jeu.getS1().augmenterScore(- (jeu.getS1().getScore()));
                        jeu.getS2().augmenterScore(- (jeu.getS2().getScore()));
                    }
                }
            }
        } 
        else //Si l'un des joueurs et mort, et que l'autre n'a pas gagné, on arrive dans cette partie
        {
            if (!jeu.getConstS1().getVivant()) jeu.getS2().augmenterScore(1);      
            else jeu.getS1().augmenterScore(1);
            renderCenterText(0, 10, "Appuyez sur espace pour continuer", font32, blanc);
            SDL_RenderPresent(renderer);
            bool reprendrePartie = false;
            while (!reprendrePartie) 
            {
                ticks = SDL_GetTicks();
                if (ticks - starting_ticks > 1000 / fps)
                {
                    starting_ticks = ticks;

                    bouttonRecommencer=isIn(1151, 400, 100, 50, x, y);
                    bouttonQuitter=isIn(1151,600,100,50,x,y);

                    sdlAff(bouttonRecommencer, bouttonQuitter);
                    if (!jeu.getConstS1().getVivant()) renderCenterText(0, -20, "Joueur 1 est mort", font32, blanc); 
                    else renderCenterText(0, -20, "Joueur 2 est mort", font32, blanc);
                    renderCenterText(0, 10, "Appuyez sur espace pour continuer", font32, blanc);

                    
                
                    SDL_RenderPresent(renderer);
                }
                while(SDL_PollEvent(&events)) {
                    if (events.type == SDL_QUIT) {
                        gameRunning = false;        // Si l'utilisateur a clique sur la croix de fermeture
                        reprendrePartie = true;
                    }
                    else if (events.type == SDL_MOUSEMOTION)
                    {
                        SDL_GetMouseState(&x, &y);
                    }
                    else if (events.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if (bouttonQuitter) {gameRunning=false; exit(0);}
                        if (bouttonRecommencer)
                        {
                            fenetreJeu.clearSurface();
                            reprendrePartie = true;
                            recommencerPartie();
                            J1GaucheAppuye = false;
                            J1DroiteAppuye = false;
                            J2GaucheAppuye = false;
                            J2DroiteAppuye = false;
                            SDL_SetRenderDrawColor(renderer, 20, 20, 50, 255);
                            SDL_RenderClear(renderer);
                            jeu.getS1().augmenterScore(- (jeu.getS1().getScore()));
                            jeu.getS2().augmenterScore(- (jeu.getS2().getScore()));
                        } 
                    }
                    else if (events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_SPACE) {
                        fenetreJeu.clearSurface();
                        reprendrePartie = true;
                        recommencerPartie();
                        J1GaucheAppuye = false;
                        J1DroiteAppuye = false;
                        J2GaucheAppuye = false;
                        J2DroiteAppuye = false;
                        SDL_SetRenderDrawColor(renderer, 20, 20, 50, 255);
                        SDL_RenderClear(renderer);
                    }
                }
            }
        }

    }


}