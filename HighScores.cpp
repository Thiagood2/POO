#include "HighScores.h"
#include <fstream>
#include <sstream>
#include "Game.h"
#include "Menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include "Perfil.h"
using namespace std;

bool comparing_score(PlayerScore &a, PlayerScore &b){
	return a.m_puntos>b.m_puntos;
}


HighScores::HighScores() {
	m_font.loadFromFile("fuente_menu.ttf");
	
	string puntos;
	ifstream archi_puntos("puntos.txt", ios::in);
	archi_puntos>>puntos;
	archi_puntos.close();
	
	PlayerScore jugador;
	jugador.m_name = m_nombre;
	jugador.m_puntos = stoi(puntos);
	
	ofstream archi("Scores.dat",ios::binary|ios::app);
	archi.write(reinterpret_cast<char*>(&jugador),sizeof(PlayerScore));
	archi.close();
	
	ifstream archi_leer ("Scores.dat",ios::binary);
	
	while (archi_leer.peek() != EOF) { /// Mientras no se llegue al final del archivo
		PlayerScore temp;
		/// Leer el struct PlayerScore del archivo binario
		archi_leer.read(reinterpret_cast<char*>(&temp), sizeof(PlayerScore));
		Scores.push_back(temp);
	}
	
	sort(Scores.begin(),Scores.end(),comparing_score);
	draw_scores.resize(Scores.size());
	
	int var_y = 50;
	
	for(int i =0;i<Scores.size();i++){
		draw_scores[i].setFont(m_font);
		draw_scores[i].setCharacterSize(24);
		draw_scores[i].setPosition(300,var_y);
		draw_scores[i].setString(to_string(i+1)+ " " + Scores[i].m_name + " " + to_string(Scores[i].m_puntos));
		var_y +=70;
	}
	
	volver_menu.setFont(m_font);
	volver_menu.setCharacterSize(16);
	volver_menu.setFillColor(Color::Green);
	volver_menu.setPosition(540,570);
	volver_menu.setString("<volver al menu>");
	
}

void HighScores::Update(Game &g){
	
}


void HighScores::ProcesarEventos(Game &g, Event &ev){
	
	
	if(ev.type== Event::KeyPressed and ev.key.code == Keyboard::Return){
		g.SetScene(new Menu());
	}
}

void HighScores::Draw(RenderWindow &w){
	w.clear({0,0,0});
	w.draw(volver_menu);
	for(auto x : draw_scores){
		w.draw(x);
	}
}
