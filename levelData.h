//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_LEVELDATA_H
#define BULLET_HELL_LEVELDATA_H

#include "board.h"
#include "enemyList.h"


class levelData {
public:
    int levelID;
    board gameArea = board();
    enemyList enemies = enemyList();

    levelData();
};


#endif //BULLET_HELL_LEVELDATA_H
