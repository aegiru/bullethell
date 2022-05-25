//
// Created by Doppie on 1/10/2022.
//

#include "player.h"
#include "definitions.h"

player::player() {
    this->position.x = PLAYER_STARTING_POSITION_X;
    this->position.y = PLAYER_STARTING_POSITION_Y;

    this->health = MAX_HEALTH;
}
