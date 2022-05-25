#define _USE_MATH_DEFINES
#define SDL_MAIN_HANDLED

#include<SDL.h>

#include "gameData.h"

int main(int argc, char *args[]) {
	gameData data = gameData();

    levelData exampleLevel = levelData();
    exampleLevel.levelID = 0;
    int sizeUnit = 180;
    exampleLevel.gameArea.minX = 0;
    exampleLevel.gameArea.minY = 0;
    exampleLevel.gameArea.sizeX = sizeUnit * 16;
    exampleLevel.gameArea.sizeY = sizeUnit * 16;
    exampleLevel.gameArea.traversableMinX = 0 + 5;
    exampleLevel.gameArea.traversableMinY = 0 + 5;
    exampleLevel.gameArea.traversableMaxX = exampleLevel.gameArea.sizeX - 3;
    exampleLevel.gameArea.traversableMaxY = exampleLevel.gameArea.sizeY - 3;
    exampleLevel.gameArea.cameraMinY = sizeUnit * 1;
    exampleLevel.gameArea.cameraMinX = sizeUnit * 1;
    exampleLevel.gameArea.cameraMaxY = exampleLevel.gameArea.sizeY - (sizeUnit * 1);
    exampleLevel.gameArea.cameraMaxX = exampleLevel.gameArea.sizeX - (sizeUnit * 1);

    enemyData exampleEnemy = enemyData();
    exampleEnemy.position.x = exampleLevel.gameArea.sizeX / 2 - 100;
    exampleEnemy.position.y = exampleLevel.gameArea.sizeY / 2 - 100;
    exampleEnemy.size.x = 20;
    exampleEnemy.size.y = 20;
    exampleEnemy.boss = true;
    exampleEnemy.maxHP = 100;
    exampleEnemy.currentHP = 80;

    shootingPattern newPattern = shootingPattern(8);
    newPattern.directions[0].y = 1;
    newPattern.directions[0].x = 0;
    newPattern.directions[1].y = 0;
    newPattern.directions[1].x = 1;
    newPattern.directions[2].y = -1;
    newPattern.directions[2].x = 0;
    newPattern.directions[3].y = 0;
    newPattern.directions[3].x = -1;
    newPattern.directions[4].y = 1;
    newPattern.directions[4].x = 1;
    newPattern.directions[5].y = -1;
    newPattern.directions[5].x = 1;
    newPattern.directions[6].y = -1;
    newPattern.directions[6].x = -1;
    newPattern.directions[7].y = 1;
    newPattern.directions[7].x = -1;

    shootingPatternList newPatternList = shootingPatternList();
    newPatternList.pattern = newPattern;
    newPatternList.pattern.shootingFrequency = 5.0;
    newPatternList.pattern.shootingTimer = 5.0;
    newPatternList.pattern.bulletSize.x = 6;
    newPatternList.pattern.bulletSize.y = 6;

    exampleEnemy.shootingPatterns.next = &newPatternList;

    enemyList newlist = enemyList();
    newlist.init();
    newlist.enemy = exampleEnemy;

    exampleLevel.enemies.next = &newlist;

    levelList newLVLList = levelList();
    newLVLList.init();
    newLVLList.levelInfo = exampleLevel;

    data.levels.next = &newLVLList;

	data.gameHandler();

	return 0;
};
