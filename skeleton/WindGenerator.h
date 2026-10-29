#pragma once
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(Vector3D vel, float wk1, float wk2 = 0.f);
	~WindGenerator() {};
	void updateForce(Particle* particle, float dt) override;
protected:
	float k1;
	float k2;

	Vector3D windVel;
};