#include "Nivel.h"

Nivel::Nivel() {
	bloq_pelota.loadFromFile("break.wav"); /// Musica de pelota - bloque(ladrillo)
	bl_pl.setBuffer(bloq_pelota);
	
	
	paleta_pelota.loadFromFile("bounce.wav"); /// Musica de paleta - pelota 
	pl_pe.setBuffer(paleta_pelota);
	
	
	musica_principal.openFromFile("musica.ogg"); /// Musica principal del juego
	musica_principal.play();
	musica_principal.setLoop(true);
	
}

int incremento_velocidad = 0;

