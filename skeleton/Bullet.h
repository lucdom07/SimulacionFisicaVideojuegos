#pragma once
#include "Particle.h"
// Clase para los proyectiles
class Bullet : public Particle
{
public:
	Bullet(Vector3D pos, Vector3D simvel, float rvel, Vector3D a, float d, float rMass, float rGravity);
	~Bullet() {};
	void integrateSemiEuler(double t) override;
	void changeGravity(bool increase);
protected:
	const float gravMod = 0.1f; // indica cuánto cambia la gravedad por cada pulsación
	Vector3D gravity;
};