#pragma once
#include "Particle.h"
// Clase para los proyectiles
class Bullet : public Particle
{
public:
	Bullet(Vector3D pos, Vector3D rvel, float rMass, float rGravity);
	~Bullet() {};
	void integrateSemiEuler(double t) override;
protected:
	// modificador para calcular la velocidad simulada
	const float simVelMod = 0.01f;
	Vector3D simGrav;
};