#pragma once
#include "Jugador.h"
#include "Adversarios.h"
#include "Aliados.h"
#include "Vehiculos.h"
#include "Mundo.h"
#include "time.h"

class Configuracion {
private:
	Jugador* objJ;
	Adversarios** arrA1;
	Adversarios** arrA2; 
	Vehiculos* objAmb;
	clock_t start;
	int tiempo;
	int* cant1;
	int* cant2;
	int ind1, ind2;
	int(mundo);
	bool fin_juego; 

public:
	Configuracion();
	~Configuracion();

	void Start();
	void Insertar_Adversarios1();
	void Insertar_Adversarios2();

	void Dinamica_Configuracion(Graphics^ g, Bitmap^ img_jugador, Bitmap^ img_mensaje, Bitmap^ img_enemigo, Bitmap^ img_amb);
	void Mover_Jugador(tecla_pulsada tecla);
	void Mover_Enemigos1(Graphics^ g, Bitmap^ img_enemigo1);
	void Mover_Enemigos2(Graphics^ g, Bitmap^ img_enemigo2);
	
	void Colisiones();
	void Disparar();
	void Cambiar_JugadorDY(int dy);
	void Cambiar_JugadorDX(int dx);
	bool Colision(Personaje* obj1, Personaje* obj2);

	bool Game_Over();

	int retornar_mundo();
	void cambiar_mundo(int n);
	int retornar_cantidad_Adversarios();
	void cambiar_Tiempo(int nuevo); 
	void cambiar_Game_over(bool nuevo);
	int retornar_Tiempo();
};