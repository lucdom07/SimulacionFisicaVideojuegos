#include "ForceRegistry.h"
#include "ForceGenerator.h"
#include "Particle.h"

void ForceRegistry::registerPair(Particle* p, ForceGenerator* f) {
	registry[p].push_back(f);
	activeForces.insert({ f, true });
}

void ForceRegistry::applyForce(double t) {
	// Se actualizan los atributos de las fuerzas antes de aplicarlas en la partícula
	for (auto [f, state] : activeForces) {
		if (activeForces[f]) f->updateAttribs(t);
	}
	for (auto [part, fGenVec] : registry) {
		if (part->isActive()) {
			part->cleanAcumulator();
			for (ForceGenerator* fGen : fGenVec) {
				if (activeForces[fGen]) fGen->updateForce(part, t);
			}
		}
	}
}
