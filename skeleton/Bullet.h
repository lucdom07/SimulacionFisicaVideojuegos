#pragma once
#include "Particle.h"
// Clase para los proyectiles
class Bullet : public Particle
{
public:
	Bullet(Vector3D pos, Vector3D rvel, float rMass, float rGravity);
	~Bullet() {};
protected:
	// modificador para ajustar la velocidad simulada
	const float simVelMod = 0.1f;
	// indica cuánto cambia la gravedad por cada pulsación
	const float gravMod = 0.1f;
	// modificador para calcular la gravedad simulada
	Vector3D simGrav;
};