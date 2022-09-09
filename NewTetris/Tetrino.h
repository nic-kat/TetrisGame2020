#pragma once
#include "Point.h"
#include "cmath"

extern int f[8][4];
const int n = 19;
const int m = 9;

class Tetrino
{
public:
	Point a[4];
	int color;
	Tetrino(int color0 = -1) :color(color0) {}

	void createTetrino(int c = 0) {//ñîçäàíèå ôèãóğêè
		if (c == 0)
			color = rand() % 7 + 1;
		else
			color = c;
		if (c >= 0) {
			for (int i = 0; i < 4; ++i) {
				a[i].x = f[color][i] % 2;
				a[i].y = f[color][i] / 2;
			}
		}
	}

	void moveToCenter() {
		for (int i = 0; i < 4; ++i) {
			a[i].x += m / 2;
			a[i].y -= 2;
		}
	}

	bool check_y(int Scr[][m+1]) {//Ïğîâåğêà âîçìîæíîñòè äâèæåíèÿ ïî y
		Point fake[4];
		for (int i = 0; i < 4; ++i) {
			fake[i] = a[i];
			fake[i].y++;
			if (fake[i].y > n || (fake[i].y > 0 && Scr[fake[i].y][fake[i].x]))// ÄÎÏÎËÍÈÒÜ, ÊÎÃÄÀ ÏÎßÂÈÒÑß ÌÀÒĞÈÖÀ
				return 0;
		}
		return 1;
	}

	void move_x(int Scr[][m + 1], int &dx) {
		Point fake[4];
		for (int i = 0; i < 4; ++i) {
			fake[i] = a[i];
			fake[i].x += dx;
			if (fake[i].x > m || fake[i].x < 0 || (fake[i].y > 0 && Scr[fake[i].y][fake[i].x]))// ÄÎÏÎËÍÈÒÜ, ÊÎÃÄÀ ÏÎßÂÈÒÑß ÌÀÒĞÈÖÀ
				goto Fin;
		}
		for (int i = 0; i < 4; ++i)
			a[i] = fake[i];
	Fin:
		dx = 0;
	}

	void rotate(int Scr[][m + 1], int& turn) {
		Point cent = a[1], fake[4];
		int x, y, count = 0;
		for (int i = 0; i < 4; ++i) {
			fake[i] = a[i];
			x = fake[i].x - cent.x;
			y = fake[i].y - cent.y;
			fake[i].x = pow(-1, turn + 1) * y + cent.x;
			fake[i].y = pow(-1, turn) * x + cent.y;
			if (fake[i].x > m)
				count--;
			else if (fake[i].x < 0)
				count++;
			if (fake[i].y >= n || (fake[i].y > 0 && Scr[fake[i].y][fake[i].x]))// ÄÎÏÎËÍÈÒÜ, ÊÎÃÄÀ ÏÎßÂÈÒÑß ÌÀÒĞÈÖÀ
				goto Fin;
		}
		for (int i = 0; i < 4; ++i) {
			a[i] = fake[i];
			a[i].x += count;
		}

	Fin:
		turn = 0;
	}

	void fall() {
		for (int i = 0; i < 4; ++i)
			a[i].y++;
	}

	~Tetrino() {};
};