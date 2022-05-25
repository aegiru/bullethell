//
// Created by Doppie on 1/10/2022.
//

#include "projectileData.h"

projectileData::projectileData(int xPosition, int yPosition, int xSize, int ySize, int xDirection, int yDirection, bool playerMade) {
    this->position.x = xPosition;
    this->position.y = yPosition;

    this->size.x = xSize;
    this->size.y = ySize;

    this->direction.x = xDirection;
    this->direction.y = yDirection;

    this->playerMade = playerMade;
}

projectileData::projectileData() = default;