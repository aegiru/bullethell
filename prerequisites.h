//
// Created by Doppie on 1/10/2022.
//

#ifndef BULLET_HELL_PREREQUISITES_H
#define BULLET_HELL_PREREQUISITES_H

#include <SDL.h>

void LocalDrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);

void LocalDrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

void LocalDrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

void LocalDrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);

void LocalDrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

void softwareQuit(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer);

int softwareCrash(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer);

double minimum(double a, double b);

double maximum(double a, double b);

double negativeFlatConversion(double a);

double positiveFlatConversion(double a);

double isAboveZero(double a);

double isBelowZero(double a);

#endif //BULLET_HELL_PREREQUISITES_H