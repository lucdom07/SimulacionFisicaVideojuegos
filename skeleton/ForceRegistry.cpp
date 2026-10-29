#include "ForceRegistry.h"
#include "ForceGenerator.h"
#include "Particle.h"

void ForceRegistry::registerPair(Particle* p, ForceGenerator* f) {
	registry[p].push_back(f);
}

void ForceRegistry::applyForce(double t) {
	for (auto [part, fGenVec] : registry) {
		part->cleanAcumulator();
		for (ForceGenerator* fGen : fGenVec) {
			fGen->updateForce(part, t);
		}
	}
}