#include "Nivel2.h"
#include "Game.h"
#include "Menu.h"
#include "Nivel3.h"
#include "GameOver.h"
#include "Nivel1.h"

Nivel2::Nivel2() {
	
	m_ball.IncrementarVelocidad(2.f);
	m_ball.setBallMoving(false);
	
	m_stats.IncrementarNivel();
	
	
	///Escalera
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j <= i; ++j) {
			float x = j * (blockWidth + 6.f) + 5.f;
			float y = i * (blockHeight + 6.f) + 5.f;
				
				
				bool is_special = (rand()% 40 == 0); /// Probabilidad 1 / 20 de bloque especial puntos
				
				if(is_special){
					m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Yellow,true,false);
				}else{
					m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Cyan);
				}
			}
		}
	}
	


void Nivel2::Update(Game &g){
	
	
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
		m_ball.Rebotar(m_player.DimensionesPlayer());
	}
	
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ){
		if (m_ball.Colisiona(*it)) {
			if (it->isSpecialBlock()) {		/// Si colisiona con bloque especial pasa esto.. {
				m_stats.aumentarpuntaje(70);
				m_stats.IncrementarVidas();
			} 	
			else { 							/// Si no es especial el bloque pasa esto..
				m_stats.aumentarpuntaje(25);
			}
			m_ball.Rebotar();
			it = m_blocks.erase(it); /// Avanza el iterador después de eliminar el bloque
		} else {
			++it; /// Avanza al siguiente bloque si no hay colisión
		}
	}
	
	if(m_blocks.empty()){
		g.SetScene(new Nivel3());
		
	}
	
	if(m_ball.falling()){
		m_stats.decrementar_vidas(1);
	}
	
	if(m_stats.VerVidas() == 0){
		m_stats.GuardarScore(m_stats.MostrarPuntajeTotal());
		g.SetScene(new GameOver());
	}
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel2::Draw(RenderWindow &w){
	w.clear({0,0,0});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}

