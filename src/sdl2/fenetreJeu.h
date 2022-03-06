/**
@brief Module gérant l'image sdl du plateau de jeu pendant la partie

Le module fenetrJeu gère l'image sdl du plateau de jeu pendant la partie

@file fenetreJeu.h
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Avril 2021
*/


#ifndef _FENETRE_JEU_H
#define _FENETRE_JEU_H

#include "jeu.h"

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#elif __linux__
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif

//! @brief Classe gérant l'affichage de la fenetre de jeu
class FenetreJeu
{
private:
    /**
    @brief Surface sdl du plateau de jeu
    */
    SDL_Surface* surface;

    /**
    @brief Texture sdl du plateau de jeu
    */
    SDL_Texture* texture;

    /**
    @brief Rect sdl du plateau de jeu pour l'affichage
    */
    SDL_Rect rect;

    /**
    @brief Entier non signé correspondant à la couleur de fond du plateau de jeu
    */
    Uint32 couleurFond;

    /**
    @brief Entier non signé correspondant à la couleur du serpent 1
    */
    Uint32 couleurJ1;

    /**
    @brief Entier non signé correspondant à la couleur du serpent 2
    */
    Uint32 couleurJ2;

    /**
    @brief Fonction permettant de dessiner un cercle sur la surface du plateau de jeu
    @param[in] color Couleur du cercle à dessiner
    @param[in] centreX Coordonnée X du centre du cercle à dessiner
    @param[in] centreY Coordonnée Y du centre du cercle à dessiner
    @param[in] radius Rayon du cercle à dessiner
    */
    void dessinerCercle(Uint32 color, int32_t centreX, int32_t centreY, int32_t radius);

    /**
    @brief Fonction permettant de dessiner un cercle rempli sur la surface du plateau de jeu
    @param[in] color Couleur du cercle rempli à dessiner
    @param[in] centreX Coordonnée X du centre du cercle rempli à dessiner
    @param[in] centreY Coordonnée Y du centre du cercle rempli à dessiner
    @param[in] radius Rayon du cercle rempli à dessiner
    */
    void dessinerCercleRempli(Uint32 color, int32_t centreX, int32_t centreY, int32_t radius);

    /**
    @brief Fonction permettant de dessiner un pixel sur la surface du plateau
    @param[in] color Couleur du pixel à dessiner
    @param[in] x Coordonnée x du pixel à dessiner
    @param[in] y Coorconnée y du pixel à dessiner
    */
    void setPixUnique(Uint32 color, int x, int y);



public:

    /**
    @brief Constructeur de la classe fenetreJeu
    @param[in] x Coordonnée X du début du plateau de jeu sur la fenetre finale
    @param[in] y Coordonnée Y du début du plateau de jeu sur la fenetre finale
    @param[in] w Largeur du plateau de jeu
    @param[in] h Hauteur du plateau de jeu
    */
    FenetreJeu(int x, int y, int w = 1122, int h = 630);//x et y coordonnées en haut  à gauche de la fenetre, relativement à window

    /**
    @brief Destructeur de la classe  fenetreJeu
    */
    ~FenetreJeu();

    /**
    @brief Fonction permettant de réinitialiser la surface du plateau de jeu
    */
    void clearSurface();

    /**
    @brief Fonction permettant de remplir les données membres de couleur avec les données d'un jeu en paramètre
    @param j Jeu dans lequel sont prises les données de couleur
    @warning Cette fonction doit etre appelée avant de commencer la boucle de jeu
    */
    void couleurJoueurs(const Jeu &j); // doit etre appelée avant de lancer la partie

    /**
    @brief Fonction permettant d'afficher l'image du plateau à l'écran
    @param renderer Renderer sdl gerant l'affichage de la texture du plateau
    */
    void draw(SDL_Renderer* renderer);

    /**
    @brief Fonction permettant de remplir la surface du plateau de jeu lors du mouvement des joueurs
    @param j Jeu dans lequel sont prises les données des joueursu
    */
    void fillSurfaceOnMotion(const Jeu &j);   

};

#endif