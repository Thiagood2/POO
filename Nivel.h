#ifndef NIVEL_H
#define NIVEL_H
#include "Scene.h"
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Blocks.h"
#include "Stats.h"
#include "Ball.h"
#include "Player.h"
#include <SFML/Window/Event.hpp>

class Nivel : public Scene {
public:
	Nivel();
	virtual void Update(Game &g, sf::Event &e) = 0;
	virtual void Draw(RenderWindow &window) = 0;
	virtual ~Nivel (){}; /// PREG A PROFE
	
protected:
	const int rowCount = 10;  /// Filas
	const int columnCount = 10;  /// Columnas
	const float blockWidth = 74.f;  /// Ancho de bloque
	const float blockHeight = 20.f;  /// Alto de bloque
	
	int contador_bloques_normales = 0;
	int contador_bloques_special = 0;
	
	int bloques_totales = 0;
	
	Ball m_ball; Player m_player;
	
	vector<Blocks>m_blocks;
};

#endif

