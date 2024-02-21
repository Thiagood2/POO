#include "Blocks.h"
#include <SFML/Graphics/RectangleShape.hpp>

Blocks::Blocks(float x, float y, float width, float height, Color color, bool is_especial, bool is_especial_n){
	
	
	b_shape.setSize(Vector2f(width,height));
	b_shape.setPosition(x,y);
	b_shape.setFillColor(color);
	b_shape.setOutlineThickness(1.f);
	b_shape.setOutlineColor(sf::Color::White);
	es_especial = is_especial;
	es_especial_nivel = is_especial_n;
}


