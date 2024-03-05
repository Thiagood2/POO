#include "Nivel3.h"
#include "Game.h"
#include "Menu.h"
#include "Ball.h"
#include "Stats.h"
#include "GameOver.h"
#include "Nivel1.h"
#include "Nivel4.h"
#include <iostream>
#include "Nivel5.h"
using namespace std;

Nivel3::Nivel3() {
	
	this->ManejoVelocidadPelota();
	
	///Cuadros concentricos
	int centerX = columnCount / 2.5;   /// Se calcula la coordenada x del centro de la matriz de bloques
	int centerY = rowCount / 2;   /// Se calcula la coordenada y del centro de la matriz de bloques
	int maxDistance = max(centerX, centerY);
	
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j < columnCount; ++j) {
			int distance = std::max(abs(centerX - j), abs(centerY - i));    /// Se calcula la distancia de la posición actual al centro 
			if (distance % 2 == 0) {
				float x = j * (blockWidth + 6.f) + 50.f;
				float y = i * (blockHeight + 6.f) + 5.f;
				this->ProbabilidadesNivelesImpares(x,y);
			}
		}
	}
	
	bloques_totales = m_blocks.size();
	
}


void Nivel3::Update(Game &g){
	
	
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ManejoColisionesNivelImpar(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
	this->ChequeoTransicion(g); /// Manejo de transicion, si se gana, se pasa de nivel
	
	this->ManejoGameOver(g); /// Manejo de vidas y escena gameover
	
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
}

void Nivel3::ChequeoTransicion(Game &g){
	if(m_blocks.empty() or contador_bloques_normales ==  (bloques_totales - contador_bloques_special)){ /// EL nivel termina cuando no hay bloques, o cuando se rompen todos los bloques normales
		g.SetScene(new Nivel4());
	}
}

void Nivel3::ColisionesEspeciales(Game &g, Blocks m_bloque){
	if (m_bloque.isSpecialNivel()) {         /// Bloque especial de Nivel (Saltea 1)
		bl_pl.play();		 			/// Musica de choque de pelota-bloque (ladrillo)
		m_stats.aumentarpuntaje(100);
		m_ball.Rebotar();
		m_stats.IncrementarNivel();
		g.SetScene(new Nivel4());
	}
	
	/// Bloque especial Nivel (Saltea 2)
	if(m_bloque.isSpecialNivel_dos()){
		bl_pl.play();				/// Musica de choque de pelota-bloque (ladrillo)
		m_stats.aumentarpuntaje(200);
		m_ball.Rebotar();
		m_stats.IncrementarDobleNivel();
		g.SetScene(new Nivel5());
	}  
	
}



void Nivel3::Draw(RenderWindow &w){
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}


