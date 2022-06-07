#pragma once

void mySetColor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}

void fillTable() {
	t.pixels = new Pixel * [10];
	for (size_t i = 0; i < 10; i++)
	{
		t.pixels[i] = new Pixel[10]{};
	}
}

void showTable() {
	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if (i == 0 || i == 11 || j == 0 || j == 11)
			{
				cout << (char)254u << ' ';
			}
			else
			{
				if (t.pixels[i - 1][j - 1].element != ' ')
				{
					mySetColor(1, 0);
					if (t.pixels[i - 1][j - 1].isPlaced == false) mySetColor(12, 0);
				}
				cout << t.pixels[i - 1][j - 1].element << ' ';
				mySetColor(15, 0);
			}
		}

		if (i == 4) cout << "   Lines";
		if (i == 5) cout << "   " << lines;
		cout << endl;
	}
}

void youWin(bool win) {
	gameMode = 2;
	//system("cls");
	cout << endl;
	cout << "\t############################\n";
	if (win) {
		cout << "\t#\tYOU WIN\t#\n";
	}
	else {
		cout << "\t#\tYOU LOSE\t#\n";
	}
	cout << "\t#\tLines : " << lines << "\t#\n";
	cout << "\t############################\n";
	while (true) { _getch(); }
	//exit(0);
}

void setCursor(bool visible) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void screen() {
	while (true) {
		system("cls");
		if (gameMode != 1) break;
		showTable();
		if (lines != 0 && lines % 10 == 0) waiting = waiting - 50;
		//Sleep(1);
	}
}

void fallDown(int h) {
	for (int i = h; i >= 1; i--)
	{
		for (int j = 9; j >= 0; j--)
		{
			t.pixels[i][j].element = t.pixels[i - 1][j].element;
			t.pixels[i][j].isPlaced = t.pixels[i - 1][j].isPlaced;
		}
	}
	lines++;
}

void clearFlatAreas() {
	bool isFlat;
	for (int i = 9; i >= 0; i--)
	{
		isFlat = true;
		for (int j = 9; j >= 0; j--)
		{
			if (t.pixels[i][j].element == ' ') isFlat = false;
		}
		if (isFlat)
		{

			for (int j = 9; j >= 0; j--)
			{
				Sleep(20);
				t.pixels[i][j].element = ' ';
				t.pixels[i][j].isPlaced = false;
			}

			Sleep(500);
			fallDown(i);
			i++;
		}
	}
}

short trys = 0;
void randomBlock() {
	if (trys == 5) youWin(false);

	short randY = rand() % 10;

	if (t.pixels[0][randY].element == ' ')
	{
		centerX = 0;
		centerY = randY;
		t.pixels[centerX][centerY].element = (char)254u;
		trys = 0;
	}
	else {
		trys++;
		randomBlock();
	}
	trys = 0;
}

void placeAll() {
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (t.pixels[i][j].isPlaced == false && t.pixels[i][j].element != ' ') {
				t.pixels[i][j].isPlaced = true;
			}
		}
	}
}

bool canGoDown() {
	for (int i = 9; i >= 0; i--)
	{
		for (int j = 9; j >= 0; j--)
		{
			if (t.pixels[i][j].isPlaced == true) {
				if (t.pixels[i - 1][j].element != ' ' && t.pixels[i - 1][j].isPlaced == false) {
					return false;
				}
			}
			if (t.pixels[i][j].element != ' ' && t.pixels[i][j].isPlaced == false && i + 1 == 10) return false;
		}
	}
	return true;
}

bool canGoRight() {
	for (int i = 9; i >= 0; i--)
	{
		for (int j = 9; j >= 0; j--)
		{
			if (t.pixels[i][j].isPlaced == false && t.pixels[i][j].element != ' ') {
				if (j == 9 || t.pixels[i][j + 1].isPlaced == true) {
					return false;
				}
			}
		}
	}
	return true;
}

bool canGoLeft() {
	for (int i = 9; i >= 0; i--)
	{
		for (int j = 9; j >= 0; j--)
		{
			if (t.pixels[i][j].isPlaced == false && t.pixels[i][j].element != ' ') {
				if (j == 0 || t.pixels[i][j - 1].isPlaced == true) {
					return false;
				}
			}
		}
	}
	return true;
}

void goDown() {
	srand(time(0));
	bool isEverthingPlaced = false;
	//bool shouldPlaceAll = false;
	while (true) {
		if (gameMode != 1) break;
		isEverthingPlaced = true;
		//shouldPlaceAll = false;
		if (!canGoDown()) {
			placeAll();
		}
		for (int i = 9; i >= 0; i--)
		{
			for (int j = 9; j >= 0; j--)
			{
				if (t.pixels[i][j].element != ' ' && t.pixels[i][j].isPlaced == false) {
					if (i + 1 != 10 && t.pixels[i + 1][j].isPlaced == false) {
						t.pixels[i + 1][j].element = (char)254u;
						t.pixels[i][j].element = ' ';
						isEverthingPlaced = false;
						//if (t.pixels[i + 2][j].isPlaced) shouldPlaceAll = true;
						//updatePixel(j, i + 1, (char)254u, 12);
						//updatePixel(j, i, ' ', 15);
					}
					else {
						placeAll();
						break;
						//updatePixel(j, i, (char)254u, 1);
					}
				}
			}
			//if (shouldPlaceAll) break;
		}
		centerX++;
		//if (shouldPlaceAll) placeAll();
		if (isEverthingPlaced)
		{
			clearFlatAreas();
			randomBlock();
		}
		//updateScreen();
		Sleep(waiting);
	}
}

void movements() {
	while (true) {
		int number;
		while (true)
		{
			number = _getch();

			if (number == 224) {
				number = _getch();

				switch (number)
				{
				case 80: // Down
					if (!canGoDown()) {
						placeAll();
					}
					for (int i = 9; i >= 0; i--)
					{
						for (int j = 9; j >= 0; j--)
						{
							if (t.pixels[i][j].element != ' ' && t.pixels[i][j].isPlaced == false) {
								if (i + 1 != 10 && t.pixels[i + 1][j].isPlaced == false) {
									t.pixels[i + 1][j].element = (char)254u;
									t.pixels[i][j].element = ' ';
								}
								else {
									placeAll();

								}
							}
						}
					}
					centerX++;
					break;
				case 77: // Right
					if (!canGoRight()) break;
					for (int i = 9; i >= 0; i--)
					{
						for (int j = 9; j >= 0; j--)
						{
							if (t.pixels[i][j].element != ' ' && t.pixels[i][j].isPlaced == false) {
								if (j + 1 != 10 && t.pixels[i][j + 1].element == ' ') {
									t.pixels[i][j + 1].element = (char)254u;
									t.pixels[i][j].element = ' ';
								}
								else {
									break;
								}
							}
						}
					}
					centerY++;
					break;
				case 75: // Left
					if (!canGoLeft()) break;
					for (int i = 9; i >= 0; i--)
					{
						for (int j = 0; j < 10; j++)
						{
							if (t.pixels[i][j].element != ' ' && t.pixels[i][j].isPlaced == false) {
								if (j - 1 != -1 && t.pixels[i][j - 1].element == ' ') {
									t.pixels[i][j - 1].element = (char)254u;
									t.pixels[i][j].element = ' ';
								}
								else {
									break;
								}
							}
						}
					}
					centerY--;
					break;
				default:
					break;
				}
			}
		}
		//updateScreen();
	}
}