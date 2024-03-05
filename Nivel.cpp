#include "Nivel.h"
#include "Menu.h"
#include "GameOver.h"
#include "Player.h"
#include <fstream>
#include <iostream>
using namespace std;

Nivel::Nivel() {
	bloq_pelota.loadFromFile("break.wav"); /// Musica de pelota - bloque(ladrillo)
	bl_pl.setBuffer(bloq_pelota);
	
	
	paleta_pelota.loadFromFile("bounce.wav"); /// Musica de paleta - pelota 
	pl_pe.setBuffer(paleta_pelota);
	
	
	musica_principal.openFromFile("musica.ogg"); /// Musica principal del juego
	musica_principal.play();
	musica_principal.setLoop(true);
	
}
void Nivel::ManejoInput(Game &g){
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		m_stats.ResetStats();
		incremento_velocidad = 0; /// Eventos generales para todos los niveles
		g.SetScene(new Menu());
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Space)){ /// Eventos generales para todos los niveles
		m_ball.setBallMoving(true);
		m_stats.CambiarColores();
		m_stats.draw_text(false);
	}
}

void Nivel::ManejoGameOver(Game &g){
	if(m_stats.VerVidas() == 0){ /// Si no hay vidas, entonces se va a la scena gameover y se guarda el puntaje en block de notas
		m_stats.GuardarScore(m_stats.obtenerpuntaje());
		m_stats.ResetStats();
		incremento_velocidad = 0;
		g.SetScene(new GameOver());
	}
}

void Nivel::ManejoPelota(){
	if(m_ball.Colisiona(m_player)){ /// Colision pelota-paleta
		pl_pe.play(); /// Musica de colision pelota-paleta
		m_ball.Rebotar(m_player.DimensionesPlayer()); 
	}
	
	if(m_ball.PasoLimites()){  /// Si se cae la pelota, 1 vida menos
		m_stats.DecrementarVida();
	}
}

void Nivel::ManejoColisionesNivelImpar(Game &g){
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ) {
		if (m_ball.Colisiona(*it)) {
			if (it->isSpecialNivel() or it->isSpecialNivel_dos()) { /// Bloques especiales (niveles)
				
				it->aumentarContadorColisiones(); /// Contador de colisiones
				bl_pl.play();
				
				if(it->ObtenerContadorColisiones() == 3){ /// Si choca 3 veces, recien se rompe el bloque
					ColisionesEspeciales(g, *it);  /// Manejo de bloques especiales (niveles)
					it = m_blocks.erase(it); 
					continue;
				
				}else{
					m_ball.Rebotar();
					++it;
					continue;
				}
				
			} else {
				/// Bloque especial de puntos
				if (it->isSpecialBlock()) {
					
					it->aumentarContadorColisiones();
					bl_pl.play();
					
					if (it->ObtenerContadorColisiones() == 2) {
						m_stats.aumentarpuntaje(75);
						m_stats.IncrementarVidas();
						m_ball.Rebotar();
						it = m_blocks.erase(it);
						continue;
					} else {
						m_ball.Rebotar();
						++it;
						continue;
					}
				} else {
					 /// Bloques normales
					bl_pl.play();
					contador_bloques_normales++;
					m_stats.aumentarpuntaje(25);
					m_ball.Rebotar();
					it = m_blocks.erase(it);
					continue;
				}
			}
		} else {
			++it;
		}
		
		/// Reiniciar el contador cuando llegue a 3
		for (auto &block : m_blocks) {
			if (block.ObtenerContadorColisiones() == 3) {
				block.ReiniciarContadorColisiones();
			}
		}
	}
	
}

void Nivel::ManejoColisionesNivelPar(Game &g){
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ) {
		if (m_ball.Colisiona(*it)) {
			if (it->isSpecialNivel() or it->isSpecialNivel_dos()) { /// Bloques especiales (niveles)
				
				it->aumentarContadorColisiones(); /// Contador de colisiones
				bl_pl.play();
				
				if(it->ObtenerContadorColisiones() == 3){ /// Si choca 3 veces, recien se rompe el bloque
					ColisionesEspeciales(g, *it);  /// Manejo de bloques especiales (niveles)
					it = m_blocks.erase(it); 
					continue;
					
				}else{
					m_ball.Rebotar();
					++it;
					continue;
				}
				
			} else {
				/// Bloque especial de puntos
				if (it->isSpecialBlock()) {
					
					it->aumentarContadorColisiones();
					bl_pl.play();
					
					if (it->ObtenerContadorColisiones() == 2) {
						m_stats.aumentarpuntaje(75);
						m_stats.IncrementarVidas();  /// Manejo de bloques especial (puntos)
						m_ball.Rebotar();
						it = m_blocks.erase(it);
						continue;
					} else {
						m_ball.Rebotar();
						++it;
						continue;
					}
				} else {
					if(it->isSpecialPts()){ /// Bloque especial Resta puntos y vida
						
						it->aumentarContadorColisiones();
						bl_pl.play();
						
						
						if(it->ObtenerContadorColisiones()==2){
							m_stats.DecrementarVida();
							m_stats.aumentarpuntaje(-100);
							m_ball.Rebotar();
							it = m_blocks.erase(it);
							continue;
						}else{
							m_ball.Rebotar();
							++it;
							continue;
						}
					}else{
						/// Bloques normales
						bl_pl.play();
						contador_bloques_normales++;
						m_stats.aumentarpuntaje(25);
						m_ball.Rebotar();
						it = m_blocks.erase(it);
						continue;
					}
				}
			}
		} else {
			++it;
		}
		
		/// Reiniciar el contador cuando llegue a 3
		for (auto &block : m_blocks) {
			if (block.ObtenerContadorColisiones() == 3) {
				block.ReiniciarContadorColisiones();
			}
		}
	}
}


void Nivel::ProbabilidadesNivelesImpares(float &x, float &y, float width, float height){
	
	bool isSpecial = (rand () % 60 == 0); /// Probabilidad de 1 / 60 de ser especial el bloque nivel (Saltea 1)
	bool isSpecial_puntos = (rand()% 30 == 0); /// Probabilidad de 1 / 30 de ser especial  el bloque puntos
	bool isSpecial_nivel_d = (rand () % 110 == 0); /// Probabilidad 1 / 110 de ser especial el bloque Nivel (saltea 2)
	
	
	if(width == 0){
		if(isSpecial){
			m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color(255,0,128),false,true);
			contador_bloques_special++;
		}else{
			if(isSpecial_puntos){
				m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Yellow,true,false);
				contador_bloques_special++;
			}else{
				if(isSpecial_nivel_d){
					m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color(255,165,0),false,false,true);
					contador_bloques_special++;
				}else{
					m_blocks.emplace_back(x, y, blockWidth, blockHeight, Color::White);
				}
			}	
		}
	}else{
		
		if(isSpecial){
			m_blocks.emplace_back(x,y,width,height,Color(255,0,128),false,true);
			contador_bloques_special++;
		}else{
			if(isSpecial_puntos){
				m_blocks.emplace_back(x,y,width,height,Color::Yellow,true,false);
				contador_bloques_special++;
			}else{
				if(isSpecial_nivel_d){
					m_blocks.emplace_back(x,y,width,height,Color(255,165,0),false,false,true);
					contador_bloques_special++;
				}else{
					m_blocks.emplace_back(x, y, width,height, Color::White);
				}
			}	
		}
	}
}


void Nivel::ProbabilidadesNivelesPares(float &x, float &y){
	
	bool isSpecial = (rand () % 70 == 0); /// Probabilidad de 1 / 70 de ser especial el bloque nivel (Saltea 1)
	bool isSpecial_puntos = (rand()% 40 == 0); /// Probabilidad de 1 / 40 de ser especial  el bloque puntos
	bool isSpecial_nivel_d = (rand () % 110 == 0); /// Probabilidad 1 / 110 de ser especial el bloque Nivel (saltea 2)
	bool isSpecial_menospts = (rand () % 40 == 0); /// Probabilidad 1 / 40 de ser especial el bloque puntos (resta 100 y 1 vida)
	
	if(isSpecial){
		m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color(255,0,128),false,true);
		contador_bloques_special++;
	}else{
		if(isSpecial_puntos){
			m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Yellow,true,false);
			contador_bloques_special++;
		}else{
			if(isSpecial_nivel_d){
				m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color(255,165,0),false,false,true);
				contador_bloques_special++;
			}else{
				if(isSpecial_menospts){
					m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Blue,false,false,false,true);
					contador_bloques_special++;
				}else{
					m_blocks.emplace_back(x, y, blockWidth, blockHeight, Color::White);
				}
			}
		}
	}
	
}

void Nivel::ManejoVelocidadPelota(){
	m_ball.setBallMoving(false);
	m_ball.IncrementarVelocidad(incremento_velocidad++);
}

int incremento_velocidad = 0;

