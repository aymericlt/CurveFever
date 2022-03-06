/**
@brief Module gérant les couleurs des joueurs

Le module Couleur permet de gérer les couleurs des serpents et de leur trace.

@file Couleur.h
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Mars 2021
*/
#ifndef COULEUR_H
#define COULEUR_H

//! @brief Classe définissant une couleur rgb
class Couleur
{
private :
    /**
    @brief Quantité de rouge dans la couleur entre 0 et 255.
    */
    unsigned char r;
    
    /**
    @brief Quantité de vert dans la couleur entre 0 et 255.
    */
    unsigned char g;
    
    /**
    @brief Quantité de bleu dans la couleur entre 0 et 255.
    */
    unsigned char b;
    
public :
    /**
    @brief Constructeur par défaut de la classe : initialise le couleur en noir.
    */
    Couleur();

    /**
    @brief Constructeur de la classe: initialise le pixel avec les couleurs R G B fournies.
    @warning nr, ng et nb doivent être compris entre 0 et 255 inclus
    @param[in] nr Valeur de la composante rouge de la couleur
    @param[in] ng Valeur de la composante verte de la couleur
    @param[in] nb Valeur de la composante bleue de la couleur
    */
    Couleur(unsigned char nr, unsigned char ng, unsigned char nb);
    
    /**
    @brief Destructeur de la classe.
    */
    ~Couleur();

    /**
    @brief Accesseur : récupère la composante rouge de la couleur.
    @return unsigned char
    */
    unsigned char getRouge() const;

    /**
    @brief Accesseur : récupère la composante verte de la couleur.
    @return unsigned char
    */
    unsigned char getVert() const;

    /**
    @brief Accesseur : récupère la composante bleue de la couleur.
    @return unsigned char
    */
    unsigned char getBleu() const;
    
    /**
    @brief Mutateur : modifie la couleur.
    @warning nr, ng et nb doivent être compris entre 0 et 255 inclus
    @param[in] nr Valeur de la composante rouge de la couleur
    @param[in] ng Valeur de la composante verte de la couleur
    @param[in] nb Valeur de la composante bleue de la couleur
    */
    void setCouleur(unsigned char nr, unsigned char ng, unsigned char nb);

};

#endif /* Couleur_h */
