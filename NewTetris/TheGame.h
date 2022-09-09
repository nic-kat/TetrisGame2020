#pragma once
#include <SFML/Graphics.hpp>
#include "Tetrino.h"
#include "Screen.h"
#include <iostream> 
extern const int square;
extern sf::Event event, event2;
extern int scrWidth, scrHeight,mode;
extern sf::RenderWindow window;
extern Screen S;

class TheGame
{
private:
	int Scr[n+1][m+1], rows[4], lines, level, score;
	float timer, locktimer, lockdelay = 0.15;
	sf::Clock clock, lockclock;
	Tetrino player, nextf, pocketf, ghost;
	sf::Texture t1, t2, t3, t4, t5;//объявление текстур
	sf::Sprite sq, sqg, background, frame, grid, next, pocket;
public:
	bool gameover, harddrop;
	int dx, turn, change;
	double delay;

	bool getGameover() {return gameover;}

	int getScore() {return score;}

	void timerInc() {
		float time = clock.getElapsedTime().asSeconds();//Счетчик времени, требуется для плавного падения фигуры
		clock.restart();
		timer += time;
	}

	void setGrid(int x = 0, int y = 0) {
		t5.loadFromFile("images/grid1.png");
		grid = sf::Sprite(t5);
		if (x < grid.getLocalBounds().width / 2)
			grid.setPosition(0, y);
		else
			grid.setPosition(x - grid.getLocalBounds().width/2, y);
	}

	void setGame() {
		player.createTetrino();//потом нужно будет убрать
		ghost = player;
		while (ghost.check_y(Scr))
			ghost.fall();
		player.moveToCenter();
		nextf.createTetrino();
		pocketf.createTetrino(-1);
		t1.loadFromFile("images/tiles.png");
		t2.loadFromFile("images/background2.jpg");
		t3.loadFromFile("images/frame.png");
		t4.loadFromFile("images/next.png");
		sq = sf::Sprite(t1);
		sqg = sf::Sprite(t1);
		sqg.setColor(sf::Color(255, 255, 255, 128));
		background = sf::Sprite(t2);
		frame = sf::Sprite(t3);
		next = sf::Sprite(t4);
		pocket = sf::Sprite(t4);
		Point pos;
		pos.x = grid.getPosition().x - 10;
		pos.y = grid.getPosition().y - 10;
		frame.setPosition(pos.x, pos.y);
		pos.x += (frame.getLocalBounds().width) * 1.1;
		next.setPosition(pos.x, pos.y);
		pos.x -= ((frame.getLocalBounds().width) * 1.2 + pocket.getLocalBounds().width);
		pocket.setPosition(pos.x, pos.y);
		gameover = harddrop = timer = lines = level = score = dx = turn = change = 0;
		delay = 0.5;
		locktimer = -1;
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= m; ++j)
				Scr[i][j] = 0;
		}
		for (int i = 0; i < 4; ++i)
			rows[i] = -1;
	}

	void rowCleaning() {
		int k = 0;
		for (int i = n; i >= 0; --i) {
			int counter = 0;
			for (int j = 0; j <= m; ++j) {

				if (Scr[i][j] != 0)
					++counter;
				else
					--counter;
			}
			if (counter == m + 1) {
				rows[k] = i;
				++k;
			}
			if (counter == -m - 1 || k >= 4)
				break;
		}
		for (int c = k - 1; c >= 0; --c) {
			for (int i = rows[c]; i >= 0; --i) {
				int counter = 0;
				for (int j = 0; j <= m; ++j) {
					if (Scr[i][j] == 0)
						++counter;
					Scr[i][j] = Scr[i - 1][j];
				}
				if (counter == m + 1)
					break;
			}
			rows[c] = -1;
		}
		if (k > 0) {
			lines += k;
			level = lines / 10;
			switch (k)
			{
			case 1:
				score += (level + 1) * 40;
				break;
			case 2:
				score += (level + 1) * 100;
				break;
			case 3:
				score += (level + 1) * 300;
				break;
			case 4:
				score += (level + 1) * 1200;
				break;
			default:
				break;
			}
		}
	}

	void play() {
		timerInc();
		if (harddrop == 1) {
			while (player.check_y(Scr)) {
				player.fall();
				score += 2;
			}
		}
		if (timer > delay && player.check_y(Scr)) {
			player.fall();
			timer = 0;
			if (delay < (0.5-0.035*(level))) {
				delay = 0.5 - 0.035 * (level);
				score++;
			}
			ghost = player;
			while (ghost.check_y(Scr))
				ghost.fall();
		}

		if (!player.check_y(Scr)) {
			if (locktimer < 0) {
				lockclock.restart();
				locktimer = 0;
			}
			float time = lockclock.getElapsedTime().asSeconds();//Счетчик времени, требуется для плавного падения фигуры
			lockclock.restart();
			locktimer += time;
			if (locktimer > lockdelay || harddrop == 1) {
				for (int i = 0; i < 4; ++i)
					Scr[player.a[i].y][player.a[i].x] = player.color;
				rowCleaning();
				change = 0;
				delay = 0.5 - 0.035 * (level);
				harddrop = 0;
				player.createTetrino(nextf.color);
				player.moveToCenter();
				ghost = player;
				while (ghost.check_y(Scr))
					ghost.fall();
				nextf.createTetrino();
				if (!player.check_y(Scr))
					gameover = true;
				locktimer = -1;
			}
		}
		if (dx) {
			player.move_x(Scr, dx);
			ghost = player;
			while (ghost.check_y(Scr))
				ghost.fall();
		}
		if (turn && player.color != 4) {
			player.rotate(Scr, turn);
			ghost = player;
			while (ghost.check_y(Scr))
				ghost.fall();
		}
		if (change == 1) {
			change++;
			if (pocketf.color < 0) {
				pocketf.createTetrino(player.color);
				player.createTetrino(nextf.color);
				player.moveToCenter();
				nextf.createTetrino();
			}
			else {
				int temp = player.color;
				player.createTetrino(pocketf.color);
				player.moveToCenter();
				pocketf.createTetrino(temp);
			}
			ghost = player;
			while (ghost.check_y(Scr))
				ghost.fall();
		}

	}

	void renderBackground() {
		window.clear(sf::Color::White);//очищение экрана
		window.draw(background);
	}

	void render(int SetScore2P) {
			window.draw(next);
			window.draw(frame);
			window.draw(grid);
			window.draw(pocket);
			if (mode == 1)
			{
				//S.SetCaption(0, 0, 6, 6, 24, "Level: " + std::to_string(level));
				//S.SetCaption(0, 75, 6, 6, 24, "Lines: " + std::to_string(lines));
				//S.SetCaption(0, 150, 6, 6, 24, "Score: " + std::to_string(score));
				S.SetCaption(grid.getPosition().x - 240, grid.getPosition().y + 100, 24, "Level: " + std::to_string(level));
				S.SetCaption(grid.getPosition().x - 240, grid.getPosition().y + 175, 24, "Lines: " + std::to_string(lines));
				S.SetCaption(grid.getPosition().x - 240, grid.getPosition().y + 250, 24, "Score: " + std::to_string(score));
			}
			if (mode == 2)
			{
				if (SetScore2P == 2)
				{
					//S.SetCaption(70, 75, 2, 6, 24, "Level: " + std::to_string(level));
					//S.SetCaption(70, 150, 2, 6, 24, "Lines: " + std::to_string(lines));
					//S.SetCaption(70, 225, 2, 6, 24, "Score: " + std::to_string(score));
					S.SetCaption(grid.getPosition().x - 140, grid.getPosition().y + 100, 19, "Level: " + std::to_string(level));
					S.SetCaption(grid.getPosition().x - 140, grid.getPosition().y + 175, 19, "Lines: " + std::to_string(lines));
					S.SetCaption(grid.getPosition().x - 140, grid.getPosition().y + 250, 19, "Score: " + std::to_string(score));
				}
				if (SetScore2P == 1)
				{
					//S.SetCaption(150, 75, 6, 6, 24, "Level: " + std::to_string(level));
					//S.SetCaption(150, 150, 6, 6, 24, "Lines: " + std::to_string(lines));
					//S.SetCaption(150, 225, 6, 6, 24, "Score: " + std::to_string(score));
					S.SetCaption(grid.getPosition().x + 195, grid.getPosition().y + 100, 19, "Level: " + std::to_string(level));
					S.SetCaption(grid.getPosition().x + 195, grid.getPosition().y + 175, 19, "Lines: " + std::to_string(lines));
					S.SetCaption(grid.getPosition().x + 195, grid.getPosition().y + 250, 19, "Score: " + std::to_string(score));
				}
			}
		for (int i = 0; i <= n; ++i) {//отрисовка уже упавших фигур
			for (int j = 0; j <= m; ++j) {
				if (Scr[i][j])
					drawing(sq, Scr[i][j], grid.getPosition().x + (j) * square, grid.getPosition().y + i * square);
			}
		}
		for (int i = 0; i < 4; i++) {//отрисовка движущейся фигуры
			if (player.a[i].y >= 0) {//сделал, чтоб фигурка не отрисовывалась за пределами рамки
				drawing(sq, player.color, grid.getPosition().x + player.a[i].x * square, grid.getPosition().y + (player.a[i].y) * square);
			}
		}
		for (int i = 0; i < 4; i++) //отрисовка будущей фигуры
			drawing(sq, nextf.color, next.getPosition().x + 3 + (nextf.a[i].x) * square, next.getPosition().y + 2 + (nextf.a[i].y) * square);
		if (pocketf.color > 0) {
			for (int i = 0; i < 4; i++) //отрисовка карманной фигуры 
				drawing(sq, pocketf.color, pocket.getPosition().x + 3 + (pocketf.a[i].x) * square, pocket.getPosition().y + 2 + (pocketf.a[i].y) * square);
		}
		for (int i = 0; i < 4; i++) {//отрисовка призрачной фигуры
			drawing(sqg, ghost.color, grid.getPosition().x + ghost.a[i].x * square, grid.getPosition().y + (ghost.a[i].y) * square);
		}
	}

	void drawing(sf::Sprite& sq, int color, int x, int y) {
		sq.setTextureRect(sf::IntRect(color * square, 0, square, square));
		sq.setPosition(x, y);
		window.draw(sq);
	}
	~TheGame() {};
};