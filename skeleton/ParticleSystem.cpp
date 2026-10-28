#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "Particle.h"
#include "ForceRegistry.h"

ParticleSystem::ParticleSystem(GeneratorConfig& config) : generator(new ParticleGenerator(config)), fReg(new ForceRegistry())
{
	for (int i = 0; i < N_PARTS; i++) {
		particles.push_back(new Particle());
	}
	firstInactive = particles.begin();
}

ParticleSystem::~ParticleSystem() {
	delete generator;
	for (Particle* p : particles) {
		delete p;
	}
	particles.clear();
}

void ParticleSystem::update(double dt) {
	std::vector<ParticleConfig> newParticles;
	generator->update(dt, newParticles);
	for (ParticleConfig& config : newParticles) {
		activateParticle(config);
	}

	fReg->applyForce(dt);

	for (Particle* p : particles) {
		if (p->isActive()) p->update(dt);
	}
}

void ParticleSystem::addForce(ForceGenerator* f) {
	for (Particle* p : particles) {
		fReg->registerPair(p, f);
	}
}

void ParticleSystem::activateParticle(ParticleConfig config) {
	int i = 0;
	while ((*firstInactive)->isActive() && i < N_PARTS) {
		++firstInactive;
		if (firstInactive == particles.end()) firstInactive = particles.begin();
		i++;
	}
	if (!(*firstInactive)->isActive()) (*firstInactive)->configParticle(config.pos, config.vel, config.color, config.mass, config.life, config.size);
}