#include "framework.h"
#include "Game.h"
#include <stdio.h>
//#include <stdio.h>

void movement(bool flag) {
	
	int rightwardMove, leftwardMove;

	
	if (!flag) {
		if (count_of_click == 1 || count_of_click == 2) {
			if (y >= 0) {
				if (x > 0 && x < 7) {
					if (field[y - 1][x - 1] == 0) field[y - 1][x - 1] = 55;
					if (field[y - 1][x + 1] == 0) field[y - 1][x + 1] = 55;

				}
				else if (x > 0) {
					if (field[y - 1][x - 1] == 0) field[y - 1][x - 1] = 55;
				}
				if (x < 7) {
					if (field[y - 1][x + 1] == 0) field[y - 1][x + 1] = 55;
				}
			}
		}
	}

	if (flag) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (field[i][j] == 55) field[i][j] = 0;
			}
		}
	}
}

void strokeCleaning() {
	for (int i = 0; i < count_of_cell; i++) {

		if (i == 0) {
			field[y][x] %= 30;
		}
		else field[y][x] = 0;
	}
}

void cleaningOfCell() {
	for (int i = 0; i <= count_of_cell; i++) {
		cell[i][0] = 0;
		cell[i][1] = 0;
	}
}



void leftClickingForTheSecondWindow(HDC hdc, LPARAM lParam) {
	
	int timeVariable;
	int yOfpreviousСell = cell[count_of_cell - 1][0];
	int xOfpreviousСell = cell[count_of_cell - 1][1];
	int *currentCell = &field[y][x];

	if (count_of_cell == 0) {
		timeVariable = 0;
	}
	else {
		timeVariable = count_of_cell;
	}

	cell[timeVariable][0] = y;
	cell[timeVariable][1] = x;
	count_of_click++;

	movement(false);

	if (count_of_click == 2) {

		if (count_of_cell == 0) clicking(1);
		else 
		{
			if (y == yOfpreviousСell && x == xOfpreviousСell) clicking(3);
			else strokeCleaning();
			count_of_cell = 0;
			count_of_click = 0;
			cleaningOfCell();
		}
	}
	else if (count_of_click == 1 && *currentCell != 0) *currentCell += 30;

}


void FirstWindow(HDC hdc) {
	HBRUSH firstWindow = CreateSolidBrush(RGB(211, 119, 49));
	SelectObject(hdc, firstWindow);
	Rectangle(hdc, 0, 0, 1300, 856);
	DeleteObject(firstWindow);
}


void rightClickingForTheSecondWindow(HDC hdc, LPARAM lParam) {

	if (count_of_click == 1) {
		clicking(2);
	}

}


void normal_course() {

}



void shading_the_checkers(HDC hdc, int j, int i) {

	HBRUSH cell_first_player, cell_second_player, H_selected_cells, white_cage, black_cage;

	cell_first_player = CreateSolidBrush(RGB(33, 33, 33)); // цвет шашки первого игрока
	cell_second_player = CreateSolidBrush(RGB(231, 231, 231)); // цвет шашки второго игрока
	H_selected_cells = CreateSolidBrush(RGB(205, 133, 63)); // цвет оконтовки шашки при многократном ходе
	//RGB(15, 46, 66)
	white_cage = CreateSolidBrush(RGB(231, 187, 154));
	black_cage = CreateSolidBrush(RGB(126, 56, 3));


	HPEN stroke_first_player_cell, stroke_second_player_cell, selected_cells, green_cell, strokeCell;

	strokeCell = CreatePen(PS_SOLID, 8, RGB(254, 194, 57));
	selected_cells = CreatePen(PS_SOLID, 8, RGB(205, 133, 63)); // цвет шашки при многократном ходе
	green_cell = CreatePen(PS_SOLID, 8, RGB(0, 255, 0)); // цвет выделенной ячейки
	stroke_first_player_cell = CreatePen(PS_SOLID, 8, RGB(0, 0, 0)); // цвет оконтовки шашки первого игрока
	stroke_second_player_cell = CreatePen(PS_SOLID, 8, RGB(255, 255, 255)); // цвет оконтовки шашки второго игрока


	int cx = (i + 1) * 100 - 50;
	int cy = (j + 1) * 100 - 50;

	if (field[j][i] == 1) { // закрашивание шашки первого игрока
		SelectObject(hdc, stroke_first_player_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}
	else if (field[j][i] == 2) {  // закрашивание шашки второго игрока
		SelectObject(hdc, stroke_second_player_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}

	if (field[j][i] == 31) { // закрашивание выделенной шашки первого игрока
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}
	else if (field[j][i] == 32) {  // закрашивание выделенной шашки второго игрока
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}
	if (field[j][i] == 44) { // закрашивание шашки при многократном ходе
		SelectObject(hdc, selected_cells);
		SelectObject(hdc, H_selected_cells);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}
	if (field[j][i] == 55) { 
		SelectObject(hdc, strokeCell);
		SelectObject(hdc, black_cage);
		Rectangle(hdc, cx - 46, cy - 46, cx + 48, cy + 48);
	}

	DeleteObject(cell_first_player);
	DeleteObject(cell_second_player);
	DeleteObject(H_selected_cells);
	DeleteObject(selected_cells);
	DeleteObject(green_cell);
	DeleteObject(stroke_first_player_cell);
	DeleteObject(stroke_second_player_cell);
	DeleteObject(strokeCell);
	DeleteObject(white_cage);
	DeleteObject(black_cage);
};


void SecondWindow(HDC hdc) { // отрисовка игрового поля в целом

	HBRUSH cell_first_player_cell, cell_second_player_cell, white_cage, black_cage;

	white_cage = CreateSolidBrush(RGB(231, 187, 154));
	black_cage = CreateSolidBrush(RGB(126, 56, 3));

	HPEN stroke_first_player_cell, stroke_second_player_cell, selected_cells, green_cell, H_white_cage, H_black_cage;

	H_white_cage = CreatePen(PS_SOLID, 1, RGB(231, 187, 154));
	H_black_cage = CreatePen(PS_SOLID, 1, RGB(126, 56, 3));

	int x = 0;
	int y = 0;
	int paint_identifier = 0;

	for (int i = 0; i < 8; i++) {

		SelectObject(hdc, H_black_cage);
		if (i % 2 == 0) {
			paint_identifier = 0;
		}

		else paint_identifier = 1;


		for (int j = 0; j < 8; j++) {

			if (j % 2 == paint_identifier) {
				SelectObject(hdc, white_cage);
			}
			else {
				SelectObject(hdc, black_cage);
			}
			Rectangle(hdc, x, y, x + (800 / 8) + 1, y + (800 / 8) + 1);
			x += 800 / 8;
		}

		y += 800 / 8;
		x = 0;

	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			shading_the_checkers(hdc, i, j);

		}
	}

	DeleteObject(H_black_cage);
	DeleteObject(black_cage);
	DeleteObject(white_cage);
	DeleteObject(H_white_cage);

	HFONT hFont;
	hFont = CreateFont(20,
		0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Courier New"
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 128, 128));

	TCHAR  string1[] = _T("Потеряно белых шашек: ");
	TCHAR  string2[] = _T("Потеряно черных шашек: ");
	TextOut(hdc, 900, 50, (LPCWSTR)string1, _tcslen(string1));
	TextOut(hdc, 900, 70, (LPCWSTR)string2, _tcslen(string2));
	char nNumberOfFallenWhiteCheckers[5];
	TCHAR  tNumberOfFallenWhiteCheckers[5];
	sprintf(nNumberOfFallenWhiteCheckers, "%d", NumberOfFallenWhiteCheckers);
	OemToChar(nNumberOfFallenWhiteCheckers, tNumberOfFallenWhiteCheckers);
	TextOut(hdc, 1110, 50, (LPCWSTR)tNumberOfFallenWhiteCheckers, _tcslen(tNumberOfFallenWhiteCheckers));


	char nNumberOfFallenBlackCheckers[5];
	TCHAR  tNumberOfFallenBlackCheckers[5];
	sprintf(nNumberOfFallenBlackCheckers, "%d", NumberOfFallenBlackCheckers);
	OemToChar(nNumberOfFallenBlackCheckers, tNumberOfFallenBlackCheckers);
	TextOut(hdc, 1120, 70, (LPCWSTR)tNumberOfFallenBlackCheckers, _tcslen(tNumberOfFallenBlackCheckers));


	TCHAR string3[] = _T("Игрок, который сейчас ходит: ");
	TextOut(hdc, 900, 90, (LPCWSTR)string3, _tcslen(string3));
	char nnumberPlayer[5];
	TCHAR  tnumberPlayer[5];
	sprintf(nnumberPlayer, "%d", numberPlayer);
	OemToChar(nnumberPlayer, tnumberPlayer);
	TextOut(hdc, 1180, 90, (LPCWSTR)tnumberPlayer, _tcslen(tnumberPlayer));



};

void Turning_the_board() {
	int end = 7;
	int x;
	for (int begin = 0; begin < 8; begin++) {
		for (int j = 0; j < 8; j++) {
			x = field[begin][j];
			field[begin][j] = field[end][7 - j];
			field[end][7 - j] = x;
		}
		end--;
		if (begin == end) {
			break;
		}

	}
};

bool checking_cell(int x, int y) {
	if (x % 2 == 1 && y % 2 == 0) return true;
	return false;
}

void clicking(int flag) {


	// Переменная-флаг для действий с шашками
	//////////////////////////////
	int flag1_ = false;
	//////////////////////////////


	// Переменные для проверки четности клетки врага
	////////////////////////////////
	int checkk_ = cell[count_of_cell][0] + cell[count_of_cell - 1][0];
	int checkk1_ = cell[count_of_cell][1] + cell[count_of_cell - 1][1];
	////////////////////////////////



	// Клетка, которую едим
	///////////////////////////////
	int Ykletka_of_enemy = abs(cell[count_of_cell][0] + cell[count_of_cell - 1][0]) / 2;
	int Xkletka_of_enemy = abs(cell[count_of_cell][1] + cell[count_of_cell - 1][1]) / 2;

	int* location_of_enemy = &field[Ykletka_of_enemy][Xkletka_of_enemy];
	//////////////////////////////



	// Самая первая ячейка
	///////////////////////////////
	int Xstarting_cell = cell[0][1];
	int Ystarting_cell = cell[0][0];

	int* first_clicking = &field[cell[0][0]][cell[0][1]];
	//////////////////////////////



	// Вторая ячейка
	/////////////////////////////
	int* second_clicking = &field[cell[1][0]][cell[1][1]];
	/////////////////////////////



	// Самая последняя ячейка
	/////////////////////////////
	int Xfinal_cell = cell[count_of_cell - 1][1];
	int Yfinal_cell = cell[count_of_cell - 1][0];

	int* final_cell = &field[Yfinal_cell][Xfinal_cell]; 
	/////////////////////////////
	//  || (*second_clicking == *first_clicking && (cell[0][0] != cell[1][0] || cell[0][1] != cell[1][1]))
	if (*second_clicking == 55) {
		
		// Передвигаем шашку вперед
		//////////
		*second_clicking = (*first_clicking % 30);
		movement(true);
		*first_clicking = 0;
		//////////
		cleaningOfCell();
		count_of_cell = 0;
		count_of_click = 0;
		Turning_the_board();
		if (numberPlayer == 1) numberPlayer = 2;
		else if (numberPlayer == 2) numberPlayer = 1;
		return;
	}
	if (flag == 1) {
		if (*first_clicking == *second_clicking) {
			*first_clicking %= 30;
			*second_clicking %= 30;
			count_of_click = 0;
			cleaningOfCell();
			movement(true);
		}
		else if (*second_clicking == 0) {
			count_of_click = 0;
			*first_clicking %= 30;
			cleaningOfCell();
			movement(true);
		}
		else {
			movement(true);
			if (*second_clicking == (*first_clicking % 30)) {
				*first_clicking %= 30;
				*second_clicking += 30;
				cell[0][0] = cell[1][0];
				cell[0][1] = cell[1][1];
				count_of_click = 1;
				count_of_cell = 1;
				movement(false);
			}
			else {
				cleaningOfCell();
				*first_clicking %= 30;
				//movement(false);
				count_of_click = 0;
			}
			movement(false);
			
		}

	}
	if (flag == 2)
	{
		count_of_cell++;
		cell[count_of_cell][0] = y;
		cell[count_of_cell][1] = x;

		if (((x % 2 == 0 && y % 2 == 1) || (x % 2 == 1 && y % 2 == 0)) && (field[y][x] == 0) && *location_of_enemy != 0 && checkk_ % 2 == 0 && checkk1_ % 2 == 0) {
			field[y][x] = 44;
		}
		else count_of_cell--;
	}
	if (flag == 3)
	{
		
		for (int i = 1; i <= count_of_cell - 1; i++) {

			int x = cell[i][1];
			int y = cell[i][0];
			field[y][x] = 0;

			if (i <= count_of_cell - 1) {
				int Ykletka_of_enemy = abs(cell[i - 1][0] + cell[i][0]) / 2;
				int Xkletka_of_enemy = abs(cell[i - 1][1] + cell[i][1]) / 2;
				field[Ykletka_of_enemy][Xkletka_of_enemy] = 0;
			}
		}

		*final_cell = *first_clicking % 30;
		*first_clicking = 0;
		if (numberPlayer == 1) NumberOfFallenBlackCheckers += (count_of_cell - 1);
		else NumberOfFallenWhiteCheckers += (count_of_cell - 1);
		if (numberPlayer == 1) numberPlayer = 2;
		else if (numberPlayer == 2) numberPlayer = 1;
		movement(true);
		Turning_the_board();
	}

}

