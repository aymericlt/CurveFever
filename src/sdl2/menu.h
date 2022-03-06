/**
@brief Module gérant le menu de la partie

Le module Menu l'affichage du menu et la saisie d'informations avant la partie

@file menu.h
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Avril 2021
*/

#ifndef MENU_H
#define MENU_H

#include "Couleur.h"
#include "Image.h"
#include <iostream>

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


//! @brief Classe gérant le menu de la partie
class Menu
{
private:
    /**
    @brief Image du menu avec souris sur Jouer
    */
    Image imMenuPresse;

    /**
    @brief Image du menu
    */
    Image imMenu;

    /**
    @brief Fenetre du menu
    */
	SDL_Window* window;

    /**
    @brief Renderer du menu pour l'affichage
    */
	SDL_Renderer* renderer;

    /**
    @brief Pour traiter les evenements de la souris ou du clavier
    */
	SDL_Event event;

    /**
    @brief Police d'affichage
    */
	TTF_Font* font;

    /**
    @brief Couleur de la police du joueur1
    */
	SDL_Color font_color1;

    /**
    @brief Couleur de la police du joueur2
    */
    SDL_Color font_color2;

    /**
    @brief Fonction d'affichage du menu
    */
    void menuAff(bool sourisSurJoueur);

public:

    /**
    @brief Constructeur par défaut de la classe Menu
    */
    Menu();

    /**
    @brief Destructeur de la classe Menu
    */
    ~Menu();

    /**
    @brief Fonction de boucle qui permet de saisir les informations nécessaires et d'afficher le menu
    */
    void boucleRemplissage();

    /**
    @brief Fonction permettant de savoir si la souris est dans une hitbox
    @param[in] x Coordonnée en x du point en haut à gauche de la hitbox
    @param[in] y Coordonnée en y du point en haut à gauche de la hitbox
    @param[in] w Largeur de la hitbox
    @param[in] h Hauteur de la hitbox
    @param[in] souris_x Coordonnée en x de la souris
    @param[in] souris_y Coordonnée en y de la souris
    @return bool
    */
    bool isIn(int x, int y, int w, int h, int souris_x, int souris_y);

    /**
    @brief Couleur du joueur 1
    */
    Couleur couleurJ1;

    /**
    @brief Couleur du joueur 2
    */
    Couleur couleurJ2;
};

#endif