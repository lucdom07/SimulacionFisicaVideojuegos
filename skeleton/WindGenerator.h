#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(Vector3D dimArea, Vector3D pos, Vector3D vel, float wk1, float wk2 = 0.f);
	~WindGenerator();
	void updateForce(Particle* particle, float dt) override;
protected:
	float k1;
	float k2;

	RenderItem* renderItem;
	physx::PxTransform windTrans;
	Vector3D windVel;
};