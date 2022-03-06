/**
@brief Module gérant la partie SDL

@detail Coeur de la version graphique du jeu, ce module contient les images utilisées, 
les couleurs, les polices d'écriture ou encore la fenêtre du jeu.

sdlJeu fonctionne autour d'une boucle qui récupère les actions des joueurs 
et appelle les fonctions de calculs et d'affichage.

A chaque itération, la boucle affichera tout le jeu, fera avancer les serpents, 
tracera un peu plus leur courbe si un trou ne se forme pas, 
ajustera leur orientation en fonction des touches appuyées 
et vérifira les colisions pour determiner si un joueur à perdu.

@file sdlJeu.h
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Mars 2021
*/

#ifndef SDLJEU_H
#define SDLJEU_H
#include "Jeu.h"
#include "Image.h"
#include "fenetreJeu.h"
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

//! \brief Module gérant la boucle du jeu
class sdlJeu
{
public:
    /**
    @brief Constructeur de la classe, démarre une partie avec une taille de terrain de largeur tailleX et hauteur tailleY
    De plus on passe en paramètre les couleurs des deux serpents
    */
    sdlJeu(unsigned int tailleX, unsigned int tailleY, Couleur couleur1, Couleur couleur2);

    /**
    @brief Destructeur de la classe, il libère le renderer, la fenêtre, et ferme SDL
    */
    ~sdlJeu();

    /**
    @brief Boucle principale du jeu, elle est appelée une unique fois dans le programme principal.
    */
    void sdlBoucle();

private:
    /**
    @brief Booleen étant initialisé à true, quand il devient false le programme se termine en sortant de la boucle de jeu
    */
    bool gameRunning;

    /**
    @brief Jeu qui contient les infos de la partie, tel que les serpents ou le terrain
    */
    Jeu jeu;

    /**
    @brief Module fenêtre du jeu qui contient les fonctions d'affichage des surfaces ou encore des tracés des serpents
    */
    FenetreJeu fenetreJeu;

    /**
    @brief Image correspondant à la barre horizontale au dessus du jeu, avec le titre CURVEFEVER
    */
    Image imageTitreJeu;

    /**
    @brief Image correspondant à la barre latérale à droite du jeu
    */
    Image imageDroiteJeu;

    /**
    @brief Image correspondant au bouton Quitter, sous forme Presse
    */
    Image imQuitterPresse;

    /**
    @brief Image correspondant au bouton Quitter, sous forme non Presse
    */
    Image imQuitter;

    /**
    @brief Image correspondant au bouton Recommencer, sous forme Presse
    */
    Image imRecommencerPresse;

    /**
    @brief Image correspondant au bouton Recommencer, sous forme non Presse
    */
    Image imRecommencer;

    /**
    @brief Tableau d'images de serpent, il contient les 6 têtes colorées qui seront selectionnées en fonctions des images des serpents
    */
    Image imTeteSerpent[6];

    /**
    @brief Police d'écriture de taille 24
    */
    TTF_Font * font24;

    /**
    @brief Police d'écriture de taille 32
    */
    TTF_Font * font32;

    /**
    @brief Police d'écriture de taille 48
    */
    TTF_Font * font48;

    /**
    @brief Police d'écriture de taille 64
    */
    TTF_Font * font64;

    /**
    @brief Couleur pour les écritures : Blanc
    */
    SDL_Color blanc;

    /**
    @brief Couleur pour les écritures : Gris clair
    */
    SDL_Color grisEcriture;

    /**
    @brief Fenêtre du jeu
    */
    SDL_Window * window;

    /**
    @brief Renderer du jeu
    */
    SDL_Renderer * renderer;

    /**
    @brief Fonction principale d'affichage, elle appelle l'affichage des courbes, affiche les boutons, 
    écrit les scores, les textes et appelle l'affichage des têtes des serpents
    @param[in] boutonRecommencer Booleen indiquant si la souris survole le bouton Recommencer
    @param[in] boutonQuitter Booleen indiquant si la souris survole le bouton Quitter
    */
    void sdlAff(bool boutonRecommencer, bool boutonQuitter);

    /**
    @brief Vérifie si la souris est dans un certain rectangle spécifiée par les arguments
    @return Booleen valant vrai si la souris est dans la zone, faux sinon
    @param[in] x Coordonnée x du coin gauche de la zone
    @param[in] y Coordonnée y du coin gauche de la zone
    @param[in] w Largeur de la zone
    @param[in] h Hauteur de la zone
    @param[in] souris_x Coordonnée x de la souris
    @param[in] souris_y Coordonnée y de la souris
    */
    bool isIn(int x, int y, int w, int h, int souris_x, int souris_y);

    /**
    @brief Fonction d'affichage de la tête des serpent, en affiche la tête de chaque serpent avec la bonne couleur, et la bonne orientation
    @param[in] renderer Renderer de la partie
    @param[in] S Serpent dont on doit afficher la tête
    */
    void afficherTeteSerpent(SDL_Renderer* renderer, Serpent S);

    /**
    @brief Fonction d'affichage d'un texte centré au milieu de la fenêtre, on peut le decaler si on le souhaite, ou bien le centrer 
    parfaitement en entrant 0 pour p_x et p_y
    @param[in] p_x Décalage horizontal du texte (+ -> texte décalé à droite)
    @param[in] p_y Décalage vertical du texte (+ -> texte décalé en bas)
    @param[in] p_text Chaine de caractère que l'on veut écrire
    @param[in] font Police d'écriture désirée
    @param[in] textColor Couleur désirée
    */
    void renderCenterText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);

    /**
    @brief Fonction d'affichage d'un texte où l'on souhaite dans la fenêtre fenêtre
    @param[in] p_x Coordonnée x du texte
    @param[in] p_y Coordonnée y du texte
    @param[in] p_text Chaine de caractère que l'on veut écrire
    @param[in] font Police d'écriture désirée
    @param[in] textColor Couleur désirée
    */
    void renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);

    /**
    @brief Avancée automatique des serpents, et traçage de leur courbe au fur et à mesure.
    */
    void sdlActionsAutomatiques();

    /**
    @brief Réinitialise les données membres de la classe pour redémarrer une partie, en passant par Jeu, Terrain, Serpents, etc
    */
    void recommencerPartie();
};


#endif