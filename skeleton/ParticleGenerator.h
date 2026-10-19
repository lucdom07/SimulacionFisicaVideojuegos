#pragma once
#include "ParticleGenConfigs.h"
#include <vector>
class ParticleGenerator
{
public:
	ParticleGenerator() {};
	~ParticleGenerator();
	std::vector<ParticleConfig> generateNewPartConfigs();
	ParticleConfig uniformAttribs();
	ParticleConfig gaussianAttribs();
protected:
	Distribution distribType;
	UniformConfig uniform;
	GaussianConfig gaussian;

	Vector3D velDir;
	float partMass;
	float genTime;
	int meanParts;
	int varParts;
	float emitRadius;
	float screenSizeFactor;

	physx::PxTransform emitTrans;
};