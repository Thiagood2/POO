#include "Nivel7.h"

#include "Menu.h"
#include "GameOver.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Nivel1.h"
#include "Nivel2.h"

Nivel7::Nivel7() {
	
	this->ManejoVelocidadPelota();
	
	for (int i = 0; i < rowCount-5; ++i) { 
		if (i%2!=0){ /// Si la fila es par se colocan los bloques verticales
			for (int j = 0; j < columnCount+4; ++j) {
				i--;
				float x = j * ((blockWidth-54) + 34.f) + 40.f;
				float y = i * (blockHeight + 36) + 34.f;
				i++;
				this->ProbabilidadesNivelesImpares(x,y,blockWidth-54,blockHeight+54);
			}
		}else{ /// Caso contrario, se colocaran horizontales
			for (int j = 0; j < columnCount-3; ++j) {
				float x = j * ((blockWidth-54) + 88.f) + 40.f;
				float y = i * (blockHeight + 36) + 4.f;
				this->ProbabilidadesNivelesImpares(x,y);
			}
		}
	}
}

void Nivel7::Update (Game &g) {
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ManejoColisionesNivelImpar(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
	this->ChequeoTransicion(g); /// Manejo de transicion, si se gana, se pasa de nivel
	
	this->ManejoGameOver(g); /// Manejo de vidas y escena gameover
	
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel7::ChequeoTransicion(Game &g){
	if(m_blocks.empty()){
		g.SetScene(new Nivel1());
	}
}

void Nivel7::ColisionesEspeciales(Game &g, Blocks m_bloque){
	if (m_bloque.isSpecialNivel()) {         /// Bloque especial de Nivel (Saltea 1)
		bl_pl.play();		 /// Musica de choque de pelota-bloque (ladrillo)
		m_stats.aumentarpuntaje(100);
		m_ball.Rebotar();
		m_stats.IncrementarNivel();
		g.SetScene(new Nivel1());
	}
	
	/// Bloque especial Nivel (Saltea 2)
	if(m_bloque.isSpecialNivel_dos()){
		bl_pl.play();				/// Musica de choque de pelota-bloque (ladrillo)
		m_stats.aumentarpuntaje(200);
		m_ball.Rebotar();
		m_stats.IncrementarDobleNivel();
		g.SetScene(new Nivel2());
	} 
}



void Nivel7::Draw (RenderWindow &w) {
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}

