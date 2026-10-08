#pragma once
#include "Particle.h"
// Clase para los proyectiles
class Bullet : public Particle
{
public:
	Bullet(Vector3D pos, Vector3D pvel, Vector3D a, float d, float m, float g) : Particle(pos, pvel, a, d, m), gravity(Vector3D(0, -g, 0)) {};
	~Bullet() {};
	void integrateSemiEuler(double t) override;
	void changeGravity(bool increase);
protected:
	const float gravMod = 0.1f; // indica cuánto cambia la gravedad por cada pulsación
	Vector3D gravity;
};