#include <SFML/Graphics.hpp>

using namespace sf;

sf::View view;

View getCoordinatView(float x, float y) {
	view.setCenter(x + 100, y);
	return view;
}