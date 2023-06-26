//для работы с камерой вида

#include "SFML/Graphics.hpp"

using namespace sf;

sf::View view;

View getCoordinatPlayerView(float x, float y) {
	float tempX = x; float tempY = 360;
	if (x < 640) tempX = 640;
	if (x > 1920) tempX = 1920;
	view.setCenter(tempX, tempY);
	return view;
}