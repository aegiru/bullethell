//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_ENEMYDATA_H
#define BULLET_HELL_ENEMYDATA_H

#include "coordinate.h"
#include "definitions.h"
#include "shootingPatternList.h"

class enemyData {
public:
    coordinate position = coordinate();
    coordinate size = coordinate();
    bool boss = false;
    int maxHP = 100;
    int currentHP = maxHP;
    int minHP = 0;
    shootingPatternList shootingPatterns;


    enemyData();
};


#endif //BULLET_HELL_ENEMYDATA_H
