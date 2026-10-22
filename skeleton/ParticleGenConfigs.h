#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"
#include "Vector3D.h"

enum Distribution { UNIFORM, GAUSSIAN };


struct UniformConfig {
	Vector3D minDir;
	Vector3D maxDir;

	float minVel;
	float maxVel;

	float minLife;
	float maxLife;

	float minSize;
	float maxSize;

	float minColorR;
	float maxColorR;

	float minColorG;
	float maxColorG;

	float minColorB;
	float maxColorB;
};

struct GaussianConfig {
	Vector3D meanDir;
	Vector3D stddevDir;

	float meanVel;
	float stddevVel;

	float meanLife;
	float stddevLife;

	float meanSize;
	float stddevSize;

	float meanColorR;
	float stddevColorR;

	float meanColorG;
	float stddevColorG;

	float meanColorB;
	float stddevColorB;
};

struct ParticleConfig {
	Vector3D pos;
	float mass;
	Vector3D vel;
	float life;
	float size;
	Vector3D color;
};

struct GeneratorConfig {
	Distribution distribType;
	UniformConfig uniform;
	GaussianConfig gaussian;

	Vector3D velDir;
	float partMass;
	float genTime;
	int meanParts;
	int varParts;
	float emitRadius;

	physx::PxTransform emitTrans;
};