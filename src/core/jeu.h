/**
@brief Module gérant les informations du jeu

Le module Jeu permet de gérer les données du jeu comme le terrain et les deux serpents.

@file Jeu.h
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Mars 2021
*/

#ifndef JEU_H
#define JEU_H

#include "Serpent.h"
#include "Terrain.h"

//! @brief Classe avec les fonctions de coeur du jeu
class Jeu
{
private :
    /**
    @brief Permier serpent de la partie (celui du joueur 1).
    */
    Serpent s1;
    
    /**
    @brief Second serpent de la partie (celui du joueur 2).
    */
    Serpent s2;

    
public :
    /**
    @brief Terrain de jeu de la partie.
    */
    Terrain t;
    
    /**
    @brief Constructeur de la classe, lance une partie avec 2 serpents et 1 terrain de jeu.
    */
    Jeu();

    /**
    @brief Constructeur de la classe, lance une partie avec 2 serpents et 1 terrain de jeu.
    */
    Jeu(unsigned int tailleX, unsigned int tailleY, Couleur couleur1, Couleur couleur2);
    
    /**
    @brief Destructeur de la classe.
    */
    ~Jeu();

    /**
    @brief Accesseur : Récupère l'adresse du premier serpent.
    @return Serpent&
    */
    Serpent& getS1();

    /**
    @brief Accesseur : Récupère l'adresse du deuxième serpent.
    @return Serpent&
    */
    Serpent& getS2();

    /**
    @brief Accesseur : Récupère l'adresse du premier serpent en const.
    @return const Serpent&
    */
    const Serpent& getConstS1() const;

    /**
    @brief Accesseur : Récupère l'adresse du premier serpent en const.
    @return const Serpent&
    */
    const Serpent& getConstS2() const;

    /**
    @brief Actions qui se déroulent à chaque boucle TXT
    */
    void actionsAutomatiquesTXT();

    /**
    @brief Actions qui se déroulent à chaque boucle SDL
    */
    void actionsAutomatiquesSDL();

    /**
    @brief Réactions du jeu au touches pressées
    @param[in] touche Touche appuyée par l'utilisateur
    */
    void actionClavierTXT(const char touche);

    /**
    @brief Réactions du jeu au touches pressées
    @param[in] J1GaucheAppuyee Booleen indiquant si le joueur 1 a pressé sur sa touche gauche
    @param[in] J1DroiteAppuyee Booleen indiquant si le joueur 1 a pressé sur sa touche droite
    @param[in] J2GaucheAppuyee Booleen indiquant si le joueur 2 a pressé sur sa touche gauche
    @param[in] J2DroiteAppuyee Booleen indiquant si le joueur 2 a pressé sur sa touche droite
    */
    void actionClavierSDL(bool J1GaucheAppuye, bool J1DroiteAppuye, bool J2GaucheAppuye, bool J2DroiteAppuye);
};

#endif
