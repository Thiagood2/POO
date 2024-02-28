#ifndef GAMEWON_H
#define GAMEWON_H
#include "Scene.h"
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
using namespace std;

class GameWon : public Scene {
public:
	GameWon();
	void Update (Game &g,  Event &e);
	void Draw (RenderWindow & window);
	void MoveUp ( );
	void MoveDown ( );
private:
	Text Game_won; Font m_font;
	string m_score; Text score_text;
	vector<Text>option;
	
	
	SoundBuffer sonido_win; sf::Sound s_win;
	int max_items = 2;
	int selectitem;
};

#endif

