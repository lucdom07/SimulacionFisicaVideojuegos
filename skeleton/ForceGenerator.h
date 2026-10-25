#pragma once
#include "Particle.h"
class ForceGenerator
{
public:
	ForceGenerator();
	virtual ~ForceGenerator();
	virtual void updateForce(Particle* particle, float dt) = 0;
};