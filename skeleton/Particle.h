#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"

class RenderItem;
class Particle
{
public:
	Particle(Vector3D pos, Vector3D pvel, Vector3D a, float d);
	~Particle();

	void integrate(double t);

private:
	Vector3D vel;
	Vector3D acc;
	float damping;

	physx::PxTransform pose;
	RenderItem* renderItem;
};

