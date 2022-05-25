//
// Created by Doppie on 1/10/2022.
//

#include "prerequisites.h"

#include <SDL.h>
#include <stdio.h>

void LocalDrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;

    while (*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += 8;
        text++;
    };
};



void LocalDrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
};



void LocalDrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32*)p = color;
};



void LocalDrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
    for (int i = 0; i < l; i++) {
        LocalDrawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    };
};



void LocalDrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
    int i;
    LocalDrawLine(screen, x, y, k, 0, 1, outlineColor);
    LocalDrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
    LocalDrawLine(screen, x, y, l, 1, 0, outlineColor);
    LocalDrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
    for (i = y + 1; i < y + k - 1; i++)
        LocalDrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};



void softwareQuit(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_FreeSurface(screen);
    SDL_DestroyTexture(scrtex);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}



int softwareCrash(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer) {
    printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
    softwareQuit(charset, screen, scrtex, window, renderer);
    SDL_Quit();
    return 1;
}

double minimum(double a, double b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

double maximum(double a, double b) {
    if (a < b) {
        return b;
    } else {
        return a;
    }
}

double negativeFlatConversion(double a) {
    if (a < 0) {
        return -1;
    } else {
        return 1;
    }
}

double positiveFlatConversion(double a) {
    return (negativeFlatConversion(-a));
}

double isAboveZero(double a) {
    if (a > 0) {
        return 1;
    } else {
        return 0;
    }
}

double isBelowZero(double a) {
    return isAboveZero(-a);
}