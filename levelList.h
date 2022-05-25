//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_LEVELLIST_H
#define BULLET_HELL_LEVELLIST_H


#include "levelData.h"
#include "definitions.h"

class levelList {
public:
    levelData levelInfo = levelData();
    levelList* next = UNDEFINED_LIST_POINTER;
    void init();
    levelList* findById(int id);

    levelList();
};


#endif //BULLET_HELL_LEVELLIST_H
