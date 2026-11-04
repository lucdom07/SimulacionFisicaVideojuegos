#pragma once
#include "ParticleGenConfigs.h"
#include <vector>
class ParticleGenerator
{
public:
	ParticleGenerator(GeneratorConfig& config);
	~ParticleGenerator() {};

	bool isActive() { return active; };
	void setActive(bool state) { active = state; };

	void update(double t, std::vector<ParticleConfig>& configs);
protected:
	void generateNewPartConfigs(std::vector<ParticleConfig>& configs);
	ParticleConfig uniformAttribs();
	ParticleConfig gaussianAttribs();

	Distribution distribType;
	UniformConfig uniform;
	GaussianConfig gaussian;

	bool active;

	float partMass;
	float timer;
	float genTime;
	int meanParts;
	int varParts;
	float emitRadius;
	float screenSizeFactor;

	physx::PxTransform emitTrans;
};