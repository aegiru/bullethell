//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_PROJECTILEDATA_H
#define BULLET_HELL_PROJECTILEDATA_H

#include "coordinate.h"

class projectileData {
public:
    coordinate position, size, direction;
    bool playerMade;

    projectileData(int xPosition, int yPosition, int xSize, int ySize, int xDirection, int yDirection, bool playerMade);
    projectileData();
};


#endif //BULLET_HELL_PROJECTILEDATA_H
