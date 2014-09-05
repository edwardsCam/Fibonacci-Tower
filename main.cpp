#include <Windows.h>
#include <string.h>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <math.h>

#define WIDTH 1200
#define HEIGHT 600
#define phi ((sqrt(5) + 1)/2)
#define mlen (min(WIDTH, HEIGHT) - 100.0)
#define max_level 20

sf::RenderWindow window;

void makeSquare(float x, float y, float len) {
	sf::RectangleShape box;
	box.setPosition(x, y);
	sf::Vector2f s(len, len);
	box.setSize(s);
	window.draw(box);
	window.display();
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Fibonacci Tower");
	window.clear(sf::Color::Cyan);
	window.display();
	draw(1, 20.0, 20.0);

	while (true);
}