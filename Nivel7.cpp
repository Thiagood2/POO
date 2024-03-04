#include "Nivel7.h"

#include "Menu.h"
#include "GameOver.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Nivel1.h"

Nivel7::Nivel7() {
	m_ball.IncrementarVelocidad(incremento_velocidad++);
	m_stats.IncrementarNivel();
	
	
	Color colors[] = {Color::Red, Color::Green, Color(158,71,112), Color(172,153,105), Color::Magenta, Color::Cyan}; /// Vector de colores
	
	for (int i = 0; i < rowCount-2; ++i) { /// Ladrillos cambia colores
		if (i%2!=0){
			for (int j = 0; j < columnCount+4; ++j) {
				i--;
				float x = j * ((blockWidth-54) + 34.f) + 40.f;
				float y = i * (blockHeight + 36) + 34.f;
				m_blocks.emplace_back(x, y, blockWidth - 54, blockHeight + 54, Color::White);
				i++;
			}
		}else{
			for (int j = 0; j < columnCount-3; ++j) {
				Color blockColor = colors[(i + j) % 6];
				float x = j * ((blockWidth-54) + 88.f) + 40.f;
				float y = i * (blockHeight+36) +4.f;
				m_blocks.emplace_back(x, y, blockWidth , blockHeight , blockColor);
			}
		}
	}
}

void Nivel7::Update (Game &g) {
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ColisionesPelotaLadrillo(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
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

void Nivel7::ColisionesPelotaLadrillo (Game &g){
	for(auto it = m_blocks.begin();it!=m_blocks.end();it++){
		if(m_ball.Colisiona(*it)){
			bl_pl.play();
			m_stats.aumentarpuntaje(25);
			m_blocks.erase(it);
			m_ball.Rebotar();
			break;
		}
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

