#pragma once
#include "framework.h"

void SecondWindow(HDC hdc);
void shading_the_checkers(HDC hdc, int j, int i);
void Turning_the_board(HWND hWnd);
void leftClickingForTheSecondWindow(HDC hdc, LPARAM lParam, HWND hWnd);
void rightClickingForTheSecondWindow(HDC hdc, LPARAM lParam);
void FirstWindow(HDC hdc, HWND hWnd, HINSTANCE hInst);
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
void SaveRecords();
void LoadRecords();
void LoadingTheInitialGame();
void DrawRecords(HDC hdc);
void InsertRecord(char name[], bool flag, int temp);
int CompareRecords(int index1, int index2);
void addRecord(char name[]);
void mini_menu(HDC hdc);
//void RegistrationOfPlayer(HWND hWnd, HINSTANCE hInst, static HWND hEdt1, static HWND hBtn1, static HWND hBtn2, static HWND hEdt2);

struct FIELD {
    int map[8][8];
    int numberOfWhiteCheckers;
    int numberOfBlackCheckers;
    int numberPlayer;
    int numberOfMovesPlayer1;
    int numberOfMovesPlayer2;
};




extern int hod[2];
extern int field[8][8];




extern FIELD f;
extern int x, y;
extern bool flag;
extern int* location_of_enemy;
extern int numberPlayer;
extern int steps;
extern int registration;
extern char str1[20];
extern int massivTimer[31];
extern char str2[20];
extern int numberOfMovesPlayer1;
extern int numberOfMovesPlayer2;
extern const int MAX_NUM_RECORDS;
extern int numRecords;
extern int statusOfGame;
extern int timerDigit;
extern int NumberOfFallenWhiteCheckers;
extern int NumberOfFallenBlackCheckers;
extern int window;
extern int window_menu;
extern int endOfGame();
void SaveRecordsEncoded();
void LoadRecordsEncoded();