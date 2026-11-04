#pragma once
#include "WindGenerator.h"
#include <unordered_map>

class ExplosionGenerator : public WindGenerator
{
public:
	ExplosionGenerator(Vector3D dimArea, Vector3D centerPos, float vel, float k, float durTime) : 
		WindGenerator(dimArea, centerPos, Vector3D(), k), velMag(vel), timer(durTime), duration(durTime) {};
	~ExplosionGenerator() {};
	void updateForce(Particle* particle, float dt) override;
	void updateAttribs(float dt) override;
protected:
	// magnitud del vector velocidad
	float velMag;
	float timer;
	float duration;

	// direcciones que le corresponden a cada partícula
	std::unordered_map<Particle*, Vector3D> dirs;
};

