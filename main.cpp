#include <Windows.h>
#include <string.h>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <math.h>
#include <vector>

#define WIDTH 1200.0
#define HEIGHT 600.0
#define phi ((sqrt(5) + 1)/2)
#define mlen (min(WIDTH, HEIGHT) - 100.0)
#define max_level 12

sf::RenderWindow window;
std::vector<sf::RectangleShape *> boxes;

void makeSquare(float x, float y, float len) {
	sf::RectangleShape * box = new sf::RectangleShape();
	sf::Vector2f s(len, len);
	box->setSize(s);
	box->setPosition(x, y);
	window.draw(*box);
	window.display();

	boxes.push_back(box);
}

void draw(int l, float x, float y) {
	if (l > max_level)
		return;

	float len = 1.4 * mlen / pow(phi, l);
	float nexty;
	if (l % 2)
		nexty = y;
	else
		nexty = y + len - len / phi;

	makeSquare(x, y, len);
	draw(++l, x+len, nexty);
}

bool inBounds() {
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	return (mouse.x > 20 && mouse.y > 20 && mouse.x < WIDTH - 20 && mouse.y < HEIGHT - 20);
}

bool isHoveringOverBox(sf::RectangleShape * b) {
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	sf::Vector2f p = b->getPosition();
	return (mouse.x >= p.x && mouse.x <= p.x + b->getSize().x && mouse.y >= p.y && mouse.y <= p.y + b->getSize().y);
}

void colorBoxes(sf::RectangleShape * curr) {
	window.clear(sf::Color::Cyan);
	bool hit = false;
	int s = boxes.size();
	int n = 0;
	int m;
	for (int i = 0; i < s; i++) {
		if (boxes[i] == curr) {
			hit = true;
			m = s - i;
		}
		if (hit) {
			int c = 255 - (n * 256 / m);
			boxes[i]->setFillColor(sf::Color(c, c, c));
			n++;
		} else {
			boxes[i]->setFillColor(sf::Color::White);
		}
		window.draw(*boxes[i]);
	}
	window.display();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Fibonacci Tower");
	window.clear(sf::Color::Cyan);
	window.display();
	draw(1, 20.0, 20.0);

	sf::RectangleShape * curr = 0;

	while (window.isOpen()) {
		if (inBounds()) {
			for (int i = 0; i < boxes.size(); i++) {
				if (isHoveringOverBox(boxes[i])) {
					curr = boxes[i];
					if (i > 0) {
						bool first = true;
						int init = 0;
						int diff = 0;
						int mouse = 0;
						int pos = 0;
						while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
							pos = curr->getPosition().y;
							mouse = sf::Mouse::getPosition(window).y;
							int boundl = boxes[i-1]->getPosition().y;
							int boundh = boxes[i-1]->getPosition().y + boxes[i-1]->getSize().y - curr->getSize().y;
							if (first) {
								init = mouse;
								diff = init - pos;
								first = false;
							}
							int newy = mouse-diff;
							if (newy > boundl && newy < boundh) {
								curr->setPosition(curr->getPosition().x, newy);
								for (int j = i+1; j < boxes.size(); j++) {
									sf::Vector2f np = boxes[j]->getPosition();
									boxes[j]->setPosition(np.x, np.y + newy - pos);
								}
							}
							colorBoxes(curr);
						}
					}
				}
			}
		} else curr = 0;

		colorBoxes(curr);
	}
}