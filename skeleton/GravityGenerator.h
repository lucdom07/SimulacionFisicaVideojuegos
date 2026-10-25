#pragma once
#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator(float g);
	~GravityGenerator();
	void updateForce(Particle* particle, float dt) override;
private:
	Vector3D gravity;
};

