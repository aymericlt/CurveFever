/**
@brief Implémentation de la classe FenetreJeu


@file fenetreJeu.cpp
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Avril 2021
*/

#include "fenetreJeu.h"
#define TAILLE_SPRITE 6
FenetreJeu::FenetreJeu(int x, int y, int w, int h)
{
    surface = NULL;
    texture = NULL;
    surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
    Uint32 color = SDL_MapRGB(surface->format,45,49,66);
    SDL_FillRect(surface, NULL, color);
    rect = surface->clip_rect;


    rect.x = x;
    rect.y = y;
    couleurFond = SDL_MapRGB(surface->format,45,49,66);
}

void FenetreJeu::couleurJoueurs(const Jeu &j)
{
    couleurJ1 = SDL_MapRGB(surface->format, j.getConstS1().getCouleur().getRouge(), j.getConstS1().getCouleur().getVert(), j.getConstS1().getCouleur().getBleu());
    couleurJ2 = SDL_MapRGB(surface->format, j.getConstS2().getCouleur().getRouge(), j.getConstS2().getCouleur().getVert(), j.getConstS2().getCouleur().getBleu());
}

void FenetreJeu::clearSurface()
{
    SDL_FillRect(surface, NULL, couleurFond);

}

FenetreJeu::~FenetreJeu()
{
    SDL_FreeSurface(surface);
    texture = NULL;
}


void FenetreJeu::setPixUnique(Uint32 color, int x, int y)
{
    SDL_Rect pixel;
    pixel.w = 1, pixel.h = 1;
    pixel.x = x, pixel.y = y; 
    SDL_FillRect(surface, &pixel, color);
}

void FenetreJeu::dessinerCercle(Uint32 color, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      setPixUnique(color, centreX + x, centreY - y);
      setPixUnique(color, centreX + x, centreY + y);
      setPixUnique(color, centreX - x, centreY - y);
      setPixUnique(color, centreX - x, centreY + y);
      setPixUnique(color, centreX + y, centreY - x);
      setPixUnique(color, centreX + y, centreY + x);
      setPixUnique(color, centreX - y, centreY - x);
      setPixUnique(color, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }

}

void FenetreJeu::dessinerCercleRempli(Uint32 color, int32_t centreX, int32_t centreY, int32_t radius)
{   
    int32_t ray = radius;
    while (ray > 1) {
        dessinerCercle(color, centreX, centreY, ray);
        ray--;
    }
    setPixUnique(color, centreX, centreY);

    //Tracé à la main de 4 pixel restant
    setPixUnique(color, centreX + 3, centreY + 3);
    setPixUnique(color, centreX + 3, centreY - 3);
    setPixUnique(color, centreX - 3, centreY - 3);
    setPixUnique(color, centreX - 3, centreY + 3);
}


void FenetreJeu::fillSurfaceOnMotion(const Jeu &j)
{
    if (j.t.tabCasesOccupees[j.getConstS1().x_precedent][j.getConstS1().y_precedent] == 1)
    {
        dessinerCercleRempli(couleurJ1, j.getConstS1().x_precedent * TAILLE_SPRITE, j.getConstS1().y_precedent * TAILLE_SPRITE, TAILLE_SPRITE);
    }
    if (j.t.tabCasesOccupees[j.getConstS2().x_precedent][j.getConstS2().y_precedent] == 2)
    {
        dessinerCercleRempli(couleurJ2, j.getConstS2().x_precedent * TAILLE_SPRITE, j.getConstS2().y_precedent * TAILLE_SPRITE, TAILLE_SPRITE);
    }
}

void FenetreJeu::draw(SDL_Renderer* renderer)
{
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}