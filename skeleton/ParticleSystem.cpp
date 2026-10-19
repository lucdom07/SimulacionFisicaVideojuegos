#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "Particle.h"

void ParticleSystem::update(double dt) {

}

void ParticleSystem::activateParticle(ParticleConfig config) {
	Particle* p = *firstInactive;
	p->configParticle(config.pos, config.vel, Vector3D(0,0,0), config.color, config.mass, PARTS_GRAVITY, config.life, config.size);
}