#include "sdlJeu.h"
#include "menu.h"

int main(int argc, char* argv[])
{
    Menu menu;
    menu.boucleRemplissage();
    Couleur c1 = menu.couleurJ1;
    Couleur c2 = menu.couleurJ2;
    menu.~Menu();
    sdlJeu sjeu(187,105, c1, c2);
    
    sjeu.sdlBoucle();
    return 0;
}