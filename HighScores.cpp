#include "HighScores.h"
#include <fstream>
#include <sstream>
#include "Game.h"
#include "Menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include "Perfil.h"
#include <cstring>
using namespace std;

bool comparing_score(PlayerScore &a, PlayerScore &b){
	if (a.m_puntos != b.m_puntos) {
		return a.m_puntos > b.m_puntos; /// Compara por puntos si son diferentes
	} else {
		/// Si los puntos son iguales, compara por nombre
		return strcmp(a.m_name, b.m_name) < 0; /// Devuelve true si a.m_name es menor que b.m_name
	}
}


HighScores::HighScores() {
	
	
	m_font.loadFromFile("fuente_menu.ttf");

	ifstream archi_leer("Scores.dat",ios::binary);
	while (archi_leer.peek() != EOF) { /// Mientras no se llegue al final del archivo
		PlayerScore temp;
		/// Leer el struct PlayerScore del archivo binario
		archi_leer.read(reinterpret_cast<char*>(&temp), sizeof(PlayerScore));
		Scores.push_back(temp);
	}
	archi_leer.close();
	sort(Scores.begin(),Scores.end(),comparing_score);

	string puntos;
	ifstream archi_puntos("puntos.txt", ios::in);
	if (archi_puntos.is_open() && archi_puntos.peek() == ifstream::traits_type::eof()){
		puntos = "0";
	}else{
		archi_puntos>>puntos;
	}
	archi_puntos.close();

	PlayerScore jugador;
	strcpy(jugador.m_name, m_nombre.c_str());
	jugador.m_puntos = stoi(puntos);
	
	size_t length = strlen(jugador.m_name);  /// Se obtiene la longitud de la cadena copiada
	jugador.m_name[length] = '\0';   /// Se agrega el carácter nulo al final del arreglo después de la cadena copiada

	int cant = 0;
	int indice_a_eliminar;
	/// Busca los jugadores que necesitan ser reemplazados o eliminados
	for (size_t i = 0; i < Scores.size(); ++i) {
		if (strcmp(Scores[i].m_name, jugador.m_name) == 0 && comparing_score(jugador, Scores[i])) {
			indice_a_eliminar = i;
			cant++;
		}else{
			if (strcmp(Scores[i].m_name, jugador.m_name) == 0 && comparing_score(Scores[i],jugador)) {
				cant+=2;
			}
		}
	}

	/// Elimina los jugadores que necesitan ser reemplazados
	if(cant==1){
		auto it = Scores.begin() + indice_a_eliminar;
		Scores.erase(it);
		Scores.push_back(jugador);   /// Inserta el nuevo jugador
		sort(Scores.begin(), Scores.end(), comparing_score);
		/// Escribe los puntajes en el archivo
		ofstream archi_escribir("Scores.dat", ios::binary | ios::trunc);
		for (size_t i = 0; i < Scores.size(); ++i) {
			archi_escribir.write(reinterpret_cast<const char*>(&Scores[i]), sizeof(PlayerScore));
		}
		archi_escribir.close();  
	}
		
	if(cant==0){
		auto it = prev(Scores.end());
		if (comparing_score(jugador,*it)){
			Scores.push_back(jugador);
			sort(Scores.begin(),Scores.end(),comparing_score);
			Scores.pop_back();
			ofstream archi_escribir("Scores.dat",ios::binary|ios::trunc);
			for(int i=0;i<Scores.size();i++) { 
				archi_escribir.write(reinterpret_cast<char*>(&Scores[i]),sizeof(PlayerScore));
			}
			archi_escribir.close();
		}
	}
	
	draw_scores.resize(Scores.size());
	int var_y = 50;
	for(int i =0;i<Scores.size();i++){
		draw_scores[i].setFont(m_font);
		draw_scores[i].setCharacterSize(24);
		draw_scores[i].setPosition(250,var_y);
		draw_scores[i].setString(to_string(i+1)+ " " + Scores[i].m_name + " " + to_string(Scores[i].m_puntos));
		var_y +=105;
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
		ofstream archi("puntos.txt", ios::out);
		int puntos = 0;
		if(archi.is_open()){
			archi<<puntos;
			archi.close();
		}
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
