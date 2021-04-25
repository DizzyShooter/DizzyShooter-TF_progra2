#pragma once
#include "Personaje.h"
class Adversarios : public Personaje {
private:
	bool eliminar1, eliminar2;

public:
	Adversarios();
	Adversarios(int pini_f, int pini_c, int pfin_f, int pfin_c);
	~Adversarios();

	void Mover_enemigo1(Graphics^ g, Bitmap^ img);
	void Mover_enemigo2(Graphics^ g, Bitmap^ img);

	void cambiar_eliminar_A1(bool nuevo);
	bool retornar_eliminar_A1();

	void cambiar_eliminar_A2(bool nuevo);
	bool retornar_eliminar_A2();
};