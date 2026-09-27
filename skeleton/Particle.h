#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"

class RenderItem;
class Particle
{
public:
	Particle(Vector3D pos, Vector3D pvel);
	~Particle();

	void integrate(double t);

private:
	Vector3D vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

