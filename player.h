//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_PLAYER_H
#define BULLET_HELL_PLAYER_H

#include "coordinate.h"

class player {
public:
    coordinate position;
    int health;
    coordinate size;

    player();
};


#endif //BULLET_HELL_PLAYER_H
