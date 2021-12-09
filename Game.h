#pragma once
#include "framework.h"

void SecondWindow(HDC hdc);
void shading_the_checkers(HDC hdc, int j, int i);
void Turning_the_board();
void leftClickingForTheSecondWindow(HDC hdc, LPARAM lParam);
void rightClickingForTheSecondWindow(HDC hdc, LPARAM lParam);
void FirstWindow(HDC hdc);
void movement(bool flag);
int countOf(int number); 
bool poedanie();
void minusChecker(bool flag);
void moveCancellation();
void Ñrown(HDC hdc, int cx, int cy, int sizeX, int sizeY, COLORREF color);
void Queen();
void kushatts();
void movementOfQueen();
void saveGame();
void loadGame();
void LoadingTheInitialGame();

struct FIELD {
    int map[8][8];
    int numberOfWhiteCheckers;
    int numberOfBlackCheckers;
    int numberPlayer;
};

extern int hod[2];
extern int field[8][8];
extern FIELD f;
extern int x, y;
extern bool flag;
extern int* location_of_enemy;
extern int numberPlayer;
extern int steps;
extern int statusOfGame;
extern int NumberOfFallenWhiteCheckers;
extern int NumberOfFallenBlackCheckers;
extern int window;
extern int endOfGame();