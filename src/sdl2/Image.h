/**
@brief Module gérant des images

Le module Image gère la manipulation d'images dans sdl

@file Image.h
@author : professeurs LIFAP4, source pacman 
@date : Avril 2021
*/


#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cassert>
#include <string>

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

using namespace std;


//! @brief Classe gérant l'affichage et la gestion des images
class Image {

private:

    /**
    @brief Surface sdl du plateau de jeu
    */
    SDL_Surface * surface;

    /**
    @brief Texture sdl du plateau de jeu
    */
    SDL_Texture * texture;

    /**
    @brief booléen pour savoir s'il faut actualiser la texture
    */
    bool has_changed;

public:
    /**
    @brief Constrtucteur par défaut de la classe
    */
    Image () ;

    /**
    @brief Permet de charger l'image depuis un fichier
    @param[in] filename Chaine de caractères du chemin relatif de la photo
    @param[in] renderer enderer sdl gerant l'affichage de la texture du plateau
    */
    void loadFromFile (const char* filename, SDL_Renderer * renderer);

    /**
    @brief Permet d'actualiser la texture de l'image
    @param[in] renderer enderer sdl gerant l'affichage de la texture du plateau
    */
    void loadFromCurrentSurface (SDL_Renderer * renderer);

    /**
    @brief Fonction permettant d'afficher l'image du plateau à l'écran
    @param renderer Renderer sdl gerant l'affichage de la texture du plateau
    @param[in] x Coordonnée en x de l'endroit ou afficher le coin superieur gauche de l'image
    @param[in] y Coordonnée en y de l'endroit ou afficher le coin superieur gauche de l'image
    @param[in] w Largeur de l'image à afficher
    @param[in] h Hauteur de l'image à afficher
    */
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);

    /**
    @brief Permet de recuperer la texture de l'image
    @return SDL_Texture*
    */
    SDL_Texture * getTexture() const;

    /**
    @brief Permet de modifier directement la surface de l'image
    */
    void setSurface(SDL_Surface * surf);
};
#endif