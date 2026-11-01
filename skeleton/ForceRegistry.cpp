#include "ForceRegistry.h"
#include "ForceGenerator.h"
#include "Particle.h"

void ForceRegistry::registerPair(Particle* p, ForceGenerator* f) {
	registry[p].push_back(f);
	activeForces.insert({ f, true });
}

void ForceRegistry::applyForce(double t) {
	for (auto [part, fGenVec] : registry) {
		part->cleanAcumulator();
		for (ForceGenerator* fGen : fGenVec) {
			if (activeForces[fGen]) fGen->updateForce(part, t);
		}
	}
}

void ForceRegistry::setForceState(ForceGenerator* f, bool active) {
	activeForces[f] = active;
}