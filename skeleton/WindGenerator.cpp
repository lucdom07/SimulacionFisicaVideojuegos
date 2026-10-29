#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3D vel, float wk1, float wk2) : windVel(vel), k1(wk1), k2(wk2) {
}

void WindGenerator::updateForce(Particle* particle, float dt) {
	Vector3D windForce = (windVel - particle->getVel()) * k1 + (windVel - particle->getVel()) * (windVel - particle->getVel()).magnitude() * k2;
	particle->acumulateForce(windForce);
}