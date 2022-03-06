/**
@brief Implémentation de la classe terrain


@file Terrain.cpp
@author : Aymeric Leto, Benoît Briguet, Nathan Puricelli
@date : Mars 2021
*/

#include "Terrain.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
using namespace std;

Terrain::Terrain()
{
    tailleX = 0;
    tailleY = 0;
}

Terrain::Terrain(unsigned int tX, unsigned int tY)
{
    assert(tX>=0);
    assert(tY>=0);
    tailleX = tX;
    tailleY = tY;

    tabCasesOccupees = new unsigned char* [tX];

    for (unsigned int i = 0; i < tX; i++)
    {
        tabCasesOccupees[i] = new unsigned char [tY];
        for (unsigned int j = 0; j < tY; j++)
        {            
            tabCasesOccupees[i][j] = 0;
        }
    }
}


Terrain::~Terrain() {}

unsigned int Terrain::getTailleX()const
{
    return tailleX;
}

unsigned int Terrain::getTailleY()const
{
    return tailleY;
}
