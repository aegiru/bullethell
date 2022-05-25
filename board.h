//
// Created by Doppie on 1/12/2022.
//

#ifndef BULLET_HELL_BOARD_H
#define BULLET_HELL_BOARD_H


class board {
public:
    int minX = 0, minY = 0, sizeY = 0, sizeX = 0;
    int traversableMinX = 0, traversableMinY = 0, traversableMaxX = 0, traversableMaxY = 0;
    int cameraMinX = 0, cameraMinY = 0, cameraMaxX = 0, cameraMaxY = 0;

    board();

};


#endif //BULLET_HELL_BOARD_H
