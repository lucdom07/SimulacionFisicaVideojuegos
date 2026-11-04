#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "Particle.h"
#include <iostream>

ParticleSystem::ParticleSystem()
{
	for (int i = 0; i < N_PARTS; i++) {
		particles.push_back(new Particle());
	}
	firstInactive = particles.begin();
}

ParticleSystem::~ParticleSystem() {
	for (ParticleGenerator* g : partGens) {
		delete g;
	}
	partGens.clear();
	for (Particle* p : particles) {
		delete p;
	}
	particles.clear();
}

void ParticleSystem::update(double dt) {
	generateParticles(dt);
	for (Particle* p : particles) {
		if (p->isActive()) p->update(dt);
	}
}

void ParticleSystem::addParticleGen(ParticleGenerator* g) {
	partGens.push_back(g);
}

void ParticleSystem::setParticleGenState(ParticleGenerator* g, bool active) {
	g->setActive(active);
}

void ParticleSystem::generateParticles(double dt) {
	std::vector<ParticleConfig> newParticles;
	for (ParticleGenerator* g : partGens) {
		if (g->isActive()) g->update(dt, newParticles);
	}
	for (ParticleConfig& config : newParticles) {
		activateParticle(config);
	}
}

void ParticleSystem::activateParticle(ParticleConfig config) {
	int i = 0;
	while ((*firstInactive)->isActive() && i < N_PARTS) {
		++firstInactive;
		if (firstInactive == particles.end()) firstInactive = particles.begin();
		i++;
	}
	if (!(*firstInactive)->isActive()) {
		(*firstInactive)->configParticle(config.pos, config.vel, config.color, config.mass, PARTS_GRAVITY, config.life, config.size);
		std::cout << "aaaaaaaaa\n";
	}
}