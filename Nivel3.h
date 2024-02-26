#ifndef NIVEL3_H
#define NIVEL3_H
#include "Player.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.h"
#include "Nivel.h"
#include <SFML/Window/Event.hpp>


class Nivel3 : public Nivel{
public:
	Nivel3();
	void Draw(RenderWindow &w) override;
	void Update(Game &g, Event &e) override;
	
private:
};

#endif

