#ifndef BLOCKS_H
#define BLOCKS_H
#include "Object.h"

class Blocks : public Object {
public:
	Blocks(float x, float y, float width, float height, Color color, bool is_especial = false, bool is_especial_n = false, bool is_especial_nd = false, bool is_special_pts = false);
	bool isSpecialBlock() const {return es_especial;};
	bool isSpecialNivel() const {return es_especial_nivel;};
	bool isSpecialNivel_dos() const {return es_especial_nivel_d;};
	bool isSpecialPts() const {return es_especial_pts;};
	void MoverAbajo(int distancia);

	
	void ReiniciarContadorColisiones(){contador_colisiones = 0;};
	void aumentarContadorColisiones(){contador_colisiones++;}
	int ObtenerContadorColisiones(){ return contador_colisiones;};
	
	FloatRect getGlobalBounds() const { return b_shape.getGlobalBounds(); }
	
private:
	bool es_especial;  int contador_colisiones;
	bool es_especial_nivel;
	bool es_especial_nivel_d;
	bool es_especial_pts;
};

#endif

