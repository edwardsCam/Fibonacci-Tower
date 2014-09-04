#include <Windows.h>
#include <string.h>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#define WIDTH 800
#define HEIGHT 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	sf::RenderWindow window;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Fibonacci Tower");
	window.clear(sf::Color::Cyan);
	window.display();
	while (true);
}