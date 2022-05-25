//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_GAMEDATA_H
#define BULLET_HELL_GAMEDATA_H

#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>
#include "levelList.h"
#include "projectileList.h"
#include "enemyList.h"
#include "player.h"
#include "definitions.h"
#include "projectileData.h"


class gameData {
public:
    int t1 = 0, t2 = 0, quit = 0, frames = 0, rc = 0, levelID = 0, score = 0, bossHP = 0, bossMaxHP = 0, bossDefeatHP = 0;
    double delta = 0, worldTime = 0, fpsTimer = 0, fps = 0, distance = 0, horizontalSpeed = 0, verticalSpeed = 0;

    coordinate display;

    int currentLevel = DEFAULT_LEVEL_ID;

    coordinate cameraPosition;

    char text[TEXT_LENGTH];
    bool bossExists = false;
    bool loadNextLevel = true;

    SDL_Event event;
    SDL_Surface* screen, *charset;
    SDL_Texture* scrtex;
    SDL_Window* window;
    SDL_Renderer* renderer;

    int black;
    int white;
    int green;
    int red;
    int blue;
    int cyan;

    levelList levels;
    projectileList projectiles;
    enemyList enemies;

    board gameArea;

    player player;

    gameData();

    void renderText(int x, int y);

    void renderObject(coordinate position, coordinate size, int innerColor, int outerColor);
    void iterateShootingPattern(shootingPattern &pattern, int xPosition, int yPosition, bool playerMade);
    void updateSingleEnemy(enemyData enemy);
    void updateProjectiles();
    void nextLevel();
    void renderEnemies();
    void renderProjectiles();
    void renderTopMenu();
    void renderPlayArea();
    void renderAdditionalInfo();
    void renderFrame();
    void updateEnemies();
    void updatePlayer();
    void updateTick();
    void gameHandler();
    void reset();
};


#endif //BULLET_HELL_GAMEDATA_H
