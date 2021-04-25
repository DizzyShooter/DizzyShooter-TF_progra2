#include "Adversarios.h"
#include <iostream>

Adversarios::Adversarios() {}
Adversarios::Adversarios(int pini_f, int pini_c, int pfin_f, int pfin_c) :
	Personaje(pini_f, pini_c, pfin_f, pfin_c) {
	eliminar1 = false;
	eliminar2 = false;
}
Adversarios::~Adversarios() {}

void Adversarios::cambiar_eliminar_A1(bool nuevo) { eliminar1 = nuevo; }
bool Adversarios::retornar_eliminar_A1() { return eliminar1; }

void Adversarios::cambiar_eliminar_A2(bool nuevo) { eliminar2 = nuevo; }
bool Adversarios::retornar_eliminar_A2() { return eliminar2; }

void Adversarios::Mover_enemigo1(Graphics^ g, Bitmap^ img) {
	if (y + dy < 300 || y + dy + h > g->VisibleClipBounds.Bottom)
		dy = dy * -1;
	if (x + dx < 200 || x + dx + w > g->VisibleClipBounds.Right)
		dx = dx * -1;
	x += dx;
	y += dy;

	w = img->Width / 4;
	h = img->Height / 4;

	Dibujar(g, img);
}

void Adversarios::Mover_enemigo2(Graphics^ g, Bitmap^ img) {
	if (y + dy < 1 || y + dy + h > g->VisibleClipBounds.Bottom)
		dy = dy * -1;
	if (x + dx < 1 || x + dx + w > g->VisibleClipBounds.Right)
		dx = dx * -1;
	x += dx;
	y += dy;

	w = img->Width / 4;
	h = img->Height / 4;

	Dibujar(g, img);
}