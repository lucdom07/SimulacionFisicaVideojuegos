#include <random>
#include <algorithm>
#include "ParticleGenerator.h"

std::vector<ParticleConfig> ParticleGenerator::generateNewPartConfigs() {
	std::vector<ParticleConfig> particleConfigs;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> partsDistrib(-varParts, varParts);
	int nParts = (meanParts + partsDistrib(gen)) * screenSizeFactor;
	for (int i = 0; i < nParts; i++) {
		(distribType == GAUSSIAN) ? particleConfigs.push_back(gaussianAttribs()) : particleConfigs.push_back(uniformAttribs());
	}
	return particleConfigs;
}

ParticleConfig ParticleGenerator::uniformAttribs() {
	std::random_device rd;
	std::mt19937 gen(rd());	
	std::uniform_real_distribution<> velDistrib(uniform.minVel, uniform.maxVel);
	std::uniform_real_distribution<> lifeDistrib(uniform.minLife, uniform.maxLife);
	std::uniform_real_distribution<> sizeDistrib(uniform.minSize, uniform.maxSize);
	std::uniform_real_distribution<> colorRDistrib(uniform.minColorR, uniform.maxColorR);
	std::uniform_real_distribution<> colorGDistrib(uniform.minColorG, uniform.maxColorG);
	std::uniform_real_distribution<> colorBDistrib(uniform.minColorB, uniform.maxColorB);
	std::uniform_real_distribution<> posDistrib(-emitRadius, emitRadius);
	Vector3D pPos(emitTrans.p.x + posDistrib(gen), emitTrans.p.y, emitTrans.p.z + posDistrib(gen));

	return ParticleConfig{ pPos, partMass, velDir.normalize() * (float)velDistrib(gen), (float)lifeDistrib(gen), (float)sizeDistrib(gen),
		Vector3D((float)colorRDistrib(gen), (float)colorGDistrib(gen), (float)colorBDistrib(gen)) };
}

ParticleConfig ParticleGenerator::gaussianAttribs() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<float> velDistrib(gaussian.meanVel, gaussian.stddevVel);
	std::normal_distribution<float> lifeDistrib(gaussian.meanLife, gaussian.stddevLife);
	std::normal_distribution<float> sizeDistrib(gaussian.meanSize, gaussian.stddevSize);
	std::normal_distribution<float> colorRDistrib(gaussian.meanColorR, gaussian.stddevColorR);
	std::normal_distribution<float> colorGDistrib(gaussian.meanColorG, gaussian.stddevColorG);
	std::normal_distribution<float> colorBDistrib(gaussian.meanColorB, gaussian.stddevColorB);
	std::uniform_real_distribution<> posDistrib(-emitRadius, emitRadius);
	Vector3D pPos(emitTrans.p.x + posDistrib(gen), emitTrans.p.y, emitTrans.p.z + posDistrib(gen));

	return ParticleConfig{ pPos, partMass, velDir.normalize() * velDistrib(gen), lifeDistrib(gen), sizeDistrib(gen),
		Vector3D(colorRDistrib(gen), colorGDistrib(gen), colorBDistrib(gen)) };
}