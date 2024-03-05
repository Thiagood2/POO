#include "Nivel6.h"
#include "Stats.h"
#include "Menu.h"
#include "GameOver.h"
#include "Nivel7.h"
#include "Nivel1.h"

Nivel6::Nivel6() {
	this->ManejoVelocidadPelota();
	m_player.CambiarDimensiones(40,20); /// Cambia las dimensiones de la paleta

	/// Bloques aleatorios
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j < columnCount; ++j) {
			if (rand() % 100 < 40) {    /// Probabilidad del 40% de que haya un bloque
				float x = j * (blockWidth + 6.f) + 5.f;
				float y = i * (blockHeight + 6.f) + 5.f;
				this->ProbabilidadesNivelesPares(x,y);
			}
		}
	}
	
	bloques_totales = m_blocks.size();
	
}

void Nivel6::Update(Game &g){
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ManejoColisionesNivelPar(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
	this->ChequeoTransicion(g); /// Manejo de transicion, si se gana, se pasa de nivel
	
	this->ManejoGameOver(g); /// Manejo de vidas y escena gameover
	
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel6::ChequeoTransicion(Game &g){
	if(m_blocks.empty() or contador_bloques_normales ==  (bloques_totales - contador_bloques_special)){ /// EL nivel termina cuando no hay bloques, o cuando se rompen todos los bloques normales
		g.SetScene(new Nivel7());
	}
}

void Nivel6::ColisionesEspeciales(Game &g, Blocks m_bloque){
	if (m_bloque.isSpecialNivel()) {         /// Bloque especial de Nivel (Saltea 1)
		bl_pl.play();		 /// Musica de choque de pelota-bloque (ladrillo)
		m_stats.aumentarpuntaje(100);
		m_ball.Rebotar();
		m_stats.IncrementarNivel();
		g.SetScene(new Nivel7());
	}
	
	/// Bloque especial Nivel (Saltea 2)
	if(m_bloque.isSpecialNivel_dos()){
		bl_pl.play();				/// Musica de choque de pelota-bloque (ladrillo)
		m_stats.aumentarpuntaje(200);
		m_ball.Rebotar();
		m_stats.IncrementarDobleNivel();
		g.SetScene(new Nivel1());
	} 
}



void Nivel6::Draw(RenderWindow &w){
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}

