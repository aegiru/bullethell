//
// Created by Doppie on 1/10/2022.
//

#include "levelList.h"

levelList::levelList() = default;

void levelList::init() {
}


levelList* levelList::findById(int id) {
    levelList* tempNext = this->next;

    while (tempNext != UNDEFINED_LIST_POINTER) {
        if (tempNext->levelInfo.levelID == id) {
            return tempNext;
        }
        else {
            tempNext = tempNext->next;
        }
    }

    return UNDEFINED_LIST_POINTER;
}