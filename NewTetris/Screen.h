#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Button.h"

extern int scrWidth, scrHeight;
extern sf::RenderWindow window;

class Screen
{
private:
	sf::Text Caption;
	sf::Texture t;
	sf::Sprite background;
public:
	void ScreenSetup(std::string path)
	{
		window.clear(sf::Color::White);
		t.loadFromFile(path);
		background = sf::Sprite(t);
		background.scale(sf::Vector2f(1.5625f, 1.2f));
		window.draw(background);
		//background.setScale(ScreenWidth, ScreenHeight);
	}

	void SetCaption(int CaptionX, int CaptionY, float ratioX, float ratioY, int CaptionSize, std::string Text)
	{
		sf::Font font;
		font.loadFromFile("fonts/2.otf");
		Caption.setCharacterSize(CaptionSize);
		Caption.setString(Text);
		Caption.setFont(font);
		Caption.setFillColor(sf::Color::Black);
		Caption.setOutlineColor(sf::Color::White);
		Caption.setOutlineThickness(1);
		sf::FloatRect rect = Caption.getLocalBounds();
		Caption.setPosition(CaptionX + scrWidth / ratioX - rect.width / ratioX, CaptionY + scrHeight / ratioY - rect.height / ratioY);
		window.draw(Caption);
	}

	void SetCaption(int CaptionX, int CaptionY, int CaptionSize, std::string Text)
	{
		sf::Font font;
		font.loadFromFile("fonts/2.otf");
		Caption.setCharacterSize(CaptionSize);
		Caption.setString(Text);
		Caption.setFont(font);
		Caption.setFillColor(sf::Color::Black);
		Caption.setOutlineColor(sf::Color::White);
		Caption.setOutlineThickness(1);
		Caption.setPosition(CaptionX, CaptionY);
		window.draw(Caption);
	}
	/*void SetButton(Button button, std::string ButtonPath, std::string ButtonText, int ButtonWidth, int ButtonHeight, int ButtonX, int ButtonY, sf::RenderWindow& window)
	{
		button.setButton(ButtonPath, ButtonWidth, ButtonHeight, ButtonX, ButtonY, window);
		button.setButtonText(ButtonText, window);
	}

	/*bool ButtonIsPressed(sf::RenderWindow& window, Button button)
	{
		return button.buttonIsPressed(window);
	}*/

	/*void CleanScr(sf::RenderWindow& window)
	{
		window.clear(sf::Color::White);
	}*/
	
	void LeaderboardSetup()
	{
		std::ifstream input("txt/leaderboard.txt");
		std::vector<std::string> file;
		if (!input.is_open())
			std::cout << "File can't be opened!\n";
		else
		{
			std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(file));
			SetCaption(0, -50, 2, 8, 30, "LEADERBOARDS");
			SetCaption(0, 0, 4, 5, 30, "1.");
			SetCaption(100, 0, 4, 5, 30, file[0]);
			SetCaption(300, 0, 4, 5, 30, file[1]);
			SetCaption(0, 75, 4, 5, 30,  "2.");
			SetCaption(100, 75, 4, 5, 30, file[2]);
			SetCaption(300, 75, 4, 5, 30, file[3]);
			SetCaption(0, 150, 4, 5, 30,  "3.");
			SetCaption(100, 150, 4, 5, 30, file[4]);
			SetCaption(300, 150, 4, 5, 30, file[5]);
			SetCaption(0, 225, 4, 5, 30,  "4.");
			SetCaption(100, 225, 4, 5, 30, file[6]);
			SetCaption(300, 225, 4, 5, 30, file[7]);
			SetCaption(0, 300, 4, 5, 30,  "5.");
			SetCaption(100, 300, 4, 5, 30, file[8]);
			SetCaption(300, 300, 4, 5, 30, file[9]);
		}
	}

	~Screen() {};
};
