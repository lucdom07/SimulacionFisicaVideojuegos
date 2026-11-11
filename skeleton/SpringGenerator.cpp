#include "SpringGenerator.h"

SpringGenerator::SpringGenerator(double k, double rLength, Particle* other) {
	mK = k;
	mRestLength = rLength;
	mOther = other;
}

void SpringGenerator::updateForce(Particle* particle, float dt) {
	Vector3D relPos = mOther->getPos() - particle->getPos();
	Vector3D force;

	const float length = relPos.magnitude();
	const float deltaX = length - mRestLength;

	force = relPos.normalize() * deltaX * mK;

	particle->acumulateForce(force);
}