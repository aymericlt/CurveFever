/**
@brief Implémentation de la classe Menu

@file menu.cpp
@author : professeurs LIFAP4, source pacman 
@date : Avril 2021
*/

#include "menu.h"

Menu::Menu()
{
    //Initialisation de la sdl : 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG)) || (!(IMG_Init(IMG_INIT_JPG)))) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    //creation de la fenetre : 
    window = SDL_CreateWindow("Curvefever !", 50, 50, 1280, 720, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    //creation du rendu : 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    font = TTF_OpenFont("data/fonts/cocogoose.ttf", 50);
    if (font == NULL)
        font = TTF_OpenFont("../data/fonts/cocogoose.ttf", 50);
    if (font == NULL) {
        std::cout << "Failed to load cocogoose.ttf! SDL_TTF Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    font_color1.a = 0;
    font_color2.a = 0;

    couleurJ1 = Couleur(222,10,0);
    couleurJ2 = Couleur(222,10,0);

    imMenuPresse.loadFromFile("data/img/imMenuPresse.png", renderer);
    imMenu.loadFromFile("data/img/imMenu.png", renderer);
}

Menu::~Menu()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Menu::isIn(int x, int y, int w, int h, int souris_x, int souris_y)
{
    return (((souris_x - x) <= w) && ((souris_x - x) >= 0) && ((souris_y - y) <= h) && ((souris_y - y) >= 0)) ;
    
}

void Menu::menuAff(bool sourisSurJoueur)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if (sourisSurJoueur) imMenuPresse.draw(renderer, 0,0,1280,720);
    else imMenu.draw(renderer, 0,0,1280,720);

    //affichage de joueur 1 et joueur 2 en fonction de leur couleur
    
    Image FontJoueur1;
    font_color1.r = couleurJ1.getRouge();
    font_color1.g = couleurJ1.getVert();
    font_color1.b = couleurJ1.getBleu();
    FontJoueur1.setSurface(TTF_RenderText_Solid(font, "Joueur 1", font_color1));
    SDL_Rect PositionJoueur1;
    PositionJoueur1.x = 180; PositionJoueur1.y = 275; PositionJoueur1.w = 300; PositionJoueur1.h = 85;
    FontJoueur1.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, FontJoueur1.getTexture(), NULL, &PositionJoueur1);

    Image FontJoueur2;
    font_color2.r = couleurJ2.getRouge();
    font_color2.g = couleurJ2.getVert();
    font_color2.b = couleurJ2.getBleu();
    FontJoueur2.setSurface(TTF_RenderText_Solid(font, "Joueur 2", font_color2));
    SDL_Rect PositionJoueur2;
    PositionJoueur2.x = 820; PositionJoueur2.y = 275; PositionJoueur2.w = 300; PositionJoueur2.h = 85;
    FontJoueur2.loadFromCurrentSurface(renderer);
    SDL_RenderCopy(renderer, FontJoueur2.getTexture(), NULL, &PositionJoueur2);
}

void Menu::boucleRemplissage()
{
    int x, y; //coordonnées de la souris
    bool sourisSurJoueur = false;
    bool menuRunning = true;

    while(menuRunning)
    {
        menuAff(sourisSurJoueur);
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) 
            {
                menuRunning = false;
                exit(0);
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_q:
                        menuRunning = false;
                        exit(0);
                        break;
                    default:
                        break;
                }
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&x, &y);
                if (isIn(484,495,322,112,x,y)) sourisSurJoueur = true;
                else sourisSurJoueur = false;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&x, &y);
                if (isIn(484,495,322,112,x,y)) menuRunning = false;

                //Joueur 1 couleur
                if (isIn(85,368,55,55,x,y)) couleurJ1.setCouleur(222,10,0);
                if (isIn(169,368,55,55,x,y)) couleurJ1.setCouleur(246,237,0);
                if (isIn(253,368,55,55,x,y)) couleurJ1.setCouleur(0,217,0);
                if (isIn(335,368,55,55,x,y)) couleurJ1.setCouleur(0,6,248);
                if (isIn(418,368,55,55,x,y)) couleurJ1.setCouleur(248,111,0);
                if (isIn(502,368,55,55,x,y)) couleurJ1.setCouleur(162,6,195);

                //Joueur 2 couleur
                if (isIn(725,368,55,55,x,y)) couleurJ2.setCouleur(222,10,0);
                if (isIn(809,368,55,55,x,y)) couleurJ2.setCouleur(246,237,0);
                if (isIn(892,368,55,55,x,y)) couleurJ2.setCouleur(0,217,0);
                if (isIn(974,368,55,55,x,y)) couleurJ2.setCouleur(0,6,248);
                if (isIn(1056,368,55,55,x,y)) couleurJ2.setCouleur(248,111,0);
                if (isIn(1140,368,55,55,x,y)) couleurJ2.setCouleur(162,6,195);

                
            }
        }
        SDL_RenderPresent(renderer);
    }
}