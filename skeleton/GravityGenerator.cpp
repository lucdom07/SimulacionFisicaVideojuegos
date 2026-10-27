#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(float g) : gravity(0.f, -g, 0.f) {
}

void GravityGenerator::updateForce(Particle* particle, float dt) {
	particle->acumulateForce(gravity, dt);
}