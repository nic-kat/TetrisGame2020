#include <SFML/Graphics.hpp>
#pragma once
extern sf::RenderWindow window;
class Button
{
private:
	int width = 0, height = 0, x = 0, y = 0, temp = -1;
	float dwidth = 0, dheight = 0, timer = 0;;
	sf::Clock clock;
	sf::Sprite sprite;
	sf::Texture b;
	sf::Text text;

public:
	/*void setButton(std::string path_, int width_, int height_, int x_, int y_, sf::RenderWindow& window) {
		width = width_;
		height = height_;
		x = x_;
		y = y_;
		b.loadFromFile(path_);
		sprite.setTexture(b);
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));//ширина, высота кнопки
		sprite.setPosition(x, y);//позиция кнопки относительно окна
		window.draw(sprite);
	}*/

	void setButton(std::string path_,std::string name,int CharacterSize, int width_, int height_, int x_, int y_) {
		width = width_;
		height = height_;
		x = x_;
		y = y_;
		b.loadFromFile(path_);
		sprite.setTexture(b);
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));//ширина, высота кнопки
		sprite.setPosition(x, y);//позиция кнопки относительно окна
		window.draw(sprite);
		sf::Font font;
		font.loadFromFile("fonts/2.otf");
		text.setFont(font);
		text.setCharacterSize(CharacterSize);
		text.setFillColor(sf::Color::Black);
		text.setOutlineColor(sf::Color::White);
		text.setOutlineThickness(1);
		text.setString(name);
		text.setPosition(0, 0);
		sf::FloatRect rect = text.getLocalBounds();
		text.setPosition(x + width / 2 - rect.width / 2, y + height / 2 - rect.height / 2);
		window.draw(text);
	}

	/*void setButtonText(std::string name) {
		sf::Font font;
		font.loadFromFile("fonts/2.otf");
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Black);
		text.setOutlineColor(sf::Color::White);
		text.setOutlineThickness(1);
		text.setString(name);
		text.setPosition(0, 0);
		sf::FloatRect rect = text.getLocalBounds();
		text.setPosition(x + width / 2 - rect.width / 2, y + height / 2 - rect.height / 2);
		window.draw(text);
	}*/

	bool buttonIsPressed(sf::Event event) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (mousePos.x > x&& mousePos.x < (x + width) && mousePos.y > y&& mousePos.y < (y + height)) {
			if (event.type == sf::Event::MouseButtonPressed)
				return 1;
		}
		return 0;
	}

	/*void activeButton() {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		float time = clock.getElapsedTime().asSeconds();//Счетчик времени, требуется для плавного падения фигуры
		clock.restart();
		timer += time;
		if (mousePos.x > x&& mousePos.x < x + width && mousePos.y > y&& mousePos.y < y + height && dwidth < width * 0.1 && dheight < height * 0.1) {
			if (temp == -1) timer = 0;
			dwidth += timer * 10;
			dheight += timer * 10;
			temp = 1;
		}
		else if ((mousePos.x < x || mousePos.x > x + width || mousePos.y < y || mousePos.y > y + height) && (dwidth > 0 || dheight > 0)) {
			if (temp == 1) timer = 0;
			dwidth -= timer * 10;
			dheight -= timer * 10;
			temp = -1;
		}
		sprite.setTextureRect(sf::IntRect(0, 0, width + dwidth, height + dheight));//ширина, высота кнопки
		sprite.setPosition(x - dwidth / 2, y - dheight / 2);//позиция кнопки относительно окна
		window.draw(sprite);
	}

	void textDisplay(sf::RenderWindow& window) {
		window.draw(text);
	}*/
	~Button() {};
};

