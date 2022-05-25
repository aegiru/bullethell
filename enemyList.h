//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_ENEMYLIST_H
#define BULLET_HELL_ENEMYLIST_H


#include "enemyData.h"
#include "definitions.h"

class enemyList {
public:
    enemyData enemy = enemyData();
    enemyList* next = UNDEFINED_LIST_POINTER;
    void init();
    void removeAfter();

    enemyList();
};


#endif //BULLET_HELL_ENEMYLIST_H
