/**
@brief Module gérant le terrain de jeu et la trace

Le module Terrain permet de gérer un tableau de booléens et ainsi la trace des serpents.

@file Terrain.h
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Mars 2021
*/
#ifndef TERRAIN_H
#define TERRAIN_H

//! @brief Classe définissant le terrain de jeu
class Terrain
{
private :
    /**
    @brief Les dimensions du terrain de jeu.
    */
    unsigned int tailleX, tailleY;
    
    
public :
    /**
    @brief Tableau 2D de unsigned char indiquant si la case est occupée par la trace d'un joueur (0 = vide, 1 = J1, 2 = J2).
    */
    unsigned char** tabCasesOccupees;    
    /**
    @brief Constructeur par défaut du terrain. Initialise tailleX et tailleY à 0.
    */
    Terrain();
    
    /**
    @brief Constructeur de la classe : initialise tailleX et tailleY (après vérification) puis alloue le tableau de booléen dans le tas.
    @warning tX et tY doivent être supérieurs ou égaux à 0
    @param[in] tX Hauteur du terrain de jeu
    @param[in] tY Largeur du terrain de jeu
    */
    Terrain(unsigned int tX, unsigned int tY);
    
    /**
    @brief Destructeur de la classe : déallocation de la mémoire du tableau de et mise à jour des champs tailleX et tailleY à 0.
    */
    ~Terrain();
    
    /**
    @brief Accesseur : récupère la hauteur du terrain.
    */
    unsigned int getTailleX()const ;
    
    /**
    @brief Accesseur : récupère la largeur du terrain
    */
    unsigned int getTailleY()const ;

    
};




#endif
