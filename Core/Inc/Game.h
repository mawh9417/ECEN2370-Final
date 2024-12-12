#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>
#include <stdio.h>
#include "LCD_Driver.h"
#include "RNG.h"
#include "Timer_Driver.h"

void screenOne();
void endGameScreen();

void drawWhiteSquare(uint16_t x, uint16_t y);

// DRAW ALL SHAPES
void drawShapeO(uint16_t x, uint16_t y, uint16_t color);
void removeShapeO(uint16_t x, uint16_t y);

void drawShapeI(uint16_t x, uint16_t y, uint16_t color);
void drawShapeI2(uint16_t x, uint16_t y, uint16_t color);
void removeShapeI(uint16_t x, uint16_t y);
void removeShapeI2(uint16_t x, uint16_t y);

void drawShapeS(uint16_t x, uint16_t y, uint16_t color);
void drawShapeS2(uint16_t x, uint16_t y, uint16_t color);
void drawShapeS3(uint16_t x, uint16_t y, uint16_t color);
void drawShapeS4(uint16_t x, uint16_t y, uint16_t color);
void removeShapeS(uint16_t x, uint16_t y);
void removeShapeS2(uint16_t x, uint16_t y);
void removeShapeS3(uint16_t x, uint16_t y);
void removeShapeS4(uint16_t x, uint16_t y);


void drawShapeZ(uint16_t x, uint16_t y, uint16_t color);
void drawShapeZ2(uint16_t x, uint16_t y, uint16_t color);
void drawShapeZ3(uint16_t x, uint16_t y, uint16_t color);
void drawShapeZ4(uint16_t x, uint16_t y, uint16_t color);
void removeShapeZ(uint16_t x, uint16_t y);
void removeShapeZ2(uint16_t x, uint16_t y);
void removeShapeZ3(uint16_t x, uint16_t y);
void removeShapeZ4(uint16_t x, uint16_t y);


void drawShapeL(uint16_t x, uint16_t y, uint16_t color);
void drawShapeL2(uint16_t x, uint16_t y, uint16_t color);
void drawShapeL3(uint16_t x, uint16_t y, uint16_t color);
void drawShapeL4(uint16_t x, uint16_t y, uint16_t color);
void removeShapeL(uint16_t x, uint16_t y);
void removeShapeL2(uint16_t x, uint16_t y);
void removeShapeL3(uint16_t x, uint16_t y);
void removeShapeL4(uint16_t x, uint16_t y);

void drawShapeJ(uint16_t x, uint16_t y, uint16_t color);
void drawShapeJ2(uint16_t x, uint16_t y, uint16_t color);
void drawShapeJ3(uint16_t x, uint16_t y, uint16_t color);
void drawShapeJ4(uint16_t x, uint16_t y, uint16_t color);
void removeShapeJ(uint16_t x, uint16_t y);
void removeShapeJ2(uint16_t x, uint16_t y);
void removeShapeJ3(uint16_t x, uint16_t y);
void removeShapeJ4(uint16_t x, uint16_t y);


void drawShapeT(uint16_t x, uint16_t y, uint16_t color);
void drawShapeT2(uint16_t x, uint16_t y, uint16_t color);
void drawShapeT3(uint16_t x, uint16_t y, uint16_t color);
void drawShapeT4(uint16_t x, uint16_t y, uint16_t color);
void removeShapeT(uint16_t x, uint16_t y);
void removeShapeT2(uint16_t x, uint16_t y);
void removeShapeT3(uint16_t x, uint16_t y);
void removeShapeT4(uint16_t x, uint16_t y);


void rotateShape();
void drawRandomShape();
void gameDelay();
void moveDownOne();
void moveOneRight();
void moveOneLeft();
void rotateShape();

bool Has_Touched_Bottom();
bool White_Space_Below();
bool Collision_Detect();
void Row_Check_Delete();

void executeGame();

#endif
