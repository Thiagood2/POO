#include "Nivel4.h"
#include "Menu.h"
#include "Ball.h"
#include "Stats.h"
#include "GameOver.h"
#include "Nivel5.h"
#include <iostream>

Nivel4::Nivel4() {
	m_ball.IncrementarVelocidad(incremento_velocidad++);
	m_ball.setBallMoving(false);
	
	m_stats.IncrementarNivel();
	
	
	/// Tablero de ajedrez
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j < columnCount; ++j) {
			if ((i + j) % 2 == 0) {   /// Se a�aden bloques en posiciones donde la suma de �ndices es par
				float x = j * (blockWidth + 6.f) + 5.f;
				float y = i * (blockHeight + 6.f) + 5.f;
				
				bool isSpecial = (rand () % 70 == 0); /// Probabilidad de 1 / 70 de ser especial el bloque nivel (Saltea 1)
				bool isSpecial_puntos = (rand()% 40 == 0); /// Probabilidad de 1 / 40 de ser especial  el bloque puntos
				bool isSpecial_menospts = (rand () % 50 == 0); /// Probabilidad 1 / 50 de ser especial el bloque puntos (resta 100 y 1 vida)
				
				if(isSpecial){
					m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color(255,0,128),false,true);
					contador_bloques_special++;
				}else{
					if(isSpecial_puntos){
						m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Yellow,true,false);
						contador_bloques_special++;
					}else{
						if(isSpecial_menospts){
							m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Blue,false,false,false,true);
							contador_bloques_special++;
						}else{
							m_blocks.emplace_back(x, y, blockWidth, blockHeight, Color::Black);
						}
						
					}
				}
			}
		}
	}
	bloques_totales = m_blocks.size();
}

void Nivel4::Update(Game &g){
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		g.SetScene(new Menu());
		incremento_velocidad = 0;
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
	
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ){
		if (m_ball.Colisiona(*it)) {
			if (it->isSpecialNivel()) {         /// Bloque especial de Nivel (Saltea 1)
				bl_pl.play();
				g.SetScene(new Nivel5());
				m_stats.aumentarpuntaje(100);
				m_ball.Rebotar();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			}
			
			/// Bloque especial de puntos
			if(it->isSpecialBlock()){
				bl_pl.play();
				m_stats.aumentarpuntaje(75);
				m_stats.IncrementarVidas();
				m_ball.Rebotar();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			} 
			
			/// Bloque especial de puntos (resta 100 y 1 vida)
			if(it->isSpecialPts()){
				m_stats.restarpuntaje(100);
				bl_pl.play();
				m_ball.Rebotar();
				m_stats.DecrementarVida();
				it = m_blocks.erase(it); /// Eliminar bloque especial
				continue; /// Continuar con el siguiente bloque
			} 
			
			/// Si no es especial el bloque pasa esto..
			bl_pl.play();
			contador_bloques_normales++;
			m_stats.aumentarpuntaje(25);
			m_ball.Rebotar();
			it = m_blocks.erase(it); /// Avanza el iterador despu�s de eliminar el bloque no especial
		} else {
			++it; /// Avanza al siguiente bloque si no hay colisi�n
		}
	}
	
	cout<<incremento_velocidad<<endl;
	
	if(m_blocks.empty() or contador_bloques_normales ==  (bloques_totales - contador_bloques_special)){ /// EL nivel termina cuando no hay bloques, o cuando se rompen todos los bloques normales
		g.SetScene(new Nivel5());
	}
	
	if(m_ball.falling()){
		m_stats.DecrementarVida();
	}
	
	if(m_stats.VerVidas() == 0){
		m_stats.GuardarScore(m_stats.MostrarPuntajeTotal());
		m_stats.ResetStats();
		incremento_velocidad = 0;
		g.SetScene(new GameOver());
	}
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
}



void Nivel4::Draw(RenderWindow &w){
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}
