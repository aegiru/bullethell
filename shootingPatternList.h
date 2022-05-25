//
// Created by Doppie on 1/13/2022.
//

#ifndef BULLET_HELL_SHOOTINGPATTERNLIST_H
#define BULLET_HELL_SHOOTINGPATTERNLIST_H

#include "shootingPattern.h"
#include "definitions.h"

class shootingPatternList {
public:
    shootingPattern pattern;
    shootingPatternList* next = UNDEFINED_LIST_POINTER;

    shootingPatternList();
};


#endif //BULLET_HELL_SHOOTINGPATTERNLIST_H
