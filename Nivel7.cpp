#include "Nivel7.h"
#include "GameWon.h"
#include "Menu.h"
#include "GameOver.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Nivel1.h"

Nivel7::Nivel7() {
	m_ball.IncrementarVelocidad(incremento_velocidad++);
	m_ball.setBallMoving(false);
	
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
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		g.SetScene(new Menu());
		m_stats.ResetStats();
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Space)){
		m_ball.setBallMoving(true);
		m_stats.CambiarColores();
		m_stats.draw_text(false);
	}
	
	
	if(m_ball.Colisiona(m_player)){
		pl_pe.play();
		m_ball.Rebotar(m_player.DimensionesPlayer());
	}
	
	for(auto it = m_blocks.begin();it!=m_blocks.end();it++){
		if(m_ball.Colisiona(*it)){
			bl_pl.play();
			m_stats.aumentarpuntaje(25);
			m_blocks.erase(it);
			m_ball.Rebotar();
			break;
		}
	}
	
	if(m_blocks.empty()){
		g.SetScene(new Nivel1());
	}
	
	if(m_ball.falling()){
		m_stats.DecrementarVida();
	}
	
	if(m_stats.VerVidas() == 0){
		m_stats.GuardarScore(m_stats.MostrarPuntajeTotal());
		m_stats.ResetStats();
		g.SetScene(new GameOver());
	}
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
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

