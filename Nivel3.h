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
	void Update(Game &g) override;
	void ChequeoTransicion(Game &g) override;
	void ColisionesEspeciales(Game &g, Blocks m_bloque) override;
	
private:
};

#endif

