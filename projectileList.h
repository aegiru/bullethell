//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_PROJECTILELIST_H
#define BULLET_HELL_PROJECTILELIST_H


#include "projectileData.h"
#include "definitions.h"

class projectileList {
public:
    projectileData *projectile = UNDEFINED_LIST_POINTER;
    int size = 0;

    void init();
    void addProjectile(projectileData projectile);
    void removeProjectile(int id);

    projectileList();
};


#endif //BULLET_HELL_PROJECTILELIST_H
