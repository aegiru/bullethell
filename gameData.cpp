//
// Created by Doppie on 1/10/2022.
//

#include "gameData.h"
#include "definitions.h"
#include "prerequisites.h"
#include <malloc.h>


gameData::gameData() {
    this->levels.init();
    this->projectiles.init();
    this->enemies.init();

    this->gameArea = board();

    this->display.x = PLAY_AREA_X;
    this->display.y = PLAY_AREA_Y;

    this->player.size.x = PLAYER_SIZE;
    this->player.size.y = PLAYER_SIZE;

    int rc;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
    }

    rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    if (rc != 0) {
        SDL_Quit();
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
    };

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_SetWindowTitle(window, "Bullet Hell");

    screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_ShowCursor(SDL_DISABLE);


    charset = SDL_LoadBMP("./cs8x8.bmp");
    if (charset == NULL) {
        softwareCrash(this->charset, this->screen, this->scrtex, this->window, this->renderer);
    };

    SDL_SetColorKey(charset, true, 0x000000);

    this->black = SDL_MapRGB(this->screen->format, 0x00, 0x00, 0x00);
    this->white = SDL_MapRGB(this->screen->format, 0xFF, 0xFF, 0xFF);
    this->green = SDL_MapRGB(this->screen->format, 0x00, 0xFF, 0x00);
    this->red = SDL_MapRGB(this->screen->format, 0xFF, 0x00, 0x00);
    this->blue = SDL_MapRGB(this->screen->format, 0x11, 0x11, 0xCC);
    this->cyan = SDL_MapRGB(this->screen->format, 0x00, 0xFF, 0xFF);
}

void gameData::nextLevel() {
    this->currentLevel+=1;

    this->projectiles = projectileList();
    this->enemies = enemyList();

    this->gameArea = this->levels.findById(currentLevel)->levelInfo.gameArea;

    this->enemies = this->levels.findById(currentLevel)->levelInfo.enemies;

    this->cameraPosition.x = this->gameArea.sizeX / 2;
    this->cameraPosition.y = this->gameArea.sizeY / 2;

    this->player.position.x = this->cameraPosition.x;
    this->player.position.y = this->cameraPosition.y;

    this->loadNextLevel = false;
}

void gameData::renderObject(coordinate position, coordinate size, int innerColor, int outerColor) {
    double xDelta = position.x - this->cameraPosition.x;
    int xPosition = (abs((int)(xDelta)) * negativeFlatConversion(xDelta)) + (PLAY_AREA_OFFSET_X + (this->display.x / 2)) - size.x / 2;
    double yDelta = position.y - this->cameraPosition.y;
    int yPosition = (abs((int)(yDelta)) * negativeFlatConversion(yDelta)) + (PLAY_AREA_OFFSET_Y + (this->display.y / 2)) - size.y / 2;

    int displayMaxX = DISPLAY_AREA_X + this->display.x;
    int xDisplayPosition = minimum(maximum(DISPLAY_AREA_X, xPosition), displayMaxX);
    int xNegativePosition = DISPLAY_AREA_X - xPosition;
    int xPositivePosition = displayMaxX - xPosition - size.x;
    int xOutOfBounds = (xNegativePosition) * isAboveZero(xNegativePosition) + abs(xPositivePosition) * isBelowZero(xPositivePosition);
    int xDisplaySize = size.x - xOutOfBounds;

    int displayMaxY = DISPLAY_AREA_Y + this->display.y;
    int yDisplayPosition = minimum(maximum(DISPLAY_AREA_Y, yPosition), displayMaxY);
    int yNegativePosition = DISPLAY_AREA_Y - yPosition;
    int yPositivePosition = displayMaxY - yPosition - size.y;
    int yOutOfBounds = (yNegativePosition) * isAboveZero(yNegativePosition) + abs(yPositivePosition) * isBelowZero(yPositivePosition);
    int yDisplaySize = size.y - yOutOfBounds;

    if (xDisplaySize > 0 && yDisplaySize > 0) {
        LocalDrawRectangle(this->screen, xDisplayPosition, yDisplayPosition, xDisplaySize, yDisplaySize, innerColor, outerColor);
    }

}

void gameData::renderText(int x, int y) {
    LocalDrawString(this->screen, x, y, text, this->charset);
}

void gameData::renderProjectiles() {
    for (int i = 0; i < this->projectiles.size; i++) {
        this->renderObject(this->projectiles.projectile[i].position, this->projectiles.projectile[i].size, this->cyan, this->cyan);
    }
}

void gameData::renderEnemies() {
    enemyList tempNext = this->enemies;
    while (tempNext.next != UNDEFINED_LIST_POINTER) {
        this->renderObject(tempNext.next->enemy.position, tempNext.next->enemy.size, this->green, this->green);

        tempNext.next = tempNext.next->next;
    }
}

void gameData::renderTopMenu() {

    LocalDrawRectangle(this->screen, 4, 4, SCREEN_WIDTH - 8, 36, this->white, this->black);

    sprintf(this->text, "Bullet Hell, %.0lf fps", this->fps);
    this->renderText(this->screen->w / 2 - strlen(this->text) * 8 / 2, 10);

    sprintf(this->text, "%.2lf v, %.2lf h | %.1lf x / %.1lf y | %.1lf x / %.1lf y", this->verticalSpeed * delta, this->horizontalSpeed * delta, this->player.position.x, this->player.position.y, this->cameraPosition.x, this->cameraPosition.y);
    this->renderText(this->screen->w / 2 - strlen(this->text) * 8 / 2, 26);
}

void gameData::renderPlayArea() {
    LocalDrawRectangle(this->screen, PLAY_AREA_OFFSET_X, PLAY_AREA_OFFSET_Y, PLAY_AREA_X + DISPLAY_COMPENSATION, PLAY_AREA_Y + DISPLAY_COMPENSATION, this->white, this->black);

    this->renderProjectiles();

    this->renderEnemies();

    this->renderObject(this->player.position, this->player.size, this->red, this->red);
}

void gameData::iterateShootingPattern(shootingPattern &pattern, int xPosition, int yPosition, bool playerMade) {
    if (pattern.shootingTimer <= 0) {
        for (int i = 0; i < pattern.size; i++) {
            projectileData newProjectile = projectileData(xPosition, yPosition, (int)pattern.bulletSize.x, (int)pattern.bulletSize.y, (int)pattern.directions[i].x, (int)pattern.directions[i].y, playerMade);
            this->projectiles.addProjectile(newProjectile);
        }

        pattern.shootingTimer = pattern.shootingFrequency;

    } else {
        pattern.shootingTimer-= this->delta;
    }
}

void gameData::updateSingleEnemy(enemyData enemy) {
    shootingPatternList* tempShootingPatternList = &enemy.shootingPatterns;
    while (tempShootingPatternList->next != UNDEFINED_LIST_POINTER) {
        this->iterateShootingPattern(tempShootingPatternList->next->pattern, enemy.position.x, enemy.position.y, false);

        tempShootingPatternList = tempShootingPatternList->next;
    }

}

void gameData::renderAdditionalInfo() {
    int offsetX = PLAY_AREA_OFFSET_X + PLAY_AREA_X + ADDITIONAL_INFO_OFFSET;
    LocalDrawRectangle(this->screen, offsetX, PLAY_AREA_OFFSET_Y, ADDITIONAL_INFO_X, PLAY_AREA_Y, this->white, this->black);

    int currentOffsetY = ITEM_OFFSET;

    sprintf(this->text, "SCORE");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;
    sprintf(this->text, "%i", this->score);
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;

    currentOffsetY += SECTION_OFFSET;

    sprintf(this->text, "HEALTH");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;

    LocalDrawRectangle(this->screen, offsetX + HEALTHBAR_OFFSET, PLAY_AREA_OFFSET_Y + currentOffsetY, ADDITIONAL_INFO_X - (HEALTHBAR_OFFSET * 2), HEALTHBAR_SIZE, this->white, this->black);
    LocalDrawRectangle(this->screen, offsetX + HEALTHBAR_OFFSET + HEALTHBAR_SIZE_REDUCTION, PLAY_AREA_OFFSET_Y + currentOffsetY + HEALTHBAR_SIZE_REDUCTION, ADDITIONAL_INFO_X - ((HEALTHBAR_OFFSET + HEALTHBAR_SIZE_REDUCTION) * 2), HEALTHBAR_SIZE - (HEALTHBAR_SIZE_REDUCTION * 2), this->green, this->green);
    currentOffsetY += ITEM_OFFSET;

    currentOffsetY += SECTION_OFFSET;

    if (this->bossExists) {
        sprintf(this->text, "BOSS");
        this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
        currentOffsetY += ITEM_OFFSET;

        LocalDrawRectangle(this->screen, offsetX + HEALTHBAR_OFFSET, PLAY_AREA_OFFSET_Y + currentOffsetY, ADDITIONAL_INFO_X - (HEALTHBAR_OFFSET * 2), HEALTHBAR_SIZE, this->white, this->black);
        LocalDrawRectangle(this->screen, offsetX + HEALTHBAR_OFFSET + HEALTHBAR_SIZE_REDUCTION, PLAY_AREA_OFFSET_Y + currentOffsetY + HEALTHBAR_SIZE_REDUCTION, (int)((double)(ADDITIONAL_INFO_X - ((HEALTHBAR_OFFSET + HEALTHBAR_SIZE_REDUCTION) * 2)) * (double)((double)this->bossHP / this->bossMaxHP)), HEALTHBAR_SIZE - (HEALTHBAR_SIZE_REDUCTION * 2), this->red, this->red);
        currentOffsetY += ITEM_OFFSET;

        currentOffsetY += SECTION_OFFSET;
    }

    sprintf(this->text, "TIME");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2,PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;
    sprintf(this->text, "%.1lf s", this->worldTime);
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;

    currentOffsetY += SECTION_OFFSET;

    sprintf(this->text, "CONTROLS");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;
    sprintf(this->text, "Esc - Quit");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;
    sprintf(this->text, "\030 - Up");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;
    sprintf(this->text, "\031 - Down");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;
    sprintf(this->text, "\032 - Left");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;
    sprintf(this->text, "\033 - Right");
    this->renderText(offsetX + ADDITIONAL_INFO_X / 2 - strlen(this->text) * 8 / 2, PLAY_AREA_OFFSET_Y + currentOffsetY);
    currentOffsetY += ITEM_OFFSET;
}

void gameData::renderFrame() {

    SDL_FillRect(this->screen, NULL, this->black);

    this->renderTopMenu();

    this->renderPlayArea();

    this->renderAdditionalInfo();

    SDL_UpdateTexture(this->scrtex, NULL, this->screen->pixels, this->screen->pitch);
    SDL_RenderCopy(this->renderer, this->scrtex, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void gameData::updateEnemies() {
    enemyList* tempNext = &this->enemies;
    while (tempNext->next != UNDEFINED_LIST_POINTER) {
        if (tempNext->next->enemy.boss) {
            this->bossExists = true;
            this->bossHP = tempNext->next->enemy.currentHP;
            this->bossMaxHP = tempNext->next->enemy.maxHP;
        }

        this->updateSingleEnemy(tempNext->next->enemy);

        tempNext = tempNext->next;
    }

}

void gameData::updatePlayer() {
    double multiplier = this->delta * DEFAULT_SPEED_MULTIPLIER;
    double deltaX = (this->verticalSpeed * multiplier);
    double deltaY = (this->horizontalSpeed * multiplier);
    this->player.position.x = minimum(maximum(this->player.position.x + deltaX, this->gameArea.traversableMinX), this->gameArea.traversableMaxX);
    this->player.position.y = minimum(maximum(this->player.position.y + deltaY, this->gameArea.traversableMinY), this->gameArea.traversableMaxY);
    this->cameraPosition.x = minimum(maximum(this->player.position.x, this->gameArea.cameraMinX), this->gameArea.cameraMaxX);
    this->cameraPosition.y = minimum(maximum(this->player.position.y, this->gameArea.cameraMinY), this->gameArea.cameraMaxY);
}

void gameData::updateProjectiles() {
    for (int i = 0; i < this->projectiles.size; i++) {
        this->projectiles.projectile[i].position.x += this->projectiles.projectile[i].direction.x * this->delta * (DEFAULT_SPEED_MULTIPLIER / 2);
        this->projectiles.projectile[i].position.y += this->projectiles.projectile[i].direction.y * this->delta * (DEFAULT_SPEED_MULTIPLIER / 2);

        bool isTooLeft = this->projectiles.projectile[i].position.x + this->projectiles.projectile[i].size.x < 0;

        if (isTooLeft) {
            this->projectiles.removeProjectile(i);
        }
    }
}

void gameData::updateTick() {
    this->t2 = SDL_GetTicks();

    this->delta = (this->t2 - this->t1) * 0.001;
    this->t1 = this->t2;

    this->worldTime += this->delta;

    this->updatePlayer();

    this->updateEnemies();

    this->updateProjectiles();

    this->fpsTimer += this->delta;

    if (this->fpsTimer > 0.5) {
        this->fps = this->frames * 2;
        this->frames = 0;
        this->fpsTimer -= 0.5;
    };
}

void gameData::gameHandler() {
    this->t1 = SDL_GetTicks();

    while (!this->quit) {
        if (this->loadNextLevel) {
            this->nextLevel();
        }

        this->updateTick();

        this->renderFrame();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) this->quit = 1;
                    else if (event.key.keysym.sym == SDLK_UP)  this->horizontalSpeed = DEFAULT_HORIZONTAL_SPEED + UP_SPEED;
                    else if (event.key.keysym.sym == SDLK_DOWN) this->horizontalSpeed = DEFAULT_HORIZONTAL_SPEED + DOWN_SPEED;
                    else if (event.key.keysym.sym == SDLK_LEFT) this->verticalSpeed = DEFAULT_VERTICAL_SPEED + LEFT_SPEED;
                    else if (event.key.keysym.sym == SDLK_RIGHT) this->verticalSpeed = DEFAULT_VERTICAL_SPEED + RIGHT_SPEED;
                    else if (event.key.keysym.sym == SDLK_n) this->reset();
                    break;
                case SDL_KEYUP:
                    this->horizontalSpeed = DEFAULT_HORIZONTAL_SPEED;
                    this->verticalSpeed = DEFAULT_VERTICAL_SPEED;
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
            };
        };

        frames++;
    };


    softwareQuit(charset, screen, scrtex, window, renderer);
}

void gameData::reset() {
    this->currentLevel = DEFAULT_LEVEL_ID;

    this->nextLevel();
}