//
// Created by Doppie on 1/10/2022.
//

#include "enemyList.h"
#include "definitions.h"

enemyList::enemyList() = default;

void enemyList::init() {

}

void enemyList::removeAfter() {
    enemyList* tempNext = this->next;
    this->next = this->next->next;
    delete tempNext;
}