/**
@brief Implémentation de la classe serpent

@file Serpent.cpp
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Mars 2021
*/

#include "Serpent.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <math.h>

const float PI = 3.1415926535;

using namespace std;

Serpent::Serpent() {
    TeteX = 0;
    TeteY = 0;
    vivant = true;
    score = 0;
    direction = 0;
    couleur = Couleur(0,0,0);
    CompteurTrous = 0;
}

Serpent::Serpent(float x,float y, Couleur c)
{   
    srand((unsigned int)time(0));


    TeteX = x;
    TeteY = y;

    vivant = true;
    score = 0;
    
    direction = (rand()%4) * 90; // pas valide en sdl
    
    couleur = c;
    CompteurTrous = rand()%30;
    ID = 0;
    x_precedent = 0;
    y_precedent = 0;

}


Serpent::~Serpent()
{
    vivant = true;
    score = 0;
    couleur.~Couleur();
}


float Serpent::getTeteX()const
{
    return TeteX;
}


float Serpent::getTeteY()const
{
    return TeteY;
}


bool Serpent::getVivant()const
{
    return vivant;
}


unsigned int Serpent::getScore()const
{
    return score;
}

float Serpent::getDirection() const
{
    return direction;
}

Couleur Serpent::getCouleur()const
{
    return couleur;
}

void Serpent::setDirection(float dir)
{
    direction = dir;
}

void Serpent::setVivant(bool vie)
{
    vivant = vie;
}

void Serpent::setTeteX(float x)
{
    TeteX = x;
}


void Serpent::setTeteY(float y)
{
    TeteY = y;
}


void Serpent::avancerTXT(Terrain &t)
{
    if ((CompteurTrous%30) >= 6) t.tabCasesOccupees[(int)TeteX][(int)TeteY] = ID;    
    if (direction == 0)
    {
        TeteY++;
    }
    else if (direction == 90)
    {
        TeteX++;
    }
    else if (direction == 180)
    {
        TeteY--;
    }
    else TeteX--;    
    CompteurTrous++;
}


void Serpent::avancerSDL(Terrain &t)
{
    y_precedent = (unsigned int)TeteY;
    x_precedent = (unsigned int)TeteX;
    if ((CompteurTrous%30) >= 6) t.tabCasesOccupees[x_precedent][y_precedent] = ID;       

    float avanceeX = 1.42 * cos(direction * PI / 180);
    float avanceeY = 1.42 * sin(direction * PI / 180);

    if (avanceeX > 1) avanceeX = 1;
    if (avanceeX < -1) avanceeX = -1;

    if (avanceeY > 1) avanceeY = 1;
    if (avanceeY < -1) avanceeY = -1;
    TeteX += avanceeX;
    TeteY += avanceeY;


    CompteurTrous++;
}


void Serpent::augmenterScore(int s)
{
    score += s;
}

bool Serpent::VerifColision(const Terrain &t) const
{
    //Vérifie les cases à gauche et à droite de la tête du serpent, ce qui dépent donc de sa direction.
    //On vérifie les déplacements dans cet ordre : droite haut gauche bas
    int largeurMur = 2;

    if ((direction > 315 || direction <= 45) || (direction > 135 && direction <= 225)) //droite ou gauche
        return ((TeteX<=largeurMur) || (TeteX>=t.getTailleX()-largeurMur) || (TeteY<=largeurMur) || (TeteY>=t.getTailleY()-largeurMur) 
            || (t.tabCasesOccupees[(int) TeteX][(int) TeteY])
            || (t.tabCasesOccupees[(int) TeteX][(int) TeteY + 1]) || (t.tabCasesOccupees[(int) TeteX][(int) TeteY - 1]));

    if ((direction > 45 && direction <= 135) || (direction > 225 && direction <= 315)) //haut ou bas
        return ((TeteX<=largeurMur) || (TeteX>=t.getTailleX()-largeurMur) || (TeteY<=largeurMur) || (TeteY>=t.getTailleY()-largeurMur) 
            || (t.tabCasesOccupees[(int) TeteX][(int) TeteY])
            || (t.tabCasesOccupees[(int) TeteX + 1][(int) TeteY]) || (t.tabCasesOccupees[(int) TeteX - 1][(int) TeteY]));

    return ((TeteX<=largeurMur) || (TeteX>=t.getTailleX()-largeurMur) || (TeteY<=largeurMur) || (TeteY>=t.getTailleY()-largeurMur) 
            || (t.tabCasesOccupees[(int) TeteX][(int) TeteY]));
}
