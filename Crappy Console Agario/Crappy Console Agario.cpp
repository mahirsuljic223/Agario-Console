// Mahir Suljic - beannshie

#include <iostream>
#include <Windows.h>

using namespace std;

int w = 50, h = 20;
int pw = 3, ph = 3;

int fps = 60;
int lat = (1 / fps) * 1000;
float spd = 1;

int score = 0;

int rnd(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}

void pieceOfShitOptimisedRNGFoodGen(int x, int y, int& fx, int& fy)
{
	switch (rand() % 4)
	{
	case 0:
		if (x > 2)
			fx = rnd(2, x);
		else if (x + pw < w - 2)
			fx = rnd(x + pw, w - 2);
		else if (y > 2)
			fy = rnd(2, y);
		else if (y + ph < h - 2)
			fy = rnd(y + ph, h - 2);
		break;
	case 1:
		if (x + pw < w - 2)
			fx = rnd(x + pw, w - 2);
		else if (x > 2)
			fx = rnd(2, x);
		else if (y + ph < h - 2)
			fy = rnd(y + ph, h - 2);
		else if (y > 2)
			fy = rnd(2, y);
		break;
	case 2:
		if (y > 2)
			fy = rnd(2, y);
		else if (y + ph < h - 2)
			fy = rnd(y + ph, h - 2);
		else if (x > 2)
			fx = rnd(2, x);
		else if (x + pw < w - 2)
			fx = rnd(x + pw, w - 2);
		break;
	case 3:
		if (y + ph < h - 2)
			fy = rnd(y + ph, h - 2);
		else if (y > 2)
			fy = rnd(2, y);
		else if (x + pw < w - 2)
			fx = rnd(x + pw, w - 2);
		else if (x > 2)
			fx = rnd(2, x);
		break;
	}
}

void genF(int x, int y, int& fx, int& fy)
{
	srand(time(0));

	fx = rand() % (w - 2) + 2;
	fy = rand() % (h - 2) + 2;

	if (fy >= y && fy <= y + ph && fx >= x && fx <= x + pw)		pieceOfShitOptimisedRNGFoodGen(x, y, fx, fy);
}

void checkF(int x, int y, int& fx, int& fy)
{
	if (fy >= y && fy <= y + ph && fx >= x && fx <= x + pw)
	{
		score += 100;

		pw++;
		if (pw > ph + (pw / 2) && ph <= h - 4)	ph++;

		if (pw >= w - 4 && ph >= h - 4)
		{
			system("cls");

			cout << "Congratulations!\nYou've won with the score of " << score << "!\n\n";

			system("pause");
			exit(EXIT_FAILURE);
		}

		genF(x, y, fx, fy);
	}
}

void draw(float& x, float& y, int& fx, int& fy)
{
	checkF(x, y, fx, fy);

	if (x < 2)			x = 2;
	if (y < 2)			y = 2;
	if (x > w - pw - 1)	x = w - pw - 1;
	if (y > h - ph - 1)	y = h - ph - 1;

	system("cls");

	cout << "Score : " << score << endl;

	for (int i = 1; i <= h; i++)
	{
		for (int j = 1; j <= w; j++)
		{
			if (i >= round(y) && i <= round(y) + ph
			 && j >= round(x) && j <= round(x) + pw)	cout << "#";
			else if (i == fy && j == fx)				cout << "O";
			else if (i == 1 && j == 1)					cout << "/";
			else if (i == 1 && j == w)					cout << "\\";
			else if (i == h && j == 1)					cout << "\\";
			else if (i == h && j == w)					cout << "/";
			else if (i == h || i == 1)					cout << "-";
			else if (j == w || j == 1)					cout << "|";
			else										cout << " ";
		}

		cout << endl;
	}

	cout << "\nx : " << x << "\ny : " << y << "\ns : " << spd;
}

int main()
{
	float x = 2, y = 2;
	int fx = 0, fy = 0;

	genF((int)x, (int)y, fx, fy);

	w += 2;
	h += 2;

	pw--;
	ph--;

	while (true)
	{
		if (GetKeyState(VK_RIGHT) & 0x8000)	x += spd * 1.75;
		if (GetKeyState(VK_LEFT) & 0x8000)	x -= spd * 1.75;
		if (GetKeyState(VK_DOWN) & 0x8000)	y += spd * 0.75;
		if (GetKeyState(VK_UP) & 0x8000)	y -= spd * 0.75;

		draw(x, y, fx, fy);

		Sleep(lat);
	}

	cout << endl;	system("pause");	return 0;
}