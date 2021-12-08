#include "framework.h"
#include "Game.h"
#include <stdio.h>
//#include <stdio.h>

// 0 - пустая клетка
// 1 - белая шашка
// 2 - черная шашка
// 31 - выделенная белая
// 32 - выделенная черная
// 33 - клетка врага, которая будет съедена при окончании хода игрока
// 44 - клетки, по которым пройдет наша шашка 
// 55 - клетки, которые предлагаются для хода при выборе шашки
// 999 - королева
int countOfKushats = -1;
int kushats[20][2];
void Сrown(HDC hdc, int cx, int cy, int sizeX, int sizeY, COLORREF color) {

	POINT p[] = {
		cx,		cy - sizeY,
		cx + sizeX / 2,	cy,
		cx + sizeX,	cy - sizeY,
		cx + sizeX,	cy + sizeY,
		cx - sizeX,	cy + sizeY,
		cx - sizeX,	cy - sizeY,
		cx - sizeX / 2,	cy,
		cx,		cy - sizeY
	};

	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 3, color);
	SelectObject(hdc, hPen);
	Polygon(hdc, p, 8);
	DeleteObject(hPen);
}

void Queen() {
	for (int j = 0; j < 8; j++) {
		if (field[0][j] == (numberPlayer)) {
			field[0][j] = (numberPlayer + 2);
		}
	}
}

void movement(bool flag) {

	int rightwardMove, leftwardMove;


	if (!flag) {
		if (countOf(numberPlayer + 2 + 30) != 0) {
			movementOfQueen();
			return;
		}
		if (true) {
			if (y > 0) {
				if (x > 0 && x < 7) {
					if (field[y - 1][x - 1] == 0) field[y - 1][x - 1] = 55;
					if (field[y - 1][x + 1] == 0) field[y - 1][x + 1] = 55;
					if (x > 1 && x < 6 && y > 1) {
						if (field[y - 1][x + 1] == 1 || field[y - 1][x + 1] == 2)
						{
							if (field[y - 2][x + 2] == 0) field[y - 2][x + 2] = 55;
						}
						if (field[y - 1][x - 1] == 1 || field[y - 1][x - 1] == 2)
						{
							if (field[y - 2][x - 2] == 0) field[y - 2][x - 2] = 55;
						}
					}

				}
				else if (x > 0) {
					if (field[y - 1][x - 1] == 0) field[y - 1][x - 1] = 55;
				}
				if (x < 7) {
					if (field[y - 1][x + 1] == 0) field[y - 1][x + 1] = 55;
				}
			}
			if (countOf(numberPlayer + 2 + 30) != 0) {

				if ((x > 1 && x < 6) && (y < 6)) {
					if (field[y + 2][x - 2] == 0 && field[y + 1][x - 1] != 0) field[y + 2][x - 2] = 55;
					if (field[y + 2][x + 2] == 0 && field[y + 1][x + 1] != 0) field[y + 2][x + 2] = 55;
				}
				if ((x > 0 && x < 7) && (y < 7)) {
					if (field[y + 1][x - 1] == 0) field[y + 1][x - 1] = 55;
					if (field[y + 1][x + 1] == 0) field[y + 1][x + 1] = 55;
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


void movementOfQueen() {

	int kX = 1;
	int kY = 1;

	int xy = 0;
	int xY = 0;
	int Xy = 0;
	int XY = 0;

	while (true) {
		bool flagxy = true;
		bool flagxY = true;
		bool flagXy = true;
		bool flagXY = true;

		if (x + kX < 8 && y + kY < 8)
		{
			if (field[y + kY][x + kX] == 0 && XY != 2)
			{
				field[y + kY][x + kX] = 55;
				if (x + kX < 7 && y + kY < 7)
				{
					if (field[y + kY + 1][x + kX + 1] != 0) XY++;
				}

			}
			flagXY = false;
		}
		if (x + kX < 8 && y - kY >= 0)
		{
			if (field[y - kY][x + kX] == 0 && Xy != 2)
			{
				field[y - kY][x + kX] = 55;
				if (x + kX < 7 && y - kY >= 1)
				{
					if (field[y - kY - 1][x + kX + 1] != 0) Xy++;
				}

			}
			flagXy = false;
		}
		if (x - kX >= 0 && y + kY < 8)
		{
			if (field[y + kY][x - kX] == 0 && xY != 2)
			{
				field[y + kY][x - kX] = 55;
				if (x - kX >= 1 && y + kY < 7)
				{
					if (field[y + kY + 1][x - kX - 1] != 0) xY++;
				}

			}
			flagxY = false;
		}
		if (x - kX >= 0 && y - kY >= 0)
		{
			if (field[y - kY][x - kX] == 0 && xy != 2)
			{
				field[y - kY][x - kX] = 55;
				if (x - kX >= 1 && y - kY >= 1)
				{
					if (field[y - kY - 1][x - kX - 1] != 0) xy++;
				}


			}
			flagxy = false;
		}

		if ((flagxy && flagxY && flagXy && flagXY)) break;

		kY++;
		kX++;
	}


}

void QueenWannaEat() {
	int kx = 0;
	int ky = 0;
	int Y = hod[0];
	int X = hod[1];
	if (y - hod[0] > 0) {
		if (x - hod[1] > 0) kx = 1;
		else kx = -1;
		ky = 1;
	}
	else {
		if (x - hod[1] > 0) kx = 1;
		else kx = -1;
		ky = -1;
	}

	while (true) {
		if (hod[0] + ky == y && hod[1] + kx == x) return;
		if (field[hod[0] + ky][hod[1] + kx] != 55)
		{
			field[hod[0] + ky][hod[1] + kx] = 0;
			return;
		}
		ky += ky;
		kx += kx;
	}

}


// отмена хода
void moveCancellation() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (field[i][j] == 44) field[i][j] = 0;
			if (field[i][j] >= 30 && field[i][j] <= 34) {
				field[i][j] %= 30;
			}
		}
	}
}
void kushatts() {
	for (int i = 0; i <= countOfKushats; i++) {
		field[kushats[i][0]][kushats[i][1]] = 0;
	}
}

// уничтожение шашок
void minusChecker(bool flag) {


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (field[i][j] == 44) field[i][j] = 0;
			/*if (field[i][j] == 33) {
				if (numberPlayer == 1) NumberOfFallenBlackCheckers++;
				else NumberOfFallenWhiteCheckers++;
				field[i][j] = 0;
			}*/
			if (flag && (field[i][j] == (numberPlayer + 30) || field[i][j] == (numberPlayer + 30 + 2))) {

				field[y][x] = (field[i][j] % 30);
				field[i][j] = 0;
				flag = false;
			}
		}
	}
	endOfGame();
}

// проверка на доступность хода
bool poedanie() {

	int Ykletka_of_enemy = abs(y + hod[0]) / 2;
	int Xkletka_of_enemy = abs(x + hod[1]) / 2;
	location_of_enemy = &field[Ykletka_of_enemy][Xkletka_of_enemy];
	bool flaag = true;
	if (((x % 2 == 0 && y % 2 == 1) || (x % 2 == 1 && y % 2 == 0)) && (field[y][x] == 0) && *location_of_enemy != 0 && (y + hod[0]) % 2 == 0 && (x + hod[1]) % 2 == 0) {
		if (countOf(31) == 1 || countOf(32) == 1 || countOf(33) == 1 || countOf(34) == 1) {
			if (countOfKushats == 0) {
				if (y <= hod[0]) flaag = true;
			}
			else flaag = false;
			if (flag)
			{
				countOfKushats++;
				kushats[countOfKushats][0] = Ykletka_of_enemy;
				kushats[countOfKushats][1] = Xkletka_of_enemy;
			}
		}
		return true;
	}
	return false;

}

// подсчитывание кол-во выбранных шашок текущего игрока
int countOf(int number) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (field[i][j] == number) count++;
		}
	}
	return count;
}

// действия при нажитии левой кнопки мыши
void leftClickingForTheSecondWindow(HDC hdc, LPARAM lParam) {

	int* currentCell = &field[y][x];

	if ((countOf(numberPlayer + 30) == 0 && (*currentCell == numberPlayer) && (countOf(numberPlayer + 30 + 2) == 0)) ||
		(countOf(numberPlayer + 30 + 2) == 0 && (*currentCell == (numberPlayer + 2)) && countOf(numberPlayer + 30) == 0)){
		*currentCell += 30;
		movement(false);
	}
	else if ((countOf(numberPlayer + 30) == 1 && (*currentCell == numberPlayer || (*currentCell == (numberPlayer + 2)))) ||
			((countOf(numberPlayer + 30 + 2) == 1 && ((*currentCell == (numberPlayer + 2) || (*currentCell == (numberPlayer))))))) {
			*currentCell += 30;
			field[hod[0]][hod[1]] %= 30;
			movement(true);
			movement(false);
	}
	else if ((countOf(numberPlayer + 30) == 1 || countOf(numberPlayer + 30 + 2) == 1) && *currentCell == 44 && y == hod[0] && x == hod[1]) {
		minusChecker(true);
		Queen();
		if (numberPlayer == 1) numberPlayer = 2;
		else numberPlayer = 1;

		kushatts();
		if (statusOfGame == 0) Turning_the_board();
		else {
			statusOfGame = 1;
			window = 3;
		}
		movement(true);
	}
	else if (*currentCell == 55) {
		//field[y][x] = (numberPlayer % 30);
		field[y][x] = field[hod[0]][hod[1]] % 30;
		field[hod[0]][hod[1]] = 0;
		QueenWannaEat();
		//if (field[y][x] % 30 == 3 || field[y][x] == 4) {
		//	//QueenWannaEat();
		//}
		int ySr = (y + hod[0]);
		int xSr = (x + hod[1]);
		if (ySr % 2 == 0 && xSr % 2 == 0)
		{
			if (field[ySr / 2][xSr / 2] == 1 || field[ySr / 2][xSr / 2] == 2) field[ySr / 2][xSr / 2] = 0;
		}

		movement(true);
		Queen();
		if (numberPlayer == 1) numberPlayer = 2;
		else numberPlayer = 1;

		Turning_the_board();
	}
	else
	{
		//field[hod[0]][hod[1]] %= 30;
		moveCancellation();
		movement(true);
	}


	//if (y == 0) *currentCell += 963;
	Queen();
}

// первое окно
void FirstWindow(HDC hdc) {
	HBRUSH firstWindow = CreateSolidBrush(RGB(211, 119, 49));
	SelectObject(hdc, firstWindow);
	Rectangle(hdc, 0, 0, 1300, 856);
	DeleteObject(firstWindow);
}

// действия при нажитии второй кнопки мыши
void rightClickingForTheSecondWindow(HDC hdc, LPARAM lParam) {

	if ((countOf(numberPlayer + 30) == 1 || countOf(numberPlayer + 30 + 2) == 1) && poedanie()) {
		field[y][x] = 44;
		//*location_of_enemy = 33;
	}
	else {
		field[hod[0]][hod[1]] %= 30;
	}
}

// отрисовка шашок
void shading_the_checkers(HDC hdc, int j, int i) {

	HBRUSH cell_first_player, cell_second_player, H_selected_cells, white_cage, black_cage;

	cell_second_player = CreateSolidBrush(RGB(33, 33, 33)); // цвет шашки первого игрока
	cell_first_player = CreateSolidBrush(RGB(231, 231, 231)); // цвет шашки второго игрока
	H_selected_cells = CreateSolidBrush(RGB(205, 133, 63)); // цвет оконтовки шашки при многократном ходе
	//RGB(15, 46, 66)
	white_cage = CreateSolidBrush(RGB(231, 187, 154));
	black_cage = CreateSolidBrush(RGB(126, 56, 3));


	HPEN stroke_first_player_cell, stroke_second_player_cell, selected_cells, green_cell, strokeCell, eatenUp;

	strokeCell = CreatePen(PS_SOLID, 8, RGB(254, 194, 57));
	eatenUp = CreatePen(PS_SOLID, 8, RGB(255, 69, 34));
	selected_cells = CreatePen(PS_SOLID, 8, RGB(205, 133, 63)); // цвет шашки при многократном ходе
	green_cell = CreatePen(PS_SOLID, 8, RGB(0, 255, 0)); // цвет выделенной ячейки
	stroke_second_player_cell = CreatePen(PS_SOLID, 8, RGB(0, 0, 0)); // цвет оконтовки шашки второго игрока
	stroke_first_player_cell = CreatePen(PS_SOLID, 8, RGB(255, 255, 255)); // цвет оконтовки шашки первого игрока


	int cx = (i + 1) * 100 - 50;
	int cy = (j + 1) * 100 - 50;

	if (field[j][i] == 2) { // закрашивание шашки второго игрока
		SelectObject(hdc, stroke_second_player_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}

	if (field[j][i] == 4) {
		SelectObject(hdc, stroke_second_player_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		Сrown(hdc, cx, cy, 20, 20, RGB(255, 255, 255));
	}

	else if (field[j][i] == 1) {  // закрашивание шашки первого игрока
		SelectObject(hdc, stroke_first_player_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}

	else if (field[j][i] == 3) {
		SelectObject(hdc, stroke_first_player_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		Сrown(hdc, cx, cy, 20, 20, RGB(0, 0, 0));
	}

	if (field[j][i] == 31) { // закрашивание выделенной шашки первого игрока
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}
	if (field[j][i] == 33) {
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		Сrown(hdc, cx, cy, 20, 20, RGB(0, 0, 0));

	}
	else if (field[j][i] == 32) {  // закрашивание выделенной шашки второго игрока
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}
	else if (field[j][i] == 34) {
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		Сrown(hdc, cx, cy, 20, 20, RGB(255, 255, 255));
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
	/*else if (field[j][i] == 33) {
		SelectObject(hdc, eatenUp);
		if (numberPlayer == 1) SelectObject(hdc, cell_second_player);
		else SelectObject(hdc, cell_first_player);
		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}*/

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

// второе окно
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
	TextOut(hdc, 1115, 50, (LPCWSTR)tNumberOfFallenWhiteCheckers, _tcslen(tNumberOfFallenWhiteCheckers));


	char nNumberOfFallenBlackCheckers[5];
	TCHAR  tNumberOfFallenBlackCheckers[5];
	sprintf(nNumberOfFallenBlackCheckers, "%d", NumberOfFallenBlackCheckers);
	OemToChar(nNumberOfFallenBlackCheckers, tNumberOfFallenBlackCheckers);
	TextOut(hdc, 1125, 70, (LPCWSTR)tNumberOfFallenBlackCheckers, _tcslen(tNumberOfFallenBlackCheckers));

	int xxx = countOf(1) + countOf(31);
	TCHAR string3[] = _T("Игрок, который сейчас ходит: ");
	TextOut(hdc, 900, 90, (LPCWSTR)string3, _tcslen(string3));
	char nnumberPlayer[5];
	TCHAR  tnumberPlayer[5];
	sprintf(nnumberPlayer, "%d", numberPlayer);
	OemToChar(nnumberPlayer, tnumberPlayer);
	TextOut(hdc, 1185, 90, (LPCWSTR)tnumberPlayer, _tcslen(tnumberPlayer));

	TCHAR string4[] = _T("Кол-во белых шашек: ");
	TextOut(hdc, 900, 110, (LPCWSTR)string4, _tcslen(string4));
	//char nnumberPlayer[5];
	//TCHAR  tnumberPlayer[5];
	sprintf(nnumberPlayer, "%d", countOf(1) + countOf(31) + countOf(33) + countOf(3));
	OemToChar(nnumberPlayer, tnumberPlayer);
	TextOut(hdc, 1095, 110, (LPCWSTR)tnumberPlayer, _tcslen(tnumberPlayer));


	TCHAR string5[] = _T("Кол-во черных шашек: ");
	TextOut(hdc, 900, 130, (LPCWSTR)string5, _tcslen(string5));
	//char nnumberPlayer[5];
	//TCHAR  tnumberPlayer[5];
	sprintf(nnumberPlayer, "%d", countOf(2) + countOf(32) + countOf(34) + countOf(4));
	OemToChar(nnumberPlayer, tnumberPlayer);
	TextOut(hdc, 1105, 130, (LPCWSTR)tnumberPlayer, _tcslen(tnumberPlayer));

};

// переворот доски
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

// конец игры
int endOfGame() {
	if (NumberOfFallenBlackCheckers == 13) {
		window = 4;
		statusOfGame = 1;
		return 1;
	}
	else if (NumberOfFallenWhiteCheckers == 12) {
		statusOfGame = 1;
		window = 4;
		return 2;
	}
	else return 0;
}
