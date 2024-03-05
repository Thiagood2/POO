#include "Nivel5.h"
#include "Stats.h"
#include "Menu.h"
#include "GameOver.h"
#include "Nivel6.h"
#include "Nivel7.h"
Nivel5::Nivel5() {
	this->ManejoVelocidadPelota();
	m_player.CambiarDimensiones(60,20); /// Cambia las dimensiones de la paleta
	
	
	/// Tamanios bloques aleatorios
	
	srand(time(nullptr));   /// Inicializa la semilla para generar números aleatorios
	int minHeight = 3;
	int maxHeight = 20;
	int minWidth = 20;
	int maxWidth = 50;
	
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j < columnCount; ++j) {
			float x = j * (blockWidth + 6.f) + 5.f;
			float y = i * (blockHeight + 10.f) + 5.f;
			float height = (rand() % maxHeight) + minHeight; /// Altura aleatoria entre minHeight y maxHeight
			float Width = (rand() % maxWidth) + minWidth; /// Anchura aleatoria entre minWidtht y maxWidth
			
			this->ProbabilidadesNivelesImpares(x,y,Width,height);
		}
	}
	
	bloques_totales = m_blocks.size();
}


void Nivel5::Update(Game &g){
	this->ManejoInput(g); /// Manejo de  todos los Inputs de el Juego
	
	this->ManejoPelota(); /// Manejo de colisiones pelota - paleta y tema limites
	
	this->ManejoColisionesNivelImpar(g); /// Manejo de Colisiones pelota - ladrillo y bloques especiales
	
	this->ChequeoTransicion(g); /// Manejo de transicion, si se gana, se pasa de nivel
	
	this->ManejoGameOver(g); /// Manejo de vidas y escena gameover
	
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel5::ChequeoTransicion(Game &g){
	if(m_blocks.empty() or contador_bloques_normales ==  (bloques_totales - contador_bloques_special)){ /// EL nivel termina cuando no hay bloques, o cuando se rompen todos los bloques normales
		g.SetScene(new Nivel6());
	}
}

void Nivel5::ColisionesEspeciales(Game &g, Blocks m_bloque){
	if (m_bloque.isSpecialNivel()) {         /// Bloque especial de Nivel (Saltea 1)
		bl_pl.play();		 /// Musica de choque de pelota-bloque (ladrillo)
		m_stats.aumentarpuntaje(100);
		m_ball.Rebotar();
		m_stats.IncrementarNivel();
		g.SetScene(new Nivel6());
	}
	
	/// Bloque especial Nivel (Saltea 2)
	if(m_bloque.isSpecialNivel_dos()){
		bl_pl.play();				/// Musica de choque de pelota-bloque (ladrillo)
		m_stats.aumentarpuntaje(200);
		m_ball.Rebotar();
		m_stats.IncrementarDobleNivel();
		g.SetScene(new Nivel7());
	} 
}




void Nivel5::Draw(RenderWindow &w){
	w.clear({20,20,20});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}
