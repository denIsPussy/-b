#pragma once
#include "framework.h"

void SecondWindow(HDC hdc, int numberPlayer);
void shading_the_checkers(HDC hdc, int j, int i);
void Turning_the_board();
void clicking(int flag);
void normal_course();
void strokeCleaning();
void leftClickingForTheSecondWindow(HDC hdc, LPARAM lParam);
void rightClickingForTheSecondWindow(HDC hdc, LPARAM lParam);
void FirstWindow(HDC hdc);

extern int field[8][8];
extern int cell[20][2];
extern int click[2][2];
extern int x, y;
extern bool flag;
extern int numberPlayer;
extern int steps;
extern int NumberOfFallenWhiteCheckers;
extern int NumberOfFallenBlackCheckers;
extern int count_of_cell;
extern int count_of_click;
