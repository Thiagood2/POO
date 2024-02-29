#ifndef PERFIL_H
#define PERFIL_H
#include "Scene.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "InputText.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Perfil : public Scene {
public:
	Perfil();
	void Draw (RenderWindow & window);
	void Update (Game & g);
	void ProcesarEventos (Game & g, Event & ev);
private:
	Text m_text; Font m_font; string m_nombre;
	InputText m_input_nombre;
	Sprite s_logo;
	Texture t_logo;
};

#endif

