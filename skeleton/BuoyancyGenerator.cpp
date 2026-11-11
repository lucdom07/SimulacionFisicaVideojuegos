#include "BuoyancyGenerator.h"

BuoyancyGenerator::BuoyancyGenerator(float h, float V, float d) : mHeight(h), mVolume(V), mDensity(d) {
	mLiquidPart = new Particle(Vector3D(), Vector3D(), Vector3D(0., 0.3, 1.), 0., -1., 100, 0.1, 100);
}

BuoyancyGenerator::~BuoyancyGenerator() {
	delete mLiquidPart;
}

void BuoyancyGenerator::updateForce(Particle* particle, float dt) {
	float h = particle->getPos().y;
	float h0 = mLiquidPart->getPos().y;

	Vector3D f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > mHeight * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > mHeight * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / mHeight + 0.5;
	}
	f.y = mDensity * mVolume * immersed * 9.8;

	particle->acumulateForce(f);
}