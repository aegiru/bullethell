//
// Created by Doppie on 1/13/2022.
//

#ifndef BULLET_HELL_SHOOTINGPATTERN_H
#define BULLET_HELL_SHOOTINGPATTERN_H

#include "coordinate.h"

class shootingPattern {
public:
    double shootingFrequency = 0, shootingTimer = 0;
    int id = 0;
    int size;
    coordinate* directions;
    coordinate bulletSize;

    shootingPattern(int numberOfProjectiles);
    shootingPattern();
};


#endif //BULLET_HELL_SHOOTINGPATTERN_H
