#include "ExplosionGenerator.h"
#include <random>
#include <iostream>

void ExplosionGenerator::updateForce(Particle* particle, float dt) {
	// Si la partícula no está en el área de la explosión, no se aplica la fuerza
	if (!renderItem->checkCollision(particle->getRendeItem())) return;

	if (!dirs.contains(particle)) {
		dirs[particle] = Vector3D();
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dir(0.f, 1.f);
		dirs[particle] = Vector3D(dir(gen), dir(gen), dir(gen)).normalize();
	}
	Vector3D windForce = (timer > 0.001f) ? 
		((dirs[particle] * velMag - particle->getVel()) * k1 +
		(dirs[particle] * velMag - particle->getVel()) * (dirs[particle] * velMag - particle->getVel()).magnitude() * k2) * (timer/duration) :
		Vector3D();
	particle->acumulateForce(windForce);
}

void ExplosionGenerator::updateAttribs(float dt) {
	if (timer < 0.001f) return;
	timer -= dt;
}