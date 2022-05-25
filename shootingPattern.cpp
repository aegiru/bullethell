//
// Created by Doppie on 1/13/2022.
//

#include <malloc.h>
#include "shootingPattern.h"

shootingPattern::shootingPattern(int numberOfProjectiles) {
    this->directions = (coordinate*) malloc(sizeof(coordinate) * numberOfProjectiles);
    this->size = numberOfProjectiles;
    this->bulletSize.x = 0;
    this->bulletSize.y = 0;
}

shootingPattern::shootingPattern() = default;
