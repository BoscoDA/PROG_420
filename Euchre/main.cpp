#include <iostream>
#include "Include/euchre.h"

int main(){
    Euchre *my_game = new Euchre();

    my_game->GameLoop();
}