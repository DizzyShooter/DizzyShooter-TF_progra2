#include "Configuracion.h"
#include <iostream>

Configuracion::Configuracion() {
	fin_juego = false;
	start = clock();
	tiempo = 30;
	cant1 = new int; cant2 = new int; 
	*cant1 = 0; *cant2 = 0; 
	
	ind2 = 1 + rand() % 9;
	if (ind2 < 5)
		ind1 = 1 + rand() % 5;
	else if (ind2 >= 5)
		ind1 = (1 + rand() % 9) - ind2;

	Start();
}

Configuracion::~Configuracion() {
	delete objJ, cant1, cant2;
	delete[] arrA1;
	delete[] arrA2; 
}

void Configuracion::Cambiar_JugadorDY(int dy) { objJ->cambiar_dy(dy); }
void Configuracion::Cambiar_JugadorDX(int dx) { objJ->cambiar_dx(dx); }
void Configuracion::cambiar_Tiempo(int nuevo) { tiempo = nuevo; }
void Configuracion::cambiar_Game_over(bool nuevo) { nuevo = fin_juego; }
void Configuracion::cambiar_mundo(int n) { mundo = n; }

int Configuracion::retornar_mundo() { return mundo; }
int Configuracion::retornar_cantidad_Adversarios() { return *cant2; }
int Configuracion::retornar_Tiempo() { return tiempo; }

void Configuracion::Start() {
	//Jugador
	objJ = new Jugador(0, 0, 3, 3); 
	objJ->cambiar_sf(0);
	objJ->cambiar_sc(0);
	objJ->cambiar_x(15);
	objJ->cambiar_y(25);

	//Adversarios 
	for (int i = 0; i < ind1; i++) //saludables
		Insertar_Adversarios1();

	for (int i = 0; i < ind2; i++)
		Insertar_Adversarios2(); 

	//Vehiculos 
	objAmb = new Vehiculos(0, 0, 1, 1);
	objAmb->cambiar_sf(0);
	objAmb->cambiar_sc(0);
	objAmb->cambiar_dx(8);
	objAmb->cambiar_dy(8);
	objAmb->cambiar_x(50);
	objAmb->cambiar_y(50);
}

void Configuracion::Insertar_Adversarios1() { //saludables
	Adversarios** copia = new Adversarios * [*cant1 + 1];

	for (int i = 0; i < *cant1; i++)
		copia[i] = arrA1[i];

	copia[*cant1] = new Adversarios(0, 0, 3, 3);
	copia[*cant1]->cambiar_sf(0);
	copia[*cant1]->cambiar_sc(0);
	copia[*cant1]->cambiar_dy(5);
	copia[*cant1]->cambiar_dx(5);
	copia[*cant1]->cambiar_x(300 + rand() % 100);
	copia[*cant1]->cambiar_y(300 + rand() % 100);

	*cant1 = *cant1 + 1;
	arrA1 = copia;
}

void Configuracion::Insertar_Adversarios2() {
	Adversarios** copia = new Adversarios * [*cant2 + 1];

	for (int i = 0; i < *cant2; i++)
		copia[i] = arrA2[i];

	copia[*cant2] = new Adversarios(0, 0, 3, 3);
	copia[*cant2]->cambiar_sf(0);
	copia[*cant2]->cambiar_sc(0);
	copia[*cant2]->cambiar_dy(12);
	copia[*cant2]->cambiar_dx(12);
	copia[*cant2]->cambiar_x(100 + rand() % 300);
	copia[*cant2]->cambiar_y(100 + rand() % 300);

	*cant2 = *cant2 + 1;
	arrA2 = copia;
}

void Configuracion::Dinamica_Configuracion(Graphics^ g, Bitmap^ img_jugador, Bitmap^ img_mensaje, Bitmap^ img_enemigo, Bitmap^ img_amb) {
	//Movimiento 
	objJ->Mover_Jugador(g, img_jugador, img_mensaje);

	Mover_Enemigos1(g, img_enemigo);
	Mover_Enemigos2(g, img_enemigo);

	objAmb->Mover_Vehiculos(g, img_amb);

	Colisiones();

	if (clock()-start>=(double)CLOCKS_PER_SEC) {
		tiempo--;
		start = clock();
	}
	g->DrawString("Tiempo : " + tiempo.ToString()+ "  Vidas: "+objJ->retornar_vidas().ToString(), gcnew Font("Arial", 16), Brushes::Black, 0, 0);
}

void Configuracion::Colisiones() {
	//Colisión
	for (int i = 0; i < objJ->retornar_cantidad(); i++)
		for (int j = 0; j < *cant1; j++)
			if (Colision(objJ->retornar_Mensaje(i), arrA1[j])) {
				objJ->retornar_Mensaje(i)->cambiar_eliminar_msg(true);
				//arrA1[j]->cambiar_eliminar_A1(true);
			}

	for (int i = 0; i < objJ->retornar_cantidad(); i++)
		for (int j = 0; j < *cant2; j++)
			if (Colision(objJ->retornar_Mensaje(i), arrA2[j])) {
				objJ->retornar_Mensaje(i)->cambiar_eliminar_msg(true);
				arrA2[j]->cambiar_eliminar_A2(true);
			}
}

void Configuracion::Mover_Jugador(tecla_pulsada tecla) {
	switch (tecla) {
	case (tecla_pulsada::abajo):
		objJ->cambiar_sf(0);
		break;
	case (tecla_pulsada::izquierda):
		objJ->cambiar_sf(1);
		break;
	case (tecla_pulsada::derecha):
		objJ->cambiar_sf(2);
		break;
	case (tecla_pulsada::arriba):
		objJ->cambiar_sf(3);
		break;
	}

	objJ->cambiar_direccion(tecla);
}

void Configuracion::Mover_Enemigos1(Graphics^ g, Bitmap^ img_enemigo1) {
	int cantidad = 0;
	for (int i = 0; i < *cant1; i++)
		cantidad += arrA1[i]->retornar_eliminar_A1() ? 1 : 0;

	Adversarios** copia = new Adversarios * [*cant1 - cantidad];
	int j = 0;
	for (int i = 0; i < *cant1; i++) {
		if (!arrA1[i]->retornar_eliminar_A1()) {
			copia[j] = arrA1[i];
			j++;
		}
	}
	*cant1 = *cant1 - cantidad;
	arrA1 = copia;

	for (int i = 0; i < *cant1; i++)
		arrA1[i]->Mover_enemigo1(g, img_enemigo1);
}

void Configuracion::Mover_Enemigos2(Graphics^ g, Bitmap^ img_enemigo2) {
	int cantidad = 0;
	for (int i = 0; i < *cant2; i++)
		cantidad += arrA2[i]->retornar_eliminar_A2() ? 1 : 0;

	Adversarios** copia = new Adversarios * [*cant2 - cantidad];
	int j = 0;
	for (int i = 0; i < *cant2; i++) {
		if (!arrA2[i]->retornar_eliminar_A2()) {
			copia[j] = arrA2[i];
			j++;
		}
	}
	*cant2 = *cant2 - cantidad;
	arrA2 = copia;

	for (int i = 0; i < *cant2; i++)
		arrA2[i]->Mover_enemigo2(g, img_enemigo2);
}

bool Configuracion::Game_Over() {
	for (int i = 0; i < *cant1; i++)
		if (Colision(objJ, arrA1[i]))
			fin_juego = true;

	for (int i = 0; i < *cant2; i++)
		if (Colision(objJ, arrA2[i]))
			fin_juego = true;

	return fin_juego;
}

bool Configuracion::Colision(Personaje* obj1, Personaje* obj2) {
	Rectangle r1;
	r1.X = obj1->retornar_x();
	r1.Y = obj1->retornar_y();
	r1.Width = obj1->retornar_w();
	r1.Height = obj1->retornar_h();

	Rectangle r2;
	r2.X = obj2->retornar_x();
	r2.Y = obj2->retornar_y();
	r2.Width = obj2->retornar_w();
	r2.Height = obj2->retornar_h();

	return r1.IntersectsWith(r2);
}

void Configuracion::Disparar() {
	objJ->Disparar();
}