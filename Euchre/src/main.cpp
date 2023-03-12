#include <iostream>
#include "../include/euchre.h"

int main(){
    Euchre *my_game = new Euchre();

    my_game->GameLoop();
}