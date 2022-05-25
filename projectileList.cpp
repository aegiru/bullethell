//
// Created by Doppie on 1/10/2022.
//

#include "projectileList.h"
#include "definitions.h"
#include <malloc.h>

projectileList::projectileList() {

}

void projectileList::init() {
}

void projectileList::addProjectile(projectileData projectile) {

    this->size++;
    projectileData *tempList = (projectileData*) malloc (sizeof(projectileData) * this->size);
    for (int i = 0; i < this->size - 1; i++) {
        tempList[i] = this->projectile[i];
    }

    tempList[this->size - 1] = projectile;

    if (this->projectile != UNDEFINED_LIST_POINTER) {
        delete this->projectile;
    }

    this->projectile = tempList;
}

void projectileList::removeProjectile(int id) {
    this->size--;

    projectileData *tempList = (projectileData*) malloc (sizeof(projectileData) * this->size);
    int j = 0;
    for (int i = 0; i < this->size + 1; i++) {
        if (i == id) {
            continue;
        }
        tempList[j] = this->projectile[i];
        j++;
    }

    if (this->projectile != UNDEFINED_LIST_POINTER) {
        delete this->projectile;
    }

    this->projectile = tempList;
}