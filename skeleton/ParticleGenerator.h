#pragma once
#include "ParticleGenConfigs.h"
#include <vector>
class ParticleGenerator
{
public:
	ParticleGenerator(GeneratorConfig& config);
	~ParticleGenerator() {};

	void update(double t, std::vector<ParticleConfig>& configs);
protected:
	void generateNewPartConfigs(std::vector<ParticleConfig>& configs);
	ParticleConfig uniformAttribs();
	ParticleConfig gaussianAttribs();

	Distribution distribType;
	UniformConfig uniform;
	GaussianConfig gaussian;

	Vector3D velDir;
	float partMass;
	float timer;
	float genTime;
	int meanParts;
	int varParts;
	float emitRadius;
	float screenSizeFactor;

	physx::PxTransform emitTrans;
};