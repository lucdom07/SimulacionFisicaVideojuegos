#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"

class RenderItem;
class Particle
{
public:
	Particle(Vector3D pos, Vector3D pvel, Vector3D a, float d, float m);
	virtual ~Particle();

	void integrateEuler(double t);
	virtual void integrateSemiEuler(double t);
	void integrateVerlet(double t);
	void changeMass(bool increase);
protected:
	Vector3D vel;
	Vector3D acc;
	const float massMod = 0.1f; // indica cuánto cambia la masa por cada pulsación
	float damping;
	float mass;

	physx::PxTransform pose;
	Vector3D lastPose;
	RenderItem* renderItem;
};

