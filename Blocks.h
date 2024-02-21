#ifndef BLOCKS_H
#define BLOCKS_H
#include "Object.h"

class Blocks : public Object {
public:
	Blocks(float x, float y, float width, float height, Color color, bool is_especial = false, bool is_especial_n = false);
	bool isSpecialBlock() const {return es_especial;};
	bool isSpecialNivel() const {return es_especial_nivel;};
	
private:
	bool es_especial; 
	bool es_especial_nivel;
};

#endif

