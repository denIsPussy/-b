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
#define TIME 30
#define MAX_LEN 100



#define KEY +3

// Шифрование одной буквы ch ключом KEY
int encodeChar(int ch) {
	//char smallLetters[] ="abcdefghijklmnopqrstuvwxyz";
	//char bigLetters[]   ="ABCDEGGHIJKLMNOPQRSTUVWXYZ";

	int newCh = ch;

	if (ch >= 'A' && ch <= 'Z') {
		newCh = ch + KEY;
		if (newCh > 'Z')
			newCh = 'A' + (newCh - 'Z' - 1);
	}

	if (ch >= 'a' && ch <= 'z') {
		newCh = ch + KEY;
		if (newCh > 'z')
			newCh = 'a' + (newCh - 'z' - 1);
	}

	return newCh;
}



struct FIELD* mapp = &f;
int countOfKushats = -1;
int kushats[20][2];
struct Record {
	char name[20];
	int winCount;
	int lossCount;
	int numberOfMovesPlayer;
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
};
struct Record records[10 + 1];
bool pawnCheck(int n) {
	for (int i = 1; i < 5; i++) {
		if (n == i) return true;
	}
	return false;
}

void mini_menu(HDC hdc) {
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hbrush);
	if (window == 2) {
		hbrush = CreateSolidBrush(RGB(206, 104, 38));
		SelectObject(hdc, hbrush);
		Rectangle(hdc, 200, 250, 600, 560);
		DeleteObject(hbrush);
		hbrush = CreateSolidBrush(RGB(192, 159, 119));
		SelectObject(hdc, hbrush);
	}
	else SelectObject(hdc, hbrush);

	Rectangle(hdc, 200, 250, 600, 560);
	DeleteObject(hbrush);

	Rectangle(hdc, 310 + 5, 250 + 40 + 60, 490 + 5, 250 + 40 + 30 + 70);
	Rectangle(hdc, 310 + 5, 250 + 2*40 + 30 + 60, 490 + 5, 250 + 2*40 + 2*30 + 70);
	Rectangle(hdc, 310 + 5, 250 + 3*40 + 2*30 + 60, 490 + 5, 250 + 3 * 40 + 3 * 30 + 70);
	if (window == 2) DeleteObject(hbrush);
	HFONT hFont;
	SetBkMode(hdc, TRANSPARENT);
	hFont = CreateFont(50,
		0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Courier New"
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 0));
	TCHAR  string2[] = _T("MENU");
	TextOut(hdc, 297 + 50, 270, (LPCWSTR)string2, _tcslen(string2));
	DeleteObject(hFont);

	
	TCHAR  string3[] = _T("Continue");
	TCHAR  string3_1[] = _T("Home");
	TCHAR  string4[] = _T("Scoreboard");
	TCHAR  string5[] = _T("Exit");
	hFont = CreateFont(30,
		0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Courier New"
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 0));
	if (window != 2) TextOut(hdc, 325 + 18 + 20 + 10, 250 + 40 + 60 + 5, (LPCWSTR)string3_1, _tcslen(string3_1));
	else TextOut(hdc, 325 + 18, 250 + 40 + 60 + 5, (LPCWSTR)string3, _tcslen(string3));
	TextOut(hdc, 325, 250 + 2*40 + 60 + 15 + 20, (LPCWSTR)string4, _tcslen(string4));
	TextOut(hdc, 325 + 18*3, 250 + 3*40 + 2*60 + 5, (LPCWSTR)string5, _tcslen(string5));
	DeleteObject(hFont);
	//TextOut(hdc, 650, 20, _T("Имя игрока"), 10);
	//TextOut(hdc, 650, 20, _T("Имя игрока"), 10);
}
int decodeChar(int ch) {
	//char smallLetters[] ="abcdefghijklmnopqrstuvwxyz";
	//char bigLetters[]   ="ABCDEGGHIJKLMNOPQRSTUVWXYZ";

	int newCh = ch;

	if (ch >= 'A' && ch <= 'Z') {
		newCh = ch - KEY;
		if (newCh < 'A')
			newCh = 'Z' - ('A' - newCh - 1);
	}

	if (ch >= 'a' && ch <= 'z') {
		newCh = ch - KEY;
		if (newCh < 'a')
			newCh = 'z' - ('a' - newCh - 1);
	}

	return newCh;
}

void decodeString2(char* str) {

	while (*str) {
		*str = decodeChar(*str);
		++str;
	}
}
void encodeString(char str[]) {
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		str[i] = encodeChar(str[i]);
	}
}

void decodeString(char* str) {
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		str[i] = decodeChar(str[i]);
	}
}

void LoadRecordsEncoded() {
	// Открываем файл с рекордами на чтение
	FILE* fin = fopen("recordsEncoded.txt", "rt");
	if (fin == NULL) {
		// выходим, не загрузив рекорды из файла
		return;
	}
	char str[MAX_LEN];

	fgets(str, MAX_LEN - 1, fin);
	decodeString(str);
	sscanf(str, "%d", &numRecords);
	int i;
	for (i = 0; i < numRecords; i++) {
		// сохраняем в файле каждое поле каждого рекорда
		fgets(str, MAX_LEN - 1, fin);
		decodeString2(str);

		sscanf(str, "%s%d%d%d%d%d%d%d%d\n",
			records[i].name,
			&records[i].winCount,
			&records[i].lossCount,
			&records[i].year,
			&records[i].month,
			&records[i].day,
			&records[i].hour,
			&records[i].minute,
			&records[i].second
		);
	}
	// закрываем файл
	fclose(fin);
}

void SaveRecordsEncoded() {
	// Запись в выходной файл
	FILE* fout = fopen("recordsEncoded.txt", "wt");
	if (fout == NULL) {
		// выходим, не сохранив результаты в файл
		return;
	}

	char str[MAX_LEN];
	sprintf(str, "%d\n", numRecords);
	encodeString(str);
	fprintf(fout, "%s", str);

	int i;
	for (i = 0; i < numRecords; i++) {
		// сохраняем в файле каждое поле каждого рекорда
		sprintf(str, "%s %d %d %d %d %d %d %d %d\n",
			records[i].name,
			records[i].winCount,
			records[i].lossCount,
			records[i].year,
			records[i].month,
			records[i].day,
			records[i].hour,
			records[i].minute,
			records[i].second
		);
		encodeString(str);
		fprintf(fout, "%s", str);
	}
	// закрываем файл
	fclose(fout);
}



int countOfCheckers(int i) {
	if (i == 1) return countOf(1) + countOf(31) + countOf(33) + countOf(3);
	if (i == 2) return countOf(2) + countOf(32) + countOf(34) + countOf(4);
}

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
void addRecord(char name[])
{
	//if (numRecords >= MAX_NUM_RECORDS) {
	//numRecords = numRecords - 1;
	//}

	strcpy(records[numRecords].name, name);
	records[numRecords].winCount = 0;
	records[numRecords].lossCount = 0;
	records[numRecords].numberOfMovesPlayer = 0;

	SYSTEMTIME st;
	// Получаем текущее время
	GetLocalTime(&st);

	// и разбрасываем его по полям в таблицу рекордов
	records[numRecords].year = st.wYear;
	records[numRecords].month = st.wMonth;
	records[numRecords].day = st.wDay;

	records[numRecords].hour = st.wHour;
	records[numRecords].minute = st.wMinute;
	records[numRecords].second = st.wSecond;
	// Следующий раз будем записывать рекорд в следующий элемент	
	numRecords++;
}
char saveText[] = "C:\\Users\\Movavi\\source\\repos\\шашки\\-b\\save.txt";
char loadText[] = "C:\\Users\\Movavi\\source\\repos\\шашки\\-b\\save.txt";

void saveGame() {
	FILE* Save = fopen("save.txt", "wt");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fprintf(Save, "%d ", mapp->map[i][j]);
		}
		fprintf(Save, "\n");
	}
	fprintf(Save, "%d\n", mapp->numberOfWhiteCheckers);
	fprintf(Save, "%d\n", mapp->numberOfBlackCheckers);
	fprintf(Save, "%d", mapp->numberPlayer);
	fclose(Save);
}

void loadGame() {
	FILE* Load = fopen("save.txt", "rt");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fscanf(Load, "%d ", &mapp->map[i][j]);
		}
		fscanf(Load, "\n");
	}
	fscanf(Load, "%d\n", &mapp->numberOfWhiteCheckers);
	fscanf(Load, "%d\n", &mapp->numberOfBlackCheckers);
	fscanf(Load, "%d", &mapp->numberPlayer);
	fclose(Load);
}


void LoadingTheInitialGame() {
	FILE* Load = fopen("load1.txt", "rt");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fscanf(Load, "%d ", &mapp->map[i][j]);
		}
		fscanf(Load, "\n");
	}
	fscanf(Load, "%d\n", &mapp->numberOfWhiteCheckers);
	fscanf(Load, "%d\n", &mapp->numberOfBlackCheckers);
	fscanf(Load, "%d", &mapp->numberPlayer);
	fclose(Load);
}


void Queen() {
	for (int j = 0; j < 8; j++) {
		if (mapp->map[0][j] == (mapp->numberPlayer)) {
			mapp->map[0][j] = (mapp->numberPlayer + 2);
		}
	}
}

void movement(bool flag) {

	int rightwardMove, leftwardMove;


	if (!flag) {
		if (countOf(mapp->numberPlayer + 2 + 30) != 0) {
			movementOfQueen();
			return;
		}
		if (true) {
			if (y > 0) {
				if (x > 0 && x < 7) {
					if (mapp->map[y - 1][x - 1] == 0) mapp->map[y - 1][x - 1] = 55;
					if (mapp->map[y - 1][x + 1] == 0) mapp->map[y - 1][x + 1] = 55;
					if (x > 1 && x < 6 && y > 1) {
						if (pawnCheck(mapp->map[y - 1][x + 1]))
						{
							if (mapp->map[y - 2][x + 2] == 0) mapp->map[y - 2][x + 2] = 55;
						}
						if (pawnCheck(mapp->map[y - 1][x - 1]))
						{
							if (mapp->map[y - 2][x - 2] == 0) mapp->map[y - 2][x - 2] = 55;
						}
					}
					if (x - 2 >= 0 && y - 2 >= 0) {
						if (mapp->map[y - 2][x - 2] == 0) {
							if (pawnCheck(mapp->map[y - 1][x - 1])) mapp->map[y - 2][x - 2] = 55;
						}
					}
					if (x + 2 <= 7 && y - 2 >= 0) {
						if (mapp->map[y - 2][x + 2] == 0) {
							if (pawnCheck(mapp->map[y - 1][x + 1])) mapp->map[y - 2][x + 2] = 55;
						}
					}
					//if (x - 2 >= 0 && y - 2 >= 0 && mapp->map[y - 2][x - 2] == 0) mapp->map[y - 2][x + 2] = 55;

					

				}
				if (x > 0 && y - 1 >= 0) {
					if (mapp->map[y - 1][x - 1] == 0) mapp->map[y - 1][x - 1] = 55;
					if (x > 1 && y - 1 >= 0) {
						if ((mapp->map[y - 1][x - 1] != 0 && mapp->map[y - 1][x - 1] != 55) && mapp->map[y - 2][x - 2] == 0) mapp->map[y - 2][x - 2] = 55;
					}
				}
				if (x < 7 && y - 1 >= 0) {
					if (mapp->map[y - 1][x + 1] == 0) mapp->map[y - 1][x + 1] = 55;
					if (x < 6 && y - 1 >= 0) {
						if ((mapp->map[y - 1][x + 1] != 0 && mapp->map[y - 1][x + 1] != 55)&& mapp->map[y - 2][x + 2] == 0) mapp->map[y - 2][x + 2] = 55;
					}
				}
			}
			if (countOf(mapp->numberPlayer + 2 + 30) != 0) {

				if ((x > 1 && x < 6) && (y < 6)) {
					if (mapp->map[y + 2][x - 2] == 0 && mapp->map[y + 1][x - 1] != 0) mapp->map[y + 2][x - 2] = 55;
					if (mapp->map[y + 2][x + 2] == 0 && mapp->map[y + 1][x + 1] != 0) mapp->map[y + 2][x + 2] = 55;
				}
				if ((x > 0 && x < 7) && (y < 7)) {
					if (mapp->map[y + 1][x - 1] == 0) mapp->map[y + 1][x - 1] = 55;
					if (mapp->map[y + 1][x + 1] == 0) mapp->map[y + 1][x + 1] = 55;
				}

			}
		}
	}

	if (flag) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (mapp->map[i][j] == 55) mapp->map[i][j] = 0;
			}
		}
	}
}

int QueenRightChecking(bool fufka) {


	int firstX, firstY;
	int secondX, secondY;
	int kX = 0;
	int kY = 0;

	secondY = y;
	secondX = x;
	firstY = hod[0];
	firstX = hod[1];
	if (abs(secondY - firstY) != abs(secondX - firstX)) return 0;
	if (hod[0] < y && hod[1] < x) {
		kY = 1;
		kX = 1;
		firstY += 1;
		firstX += 1;
	}
	else if (hod[0] > y && hod[1] < x) {
		kY = -1;
		kX = 1;
		firstY -= 1;
		firstX += 1;
	}
	else if (hod[0] < y && hod[1] > x) {
		kY = 1;
		kX = -1;
		firstY += 1;
		firstX -= 1;
	}
	else if (hod[0] > y && hod[1] > x) {
		kY = -1;
		kX = -1;
		firstY -= 1;
		firstX -= 1;
	}
	//int i = firstX + 1;
	//int j = firstY + 1;
	/*if (fufka) {
		secondX += kX;
		secondY += kY;
	}*/
	/*for (int i = firstX; i < secondX - 1; i += kX) {
		for (int j = firstY; j < secondY - 1; j += kY) {
			if (mapp->map[j][i] != 0 && !fufka) return 0;
			if (fufka && mapp->map[j][i] != 0) {
				countOfKushats++;
				kushats[countOfKushats][0] = j;
				kushats[countOfKushats][1] = i;
				
			}
		}
	}*/
	int i = firstX;
	int j = firstY;
	int count = 0;
	while ((i < secondX && kX == 1) || (i > secondX && kX == -1)) {
		if (mapp->map[j][i] != 0 && !fufka) {
			count++;
		}
		if (fufka && mapp->map[j][i] != 0) {
			countOfKushats++;
			kushats[countOfKushats][0] = j;
			kushats[countOfKushats][1] = i;

		}
		i += kX;
		j += kY;
		//if (i > 7) return 0;
	}
	return count;
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

		if (x + kX < 8 && y + kY < 8 && XY != 2)
		{
			if (mapp->map[y + kY][x + kX] == 0 && XY != 2)
			{
				mapp->map[y + kY][x + kX] = 55;
				/*if (x + kX < 7 && y + kY < 7)
				{
					if (mapp->map[y + kY + 1][x + kX + 1] != 0) XY++;
				}*/

			}
			//else if (pawnCheck(mapp->map[y + kY][x + kX])) XY++;
			else if (mapp->map[y + kY][x + kX] != 0 && XY < 1) XY++;
			else if (mapp->map[y + kY][x + kX] != 0 && XY == 1) XY = 2;
			flagXY = false;
		}
		if (x + kX < 8 && y - kY >= 0 && Xy != 2)
		{
			if (mapp->map[y - kY][x + kX] == 0 && Xy != 2)
			{
				mapp->map[y - kY][x + kX] = 55;
				/*if (x + kX < 7 && y - kY >= 1)
				{
					if (mapp->map[y - kY - 1][x + kX + 1] != 0) Xy++;
				}*/

			}
			else if (mapp->map[y - kY][x + kX] != 0 && Xy < 1) Xy++;
			else if (mapp->map[y - kY][x + kX] != 0 && Xy == 1) Xy = 2;
			//else if (pawnCheck(mapp->map[y - kY][x + kX])) Xy++;
			flagXy = false;
		}
		if (x - kX >= 0 && y + kY < 8 && xY != 2)
		{
			if (mapp->map[y + kY][x - kX] == 0 && xY != 2)
			{
				mapp->map[y + kY][x - kX] = 55;
				/*if (x - kX >= 1 && y + kY < 7)
				{
					if (mapp->map[y + kY + 1][x - kX - 1] != 0) xY++;
				}*/

			}
			//else if (pawnCheck(mapp->map[y + kY][x - kX])) xY++;
			else if (mapp->map[y + kY][x - kX] != 0 && xY < 1) xY++;
			else if (mapp->map[y + kY][x - kX] != 0 && xY == 1) xY = 2;
			
			flagxY = false;
		}
		if (x - kX >= 0 && y - kY >= 0 && xy != 2)
		{
			if (mapp->map[y - kY][x - kX] == 0 && xy != 2)
			{
				mapp->map[y - kY][x - kX] = 55;
				/*if (x - kX >= 1 && y - kY >= 1)
				{
					if (mapp->map[y - kY - 1][x - kX - 1] != 0) xy++;
				}*/


			}
			else if (mapp->map[y - kY][x - kX] != 0 && xY < 1) xy++;
			else if (mapp->map[y - kY][x - kX] != 0 && xY == 1) xy = 2;
			//else if (pawnCheck(mapp->map[y - kY][x - kX])) xy++;
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
		if (mapp->map[hod[0] + ky][hod[1] + kx] != 55)
		{
			mapp->map[hod[0] + ky][hod[1] + kx] = 0;
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
			if (mapp->map[i][j] == 44) mapp->map[i][j] = 0;
			if (mapp->map[i][j] >= 30 && mapp->map[i][j] <= 34) {
				mapp->map[i][j] %= 30;
			}
		}
	}
}
void kushatts() {
	for (int i = 0; i <= countOfKushats; i++) {
		mapp->map[kushats[i][0]][kushats[i][1]] = 0;
	}
}

// уничтожение шашок
void minusChecker(bool flag) {


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (mapp->map[i][j] == 44) mapp->map[i][j] = 0;
			/*if (mapp->map[i][j] == 33) {
				if (mapp->numberPlayer == 1) NumberOfFallenBlackCheckers++;
				else NumberOfFallenWhiteCheckers++;
				mapp->map[i][j] = 0;
			}*/
			if (flag && (mapp->map[i][j] == (mapp->numberPlayer + 30) || mapp->map[i][j] == (mapp->numberPlayer + 30 + 2))) {

				mapp->map[y][x] = (mapp->map[i][j] % 30);
				mapp->map[i][j] = 0;
				flag = false;
			}
		}
	}
	endOfGame();
}


// подсчитывание кол-во выбранных шашок текущего игрока
int countOf(int number) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (mapp->map[i][j] == number) count++;
		}
	}
	return count;
}


// проверка на доступность хода
bool poedanie() {

	int Ykletka_of_enemy = abs(y + hod[0]) / 2;
	int Xkletka_of_enemy = abs(x + hod[1]) / 2;
	location_of_enemy = &mapp->map[Ykletka_of_enemy][Xkletka_of_enemy];
	bool flaag = true;
	bool flaggg = false;
	bool fllag = false;
	if ((countOf(31) == 1 || countOf(32) == 1)) {
		if (((y + hod[0]) % 2 == 0) && ((x + hod[1]) % 2 == 0)) fllag = true;
		else fllag = false;
	}
	else if (countOf(33) == 1 || countOf(34) == 1) fllag = true;
	else fllag = false;
	if (countOf(mapp->numberPlayer + 30 + 2) == 1) {
		if (QueenRightChecking(false) == 1) flaggg = true;
		else flaggg = false;
	}
	else {
		if (*location_of_enemy != 0) flaggg = true;
		else flaggg = false;
	}
	if (((x % 2 == 0 && y % 2 == 1) || (x % 2 == 1 && y % 2 == 0)) && (mapp->map[y][x] == 0) && flaggg && fllag){
		if (countOf(31) == 1 || countOf(32) == 1 || countOf(33) == 1 || countOf(34) == 1) {
			if (countOfKushats == 0) {
				if (y <= hod[0]) flaag = true;
			}
			else flaag = false;
			if (flag)
			{
				if (countOf(mapp->numberPlayer + 30 + 2) != 0) QueenRightChecking(true);
				else {
					countOfKushats++;
					kushats[countOfKushats][0] = Ykletka_of_enemy;
					kushats[countOfKushats][1] = Xkletka_of_enemy;
				}
			}
		}
		return true;
	}
	return false;

}



// действия при нажитии левой кнопки мыши
void leftClickingForTheSecondWindow(HDC hdc, LPARAM lParam, HWND hWnd) {

	int* currentCell = &mapp->map[y][x];

	if ((countOf(mapp->numberPlayer + 30) == 0 && (*currentCell == mapp->numberPlayer) && (countOf(mapp->numberPlayer + 30 + 2) == 0)) ||
		(countOf(mapp->numberPlayer + 30 + 2) == 0 && (*currentCell == (mapp->numberPlayer + 2)) && countOf(mapp->numberPlayer + 30) == 0)){
		*currentCell += 30;
		movement(false);
	}
	else if ((countOf(mapp->numberPlayer + 30) == 1 && (*currentCell == mapp->numberPlayer || (*currentCell == (mapp->numberPlayer + 2)))) ||
			((countOf(mapp->numberPlayer + 30 + 2) == 1 && ((*currentCell == (mapp->numberPlayer + 2) || (*currentCell == (mapp->numberPlayer))))))) {
			moveCancellation();
			*currentCell += 30;
			mapp->map[hod[0]][hod[1]] %= 30;
			//moveCancellation();
			movement(true);
			movement(false);
			
	}
	else if ((countOf(mapp->numberPlayer + 30) == 1 || countOf(mapp->numberPlayer + 30 + 2) == 1) && *currentCell == 44 && y == hod[0] && x == hod[1]) {
		minusChecker(true);
		Queen();
		if (mapp->numberPlayer == 1) mapp->numberPlayer = 2;
		else mapp->numberPlayer = 1;

		kushatts();
		mapp->numberOfBlackCheckers = countOfCheckers(2);
		mapp->numberOfWhiteCheckers = countOfCheckers(1);
		int end = endOfGame();
		if (end == 1 || end == 2) {
			//addRecord(str1);
			//addRecord(str2);
			return;
		}
		else Turning_the_board(hWnd);
		/*else {
			statusOfGame = 1;
			window = 3;
		}*/
		movement(true);
	}
	else if (*currentCell == 55) {
		//mapp->map[y][x] = (mapp->numberPlayer % 30);
		mapp->map[y][x] = mapp->map[hod[0]][hod[1]] % 30;
		mapp->map[hod[0]][hod[1]] = 0;
		QueenWannaEat();
		//if (mapp->map[y][x] % 30 == 3 || mapp->map[y][x] == 4) {
		//	//QueenWannaEat();
		//}
		int ySr = (y + hod[0]);
		int xSr = (x + hod[1]);
		if (ySr % 2 == 0 && xSr % 2 == 0)
		{
			if (mapp->map[ySr / 2][xSr / 2] == 1 || mapp->map[ySr / 2][xSr / 2] == 2) mapp->map[ySr / 2][xSr / 2] = 0;
		}

		movement(true);
		Queen();
		if (mapp->numberPlayer == 1) mapp->numberPlayer = 2;
		else mapp->numberPlayer = 1;
		mapp->numberOfBlackCheckers = countOfCheckers(2);
		mapp->numberOfWhiteCheckers = countOfCheckers(1);
		int end = endOfGame();
		if(end == 1 || end == 2) {
			//addRecord(str1);
			//addRecord(str2);
			return;
		}Turning_the_board(hWnd);
	}
	else
	{
		//mapp->map[hod[0]][hod[1]] %= 30;
		moveCancellation();
		movement(true);
	}


	//if (y == 0) *currentCell += 963;
	Queen();
}

// первое окно
void FirstWindow(HDC hdc, HWND hWnd, HINSTANCE hInst) {

	TCHAR  string3[] = _T("Checkers");
	TCHAR  string4[] = _T("Scoreboard");
	TCHAR  string5[] = _T("Exit");
	TCHAR  string6[] = _T("Start the game");
	HFONT hFont;

	hFont = CreateFont(100,
		0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Courier New"
	);

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 0));

	TextOut(hdc, 210, 200, (LPCWSTR)string3, _tcslen(string3));
	DeleteObject(hFont);

	Rectangle(hdc, 310 + 5 - 10, 250 + 40 + 60, 490 + 5 - 10 + 25, 250 + 40 + 30 + 70);
	Rectangle(hdc, 310 + 5 - 10, 250 + 2 * 40 + 30 + 60, 490 + 5 - 10 + 25, 250 + 2 * 40 + 2 * 30 + 70);
	Rectangle(hdc, 310 + 5 - 10, 250 + 3 * 40 + 2 * 30 + 60, 490 + 5 - 10 + 25, 250 + 3 * 40 + 3 * 30 + 70);

	hFont = CreateFont(25,
		0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Courier New"
	);

	SelectObject(hdc, hFont);

	TextOut(hdc, 325 - 15, 250 + 40 + 60 + 5, (LPCWSTR)string6, _tcslen(string6));
	TextOut(hdc, 325 + 8, 250 + 2 * 40 + 60 + 15 + 20, (LPCWSTR)string4, _tcslen(string4));
	TextOut(hdc, 325 + 18 * 3 - 2, 250 + 3 * 40 + 2 * 60 + 5, (LPCWSTR)string5, _tcslen(string5));

	//TextOut(hdc, 325, 250 + 2 * 40 + 60 + 15 + 20, (LPCWSTR)string4, _tcslen(string4));
	//TextOut(hdc, 325 + 18 * 3, 250 + 3 * 40 + 2 * 60 + 5, (LPCWSTR)string5, _tcslen(string5));
	DeleteObject(hFont);
	//if (registration == 1) RegistrationOfPlayer(hWnd, hInst);
}


// действия при нажитии второй кнопки мыши
void rightClickingForTheSecondWindow(HDC hdc, LPARAM lParam) {
	if (hod[0] == y && hod[1] == x) {
		moveCancellation();
		movement(true);
		return;
	}
	if ((countOf(mapp->numberPlayer + 30) == 1 || countOf(mapp->numberPlayer + 30 + 2) == 1) && poedanie()) {
		mapp->map[y][x] = 44;
		//*location_of_enemy = 33;
	}
	else {
		//mapp->map[hod[0]][hod[1]] %= 30;
		moveCancellation();
		movement(true);
		return;
	}
}

// отрисовка шашок
void shading_the_checkers(HDC hdc, int j, int i) {

	HBRUSH cell_first_player, cell_second_player, H_selected_cells, white_cage, black_cage;

	//cell_second_player = CreateSolidBrush(RGB(33, 33, 33)); // цвет шашки первого игрока
	//cell_first_player = CreateSolidBrush(RGB(231, 231, 231)); // цвет шашки второго игрока
	//H_selected_cells = CreateSolidBrush(RGB(205, 133, 63)); // цвет оконтовки шашки при многократном ходе
	////RGB(15, 46, 66)
	//white_cage = CreateSolidBrush(RGB(231, 187, 154));
	//black_cage = CreateSolidBrush(RGB(126, 56, 3));


	HPEN stroke_first_player_cell, stroke_second_player_cell, selected_cells, green_cell, strokeCell, eatenUp;

	//strokeCell = CreatePen(PS_SOLID, 8, RGB(254, 194, 57));
	//eatenUp = CreatePen(PS_SOLID, 8, RGB(255, 69, 34));
	//selected_cells = CreatePen(PS_SOLID, 8, RGB(205, 133, 63)); // цвет шашки при многократном ходе
	//green_cell = CreatePen(PS_SOLID, 8, RGB(0, 255, 0)); // цвет выделенной ячейки
	//stroke_second_player_cell = CreatePen(PS_SOLID, 8, RGB(0, 0, 0)); // цвет оконтовки шашки второго игрока
	//stroke_first_player_cell = CreatePen(PS_SOLID, 8, RGB(255, 255, 255)); // цвет оконтовки шашки первого игрока


	int cx = (i + 1) * 100 - 50;
	int cy = (j + 1) * 100 - 50;

	if (mapp->map[j][i] == 2) { // закрашивание шашки второго игрока
		stroke_second_player_cell = CreatePen(PS_SOLID, 8, RGB(0, 0, 0)); // цвет оконтовки шашки второго игрока
		cell_second_player = CreateSolidBrush(RGB(33, 33, 33)); // цвет шашки первого игрока
		SelectObject(hdc, stroke_second_player_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		DeleteObject(stroke_second_player_cell);
		DeleteObject(cell_second_player);
	}

	if (mapp->map[j][i] == 4) {
		stroke_second_player_cell = CreatePen(PS_SOLID, 8, RGB(0, 0, 0)); // цвет оконтовки шашки второго игрока
		cell_second_player = CreateSolidBrush(RGB(33, 33, 33)); // цвет шашки первого игрока
		SelectObject(hdc, stroke_second_player_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		Сrown(hdc, cx, cy, 20, 20, RGB(255, 255, 255));
		DeleteObject(stroke_second_player_cell);
		DeleteObject(cell_second_player);
	}

	else if (mapp->map[j][i] == 1) {  // закрашивание шашки первого игрока
		cell_first_player = CreateSolidBrush(RGB(231, 231, 231)); // цвет шашки второго игрока
		stroke_first_player_cell = CreatePen(PS_SOLID, 8, RGB(255, 255, 255)); // цвет оконтовки шашки первого игрока
		SelectObject(hdc, stroke_first_player_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		DeleteObject(stroke_first_player_cell);
		DeleteObject(cell_first_player);
	}

	else if (mapp->map[j][i] == 3) {
		cell_first_player = CreateSolidBrush(RGB(231, 231, 231)); // цвет шашки второго игрока
		stroke_first_player_cell = CreatePen(PS_SOLID, 8, RGB(255, 255, 255)); // цвет оконтовки шашки первого игрока
		SelectObject(hdc, stroke_first_player_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		Сrown(hdc, cx, cy, 20, 20, RGB(0, 0, 0));
		DeleteObject(stroke_first_player_cell);
		DeleteObject(cell_first_player);
	}

	if (mapp->map[j][i] == 31) { // закрашивание выделенной шашки первого игрока
		green_cell = CreatePen(PS_SOLID, 8, RGB(0, 255, 0)); // цвет выделенной ячейки
		cell_first_player = CreateSolidBrush(RGB(231, 231, 231)); // цвет шашки второго игрока
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		DeleteObject(green_cell);
		DeleteObject(cell_first_player);
	}
	if (mapp->map[j][i] == 33) {
		green_cell = CreatePen(PS_SOLID, 8, RGB(0, 255, 0)); // цвет выделенной ячейки
		cell_first_player = CreateSolidBrush(RGB(231, 231, 231)); // цвет шашки второго игрока
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_first_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		Сrown(hdc, cx, cy, 20, 20, RGB(0, 0, 0));
		DeleteObject(green_cell);
		DeleteObject(cell_first_player);
	}
	else if (mapp->map[j][i] == 32) {  // закрашивание выделенной шашки второго игрока
		green_cell = CreatePen(PS_SOLID, 8, RGB(0, 255, 0)); // цвет выделенной ячейки
		cell_second_player = CreateSolidBrush(RGB(33, 33, 33)); // цвет шашки первого игрока
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		DeleteObject(green_cell);
		DeleteObject(cell_second_player);
	}
	else if (mapp->map[j][i] == 34) {
		green_cell = CreatePen(PS_SOLID, 8, RGB(0, 255, 0)); // цвет выделенной ячейки
		cell_second_player = CreateSolidBrush(RGB(33, 33, 33)); // цвет шашки первого игрока
		SelectObject(hdc, green_cell);
		SelectObject(hdc, cell_second_player);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		Сrown(hdc, cx, cy, 20, 20, RGB(255, 255, 255));
		DeleteObject(green_cell);
		DeleteObject(cell_second_player);
	}
	if (mapp->map[j][i] == 44) { // закрашивание шашки при многократном ходе
		H_selected_cells = CreateSolidBrush(RGB(205, 133, 63)); // цвет оконтовки шашки при многократном ходе
		selected_cells = CreatePen(PS_SOLID, 8, RGB(205, 133, 63)); // цвет шашки при многократном ходе
		SelectObject(hdc, selected_cells);
		SelectObject(hdc, H_selected_cells);

		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
		DeleteObject(selected_cells);
		DeleteObject(H_selected_cells);
	}
	if (mapp->map[j][i] == 55) {
		strokeCell = CreatePen(PS_SOLID, 8, RGB(254, 194, 57));
		black_cage = CreateSolidBrush(RGB(126, 56, 3));
		SelectObject(hdc, strokeCell);
		SelectObject(hdc, black_cage);
		Rectangle(hdc, cx - 46, cy - 46, cx + 48, cy + 48);
		DeleteObject(strokeCell);
		DeleteObject(black_cage);
	}
	/*else if (mapp->map[j][i] == 33) {
		SelectObject(hdc, eatenUp);
		if (mapp->numberPlayer == 1) SelectObject(hdc, cell_second_player);
		else SelectObject(hdc, cell_first_player);
		Ellipse(hdc, cx - 40, cy - 40, cx + 40, cy + 40);
	}*/

	/*DeleteObject(cell_first_player);
	DeleteObject(cell_second_player);
	DeleteObject(H_selected_cells);
	DeleteObject(selected_cells);
	DeleteObject(green_cell);
	DeleteObject(stroke_first_player_cell);
	DeleteObject(stroke_second_player_cell);
	DeleteObject(strokeCell);
	DeleteObject(white_cage);
	DeleteObject(black_cage);*/
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
	DeleteObject(H_black_cage);
	DeleteObject(black_cage);
	DeleteObject(white_cage);
	DeleteObject(H_white_cage);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			shading_the_checkers(hdc, i, j);

		}
	}

	/*DeleteObject(H_black_cage);
	DeleteObject(black_cage);
	DeleteObject(white_cage);
	DeleteObject(H_white_cage);*/

	//HFONT hFont;
	//hFont = CreateFont(20,
	//	0, 0, 0, 0, 0, 0, 0,
	//	DEFAULT_CHARSET,
	//	0, 0, 0, 0,
	//	L"Courier New"
	//);
	//SelectObject(hdc, hFont);
	//SetTextColor(hdc, RGB(0, 128, 128));

	//TCHAR  string1[] = _T("Потеряно белых шашек: ");
	//TCHAR  string2[] = _T("Потеряно черных шашек: ");
	//TextOut(hdc, 900, 50, (LPCWSTR)string1, _tcslen(string1));
	//TextOut(hdc, 900, 70, (LPCWSTR)string2, _tcslen(string2));
	//char nNumberOfFallenWhiteCheckers[5];
	//TCHAR  tNumberOfFallenWhiteCheckers[5];
	//sprintf(nNumberOfFallenWhiteCheckers, "%d", NumberOfFallenWhiteCheckers);
	//OemToChar(nNumberOfFallenWhiteCheckers, tNumberOfFallenWhiteCheckers);
	//TextOut(hdc, 1115, 50, (LPCWSTR)tNumberOfFallenWhiteCheckers, _tcslen(tNumberOfFallenWhiteCheckers));


	//char nNumberOfFallenBlackCheckers[5];
	//TCHAR  tNumberOfFallenBlackCheckers[5];
	//sprintf(nNumberOfFallenBlackCheckers, "%d", NumberOfFallenBlackCheckers);
	//OemToChar(nNumberOfFallenBlackCheckers, tNumberOfFallenBlackCheckers);
	//TextOut(hdc, 1125, 70, (LPCWSTR)tNumberOfFallenBlackCheckers, _tcslen(tNumberOfFallenBlackCheckers));

	//int xxx = countOf(1) + countOf(31);
	//TCHAR string3[] = _T("Игрок, который сейчас ходит: ");
	//TextOut(hdc, 900, 90, (LPCWSTR)string3, _tcslen(string3));
	//char nnumberPlayer[5];
	//TCHAR  tnumberPlayer[5];
	//sprintf(nnumberPlayer, "%d", mapp->numberPlayer);
	//OemToChar(nnumberPlayer, tnumberPlayer);
	//TextOut(hdc, 1185, 90, (LPCWSTR)tnumberPlayer, _tcslen(tnumberPlayer));


	//mapp->numberOfWhiteCheckers = countOf(1) + countOf(31) + countOf(33) + countOf(3);
	//mapp->numberOfBlackCheckers = countOf(2) + countOf(32) + countOf(34) + countOf(4);
	//TCHAR string4[] = _T("Кол-во белых шашек: ");
	//TextOut(hdc, 900, 110, (LPCWSTR)string4, _tcslen(string4));
	////char nnumberPlayer[5];
	////TCHAR  tnumberPlayer[5];
	//sprintf(nnumberPlayer, "%d", mapp->numberOfWhiteCheckers);
	//OemToChar(nnumberPlayer, tnumberPlayer);
	//TextOut(hdc, 1095, 110, (LPCWSTR)tnumberPlayer, _tcslen(tnumberPlayer));


	//TCHAR string5[] = _T("Кол-во черных шашек: ");
	//TextOut(hdc, 900, 130, (LPCWSTR)string5, _tcslen(string5));
	////char nnumberPlayer[5];
	////TCHAR  tnumberPlayer[5];
	//sprintf(nnumberPlayer, "%d", mapp->numberOfBlackCheckers);
	//OemToChar(nnumberPlayer, tnumberPlayer);
	//TextOut(hdc, 1105, 130, (LPCWSTR)tnumberPlayer, _tcslen(tnumberPlayer));
	/*if (window_menu == 1) mini_menu(hdc);*/
	/*Rectangle(hdc, 770, 0, 800, 20);
	HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hpen);
	Ellipse(hdc, 770 + 7 - 2, 7, 770 + 7 + 6 - 2, 7 + 6);
	Ellipse(hdc, 770 + 14 - 2, 7, 770 + 14 + 6 - 2, 7 + 6);
	Ellipse(hdc, 770 + 21 - 2, 7, 770 + 21 + 6 - 2, 7 + 6);
	if (window_menu == 1) mini_menu(hdc);*/
	//DeleteObject(hFont);
};

// переворот доски
void Turning_the_board(HWND hWnd) {
	int end = 7;
	int x;
	for (int begin = 0; begin < 8; begin++) {
		for (int j = 0; j < 8; j++) {
			x = mapp->map[begin][j];
			mapp->map[begin][j] = mapp->map[end][7 - j];
			mapp->map[end][7 - j] = x;
		}
		end--;
		if (begin == end) {
			break;
		}

	}
	KillTimer(hWnd, 2);
	//SetTimer(hWnd, 2, 1000, 0);
	timerDigit = 30;
};

// конец игры
int endOfGame() {
	if (mapp->numberOfBlackCheckers == 0) {
		window = 1;
		statusOfGame = 1;
		InsertRecord(str1, true, 0);
		//InsertRecord(str2, true);
		return 1;
	}
	else if (mapp->numberOfWhiteCheckers == 0) {
		statusOfGame = 1;
		window = 1;
		InsertRecord(str2, true, 0);
		//InsertRecord(str1, true);
		return 2;
	}
	else return 0;
}





int CompareRecords(int index1, int index2)
{
	if (records[index1].winCount < records[index2].winCount)
		return -1;
	if (records[index1].winCount > records[index2].winCount)
		return +1;

	// if (records[index1].gold == records[index2].gold) {

	if (records[index1].lossCount > records[index2].lossCount)
		return -1;
	if (records[index1].lossCount < records[index2].lossCount)
		return +1;

	//   if (records[index1].steps == records[index2].steps) {
	return 0;
	//    } 
	//  }

}


int contains(int n, char name[]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(records[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

int number[2];

void InsertRecord(char name[], bool flag, int temp)
{
	if (strcmp(name, "Player 1") == 0) {
		strcpy(str1, "Noname1");
	}
	else if (strcmp(name, "Player 2") == 0) {
		strcpy(str2, "Noname2");
	}
	int xX = contains(numRecords, name);
	if (!flag) {
		
		if (xX == -1)
		{
			if (strcmp(name, "Player 1") == 0) {
				strcpy(records[numRecords].name, "Noname1");
			}
			else if (strcmp(name, "Player 2") == 0) {
				strcpy(records[numRecords].name, "Noname2");
			}
			else strcpy(records[numRecords].name, name);
			//number[numRecords % 2] = numRecords;
			records[numRecords].winCount = 0;
			records[numRecords].lossCount = 0;
			records[numRecords].numberOfMovesPlayer = 0;

		}
		//else numRecords = x;
		SYSTEMTIME st;
		// Получаем текущее время
		GetLocalTime(&st);

		// и разбрасываем его по полям в таблицу рекордов
		records[numRecords].year = st.wYear;
		records[numRecords].month = st.wMonth;
		records[numRecords].day = st.wDay;

		records[numRecords].hour = st.wHour;
		records[numRecords].minute = st.wMinute;
		records[numRecords].second = st.wSecond;

		// Продвигаем запись к началу массива - если в ней 
		// хороший результат
		if (numRecords < MAX_NUM_RECORDS && xX == -1)
			// следующий раз новый рекорд будет занесен в новый элемент
			numRecords++;
	}
	else {
		if (mapp->numberOfBlackCheckers == 0) {
			records[contains(numRecords, str1)].winCount += 1;
			records[contains(numRecords, str2)].lossCount += 1;
		}
		else if (mapp->numberOfWhiteCheckers == 0) {
			records[contains(numRecords, str2)].winCount += 1;
			records[contains(numRecords, str1)].lossCount += 1;
		}
		else if (temp == 1) {
			if (mapp->numberPlayer == 1) {
				records[contains(numRecords, str2)].winCount += 1;
				records[contains(numRecords, str1)].lossCount += 1;
			}
			else if (mapp->numberPlayer == 2) {
				records[contains(numRecords, str1)].winCount += 1;
				records[contains(numRecords, str2)].lossCount += 1;
			}
		}
		int i = numRecords - 1;
		while (i > 0) {
			if (CompareRecords(i - 1, i) < 0) {
				struct Record temp = records[i];
				records[i] = records[i - 1];
				records[i - 1] = temp;
			}
			i--;
		}
		// Если таблица заполнена не полностью
		//if (numRecords < MAX_NUM_RECORDS && xX == -1)
		//	// следующий раз новый рекорд будет занесен в новый элемент
		//	numRecords++;
	}
}


void DrawRecords(HDC hdc) {
	HFONT hFont;
	hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0, 0,
		L"Courier New"
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 64, 64));

	TCHAR  string1[] = _T("! No ! Дата       ! Время    ! Имя                  ! Победы ! Поражения !");
	TextOut(hdc, 10, 50, (LPCWSTR)string1, _tcslen(string1));

	int i;
	for (i = 0; i < numRecords; i++) {
		TCHAR  string2[200];
		char str[200];
		sprintf(str, "! %2d ! %02d.%02d.%04d ! %02d:%02d:%02d ! %-20s ! %4d   !%5d !",
			i + 1,
			records[i].day, records[i].month, records[i].year,
			records[i].hour, records[i].minute, records[i].second,
			records[i].name, records[i].winCount, records[i].lossCount
		);
		OemToChar(str, string2);
		TextOut(hdc, 10, 24 * (i + 1) + 50, (LPCWSTR)string2, _tcslen(string2));
	}
	DeleteObject(hFont);
}

int massivTimer[31] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
						1 + 10, 2 + 10, 3 + 10, 4 + 10, 5 + 10, 6 + 10, 7 + 10, 8 + 10, 9 + 10, 10 + 10,
						1 + 20, 2 + 20, 3 + 20, 4 + 20, 5 + 20, 6 + 20, 7 + 20, 8 + 20, 9 + 20, 10 + 20, 31
};

void Timer() {
	static int time = TIME;

}



//char filenameRecords[] = "records.txt";

void SaveRecords() {
	// Запись в выходной файл
	FILE* fout = fopen("records.txt", "wt");
	if (fout == NULL) {
		// выходим, не сохранив результаты в файл
		return;
	}

	fprintf(fout, "%d\n", numRecords);

	int i;
	for (i = 0; i < numRecords; i++) {
		// сохраняем в файле каждое поле каждого рекорда
		fprintf(fout, "%s %d %d %d %d %d %d %d %d\n",
			records[i].name,
			records[i].winCount,
			records[i].lossCount,
			records[i].year,
			records[i].month,
			records[i].day,
			records[i].hour,
			records[i].minute,
			records[i].second
		);

	}

	// закрываем файл
	fclose(fout);
}

void LoadRecords() {
	// Открываем файл с рекордами на чтение
	FILE* fout = fopen("records.txt", "rt");
	if (fout == NULL) {
		// выходим, не загрузив рекорды из файла
		return;
	}

	fscanf(fout, "%d", &numRecords); // количество рекордов в таблице

	int i;
	for (i = 0; i < numRecords; i++) {
		// загружаем из файла каждое поле каждого рекорда
		fscanf(fout, "%s%d%d%d%d%d%d%d%d\n",
			records[i].name,
			&records[i].winCount,
			&records[i].lossCount,
			&records[i].year,
			&records[i].month,
			&records[i].day,
			&records[i].hour,
			&records[i].minute,
			&records[i].second
		);

	}
	// закрываем файл
	fclose(fout);
}
