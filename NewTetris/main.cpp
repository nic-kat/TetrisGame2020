#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TheGame.h"
#include "Button.h"
#include "Screen.h"
#include <fstream>
#include <string>

 int f[8][4] = //матрица со всеми фигурами
{
	0,0,0,0, //добавил нулевую фигурку
	3,5,4,7, // T
	2,4,5,7, // Z
	3,5,4,6, // S
	2,3,4,5, // O
	1,3,5,7, // I
	2,5,3,7, // L
	3,5,7,6, // J
};
 const int square = 18;
 int scrWidth = 800, scrHeight = 600, mode=0;
 sf::RenderWindow window(sf::VideoMode(scrWidth, scrHeight), "MIEM Tetris");
 Screen S;

 void mainPressKey(TheGame& a, TheGame& b, bool& pause)  {
	sf::Event event;
	while (window.pollEvent(event))//Слушатель нажатия на клавишу
	{
		if (event.type == sf::Event::Closed) {
			window.close();
			a.gameover = b.gameover = 1;
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) pause = 1;
			if (event.key.code == sf::Keyboard::G) a.turn = 1;
			if (event.key.code == sf::Keyboard::H) a.turn = 2;
			if (event.key.code == sf::Keyboard::S) a.delay /= 30;//Ускорение фигурки(уменьшение задержки)
			if (event.key.code == sf::Keyboard::W) a.harddrop = 1;
			if (event.key.code == sf::Keyboard::A) a.dx = -1;//движение влево/вправо
			if (event.key.code == sf::Keyboard::D) a.dx = 1;
			if (event.key.code == sf::Keyboard::J) a.change++;
			if (event.key.code == sf::Keyboard::B) b.turn = 1;
			if (event.key.code == sf::Keyboard::N) b.turn = 2;
			if (event.key.code == sf::Keyboard::Down) b.delay /= 30;//Ускорение фигурки(уменьшение задержки)
			if (event.key.code == sf::Keyboard::Up) b.harddrop = 1;
			if (event.key.code == sf::Keyboard::Left) b.dx = -1;//движение влево/вправо
			if (event.key.code == sf::Keyboard::Right) b.dx = 1;
			if (event.key.code == sf::Keyboard::M) b.change++;
		}
	}
 }

 void mainPressKey(TheGame& a, bool& pause) {
	 sf::Event event;
	 while (window.pollEvent(event))//Слушатель нажатия на клавишу
	 {
		 if (event.type == sf::Event::Closed) {
			 window.close();
			 a.gameover = 1;
		 }
		 if (event.type == sf::Event::KeyPressed) {
			 if (event.key.code == sf::Keyboard::Space) pause = 1;
			 if (event.key.code == sf::Keyboard::Z) a.turn = 1;
			 if (event.key.code == sf::Keyboard::X) a.turn = 2;
			 if (event.key.code == sf::Keyboard::Down) a.delay /= 30;//Ускорение фигурки(уменьшение задержки)
			 if (event.key.code == sf::Keyboard::Up) a.harddrop = 1;
			 if (event.key.code == sf::Keyboard::Left) a.dx = -1;//движение влево/вправо
			 if (event.key.code == sf::Keyboard::Right) a.dx = 1;
			 if (event.key.code == sf::Keyboard::C) a.change++;
		 }
	 }
 }

 void mainPressKey() {
	 sf::Event event;
	 while (window.pollEvent(event))//Слушатель нажатия на клавишу
	 {
		 if (event.type == sf::Event::Closed) 
			 window.close();
	 }
 }

 bool IsScore(int score)
 {
	 std::ifstream input("txt/leaderboard.txt");
	 std::vector<std::string> file;
	 std::string best_score;
	 bool IsScore = 0;
	 int bestscore;
	 if (!input.is_open())
		 std::cout << "File can't be opened!\n";
	 else
	 {
		 std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(file));
		 for (int i = 1; i < 10; i += 2)
		 {
			 best_score = file[i];
			 bestscore = std::stoi(best_score);
			 if (score > bestscore)
				 IsScore = 1;
		 }
	 }
	 return IsScore;
 }

 void saveScore(int score, std::string TextBox)
 {
	 std::ifstream input("txt/leaderboard.txt");
	 std::vector<std::string> file;
	 std::string best_score;
	 int bestscore;
	 if (!input.is_open())
		 std::cout << "File can't be opened!\n";
	 else
	 {
		 std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(file));
		 for (int i = 1; i < 10; i += 2)
		 {
			 best_score = file[i];
			 bestscore = std::stoi(best_score);
			 if (score > bestscore)
			 {
				 switch (i)
				 {
				 case 1:
					 file[i + 8] = file[i + 6];
					 file[i + 7] = file[i + 5];
					 file[i + 6] = file[i + 4];
					 file[i + 5] = file[i + 3];
					 file[i + 4] = file[i + 2];
					 file[i + 3] = file[i + 1];
					 file[i + 2] = file[i];
					 file[i + 1] = file[i - 1];
					 file[i] = std::to_string(score);
					 file[i - 1] = TextBox;
					 break;
				 case 3:
					 file[i + 6] = file[i + 4];
					 file[i + 5] = file[i + 3];
					 file[i + 4] = file[i + 2];
					 file[i + 3] = file[i + 1];
					 file[i + 2] = file[i];
					 file[i + 1] = file[i - 1];
					 file[i] = std::to_string(score);
					 file[i - 1] = TextBox;
					 break;
				 case 5:
					 file[i + 4] = file[i + 2];
					 file[i + 3] = file[i + 1];
					 file[i + 2] = file[i];
					 file[i + 1] = file[i - 1];
					 file[i] = std::to_string(score);
					 file[i - 1] = TextBox;
					 break;
				 case 7:
					 file[i + 2] = file[i];
					 file[i + 1] = file[i - 1];
					 file[i] = std::to_string(score);
					 file[i - 1] = TextBox;
					 break;
				 case 9:
					 file[i] = std::to_string(score);
					 file[i - 1] = TextBox;
					 break;
				 }
				 break;

			 }
		 }
		 std::ofstream output{ "txt/leaderboard.txt", std::ios_base::trunc };
		 if (!output.is_open())
			 std::cout << "File can't be opened!\n";
		 else
			 std::copy(file.begin(), file.end(), std::ostream_iterator<std::string>(output, "\n"));
		 file.clear();
	 }
 }

int main() {
	window.setFramerateLimit(60);
	TheGame game, game2;
	Button Start1P, Start2P, Return, Leaderboard, OK, TEXTBOX, Music;
	sf::Music music;
	int outcome = 0, score = 0, musicSwitch=2;
	bool pause = 0;
	std::string TextBox = "";
	music.openFromFile("music/music.ogg");
	music.setLoop(true);
	music.setVolume(40);
	while (window.isOpen()) {
			switch (mode) {
			case 0:
				S.ScreenSetup("images/background1.jpeg");
				S.SetCaption(0, 0, 2, 5, 50, "MIEM TETRIS");
				Start1P.setButton("images/button.jpg", "1 PLAYER", 24, 200, 75, 300, 250);
				Start2P.setButton("images/button.jpg", "2 PLAYERS", 24, 200, 75, 300, 350);
				Music.setButton("images/button.jpg", "MUSIC", 12, 70, 30, 30, 30);
				Leaderboard.setButton("images/button.jpg", "LEADERBOARDS", 24, 200, 75, 300, 450);
				window.display();
				sf::Event event;
				while (window.pollEvent(event))//Слушатель нажатия на клавишу
				{
					if (event.type == sf::Event::Closed)
						window.close();
					if (Music.buttonIsPressed(event))
					{
						switch (musicSwitch)
						{
						case 1:
							music.stop();
							musicSwitch = 2;
							break;
						case 2:
							music.play();
							musicSwitch = 1;
							break;
						}
					}
					if (Start1P.buttonIsPressed(event))
						mode = 1;
					if (Start2P.buttonIsPressed(event))
						mode = 2;
					if (Leaderboard.buttonIsPressed(event))
						mode = 5;
				}
				break;
			case 1:
				game.setGrid(scrWidth / 2, 0.1 * scrHeight);
				game.setGame();
				while (!(game.getGameover())) {
					mainPressKey(game, pause);
					while (pause == 1) {
						sf::Event event;
						while (window.pollEvent(event))//Слушатель нажатия на клавишу
						{
							if (event.type == sf::Event::Closed)
								window.close(), pause = 0;
							if (event.type == sf::Event::KeyPressed) {
								if (event.key.code == sf::Keyboard::Space) pause = 0;
							}
						}
						game.renderBackground();
						game.render(1);
						S.SetCaption(scrWidth / 2, scrHeight / 2, 24, "Pause");
						window.display();
					}
					game.play();
					game.renderBackground();
					game.render(0);
					window.display();
				}
				outcome = 1;
				if (IsScore(game.getScore()))
				{
					mode = 4;
					TextBox = "";
				}
				else
					mode = 3;
				break;
			case 2:
				window.clear(sf::Color::White);
				game.setGrid(scrWidth * 0.2, 0.1 * scrHeight);
				game.setGame();
				game2.setGrid(scrWidth * 0.8, 0.1 * scrHeight);
				game2.setGame();
				while (!(game.getGameover()) || !(game2.getGameover())) {
					mainPressKey(game, game2, pause);
					while (pause==1) {
						sf::Event event;
						while (window.pollEvent(event))//Слушатель нажатия на клавишу
						{
							if (event.type == sf::Event::Closed)
								window.close(), pause = 0;
							if (event.type == sf::Event::KeyPressed) {
								if (event.key.code == sf::Keyboard::Space) pause = 0;
							}
						}
						game2.renderBackground();
						game.render(1);
						game2.render(2);
						S.SetCaption(scrWidth/2, scrHeight/2, 24, "Pause");
						window.display();
					}
					if (!(game.getGameover()))
						game.play();
					if (!(game2.getGameover()))
						game2.play();
					game2.renderBackground();
					game.render(1);
					game2.render(2);
					window.display();
				}
				std::cout << "Player#1 has scored: " << game.getScore() << "\n";
				std::cout << "Player#2 has scored: " << game2.getScore() << "\n";
				if (game.getScore() > game2.getScore())
					std::cout << "Player#1 wins\n";
				else
					std::cout << "Player#2 wins\n";
				outcome = 2;
				mode = 3;
				break;

			case 3:
				S.ScreenSetup("images/background.jpg");
				Return.setButton("images/button.jpg", "RETURN TO THE MAIN MENU", 24, 350, 75, 225, 350);
				switch (outcome) {
				case 0:
					break;
				case 1:
					S.SetCaption(0, 0, 2, 5, 30, "YOU HAVE SCORED: " + std::to_string(game.getScore()) + " POINTS");
					Leaderboard.setButton("images/button.jpg", "LEADERBOARDS", 24, 350, 75, 225, 450);
					break;
				case 2:
					S.SetCaption(0, 0, 2, 5, 30, "PLAYER#1 HAVE SCORED: " + std::to_string(game.getScore()) + " POINTS");
					S.SetCaption(0, 50, 2, 5, 30, "PLAYER#2 HAVE SCORED: " + std::to_string(game2.getScore()) + " POINTS");
					if (game.getScore() > game2.getScore())
						S.SetCaption(0, 100, 2, 5, 30, "PLAYER#1 WINS");
					else
						S.SetCaption(0, 100, 2, 5, 30, "PLAYER#2 WINS");
					break;
				}
				//sf::Event event;
				while (window.pollEvent(event))//Слушатель нажатия на клавишу
				{
					/*if (event.type == sf::Event::Closed)
						window.close();*/
					if (Return.buttonIsPressed(event))
						mode = 0;
					if (Leaderboard.buttonIsPressed(event))
						mode = 5;
				}
				window.display();
				break;
			case 4:
				//sf::Event event;
				/*while (window.pollEvent(event))
				{
					if (event.type == sf::Event::TextEntered) {
						if (event.text.unicode < 128)
							TextBox += event.text.unicode;
					}
					if (event.type == sf::Event::KeyPressed) {
						if (event.key.code == sf::Keyboard::BackSpace)if (TextBox != "")TextBox.erase(TextBox.size() - 1);
					}
				}*/
				S.ScreenSetup("images/background2.jpg");
				TEXTBOX.setButton("images/WhiteBox.jpg", TextBox, 24, 350, 75, 225, 300);
				OK.setButton("images/button.jpg", "OK", 36, 100, 100, 350, 400);
				S.SetCaption(0, 0, 2, 5, 30, "CONGRATULATIONS! NEW RECORD!");
				S.SetCaption(0, 50, 2, 5, 30, "ENTER YOUR NAME");
				//sf::Event event;
				while (window.pollEvent(event))//Слушатель нажатия на клавишу
				{
					if (event.type == sf::Event::TextEntered) {
						if (event.text.unicode < 128)
							TextBox += event.text.unicode;
					}
					if (event.type == sf::Event::KeyPressed) {
						if (event.key.code == sf::Keyboard::BackSpace)if (TextBox != "")TextBox.erase(TextBox.size() - 1);
					}
					if (event.type == sf::Event::Closed)
						window.close();
					if (TextBox != "")
					if (OK.buttonIsPressed(event))
					{
						mode = 3;
						saveScore(game.getScore(), TextBox);
					}
				}
				window.display();
				break;
			case 5:
				S.ScreenSetup("images/background2.jpg");
				S.LeaderboardSetup();
				Return.setButton("images/button.jpg", "RETURN TO THE MAIN MENU", 24, 350, 75, 225, 500);
				//sf::Event event;
				while (window.pollEvent(event))//Слушатель нажатия на клавишу
				{
					if (event.type == sf::Event::Closed)
						window.close();
					if (Return.buttonIsPressed(event))
						mode = 0;
				}
				window.display();
				break;
			}
		
	}
	//system("pause");
	return 0;
}