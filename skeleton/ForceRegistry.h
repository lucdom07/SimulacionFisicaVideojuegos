#pragma once
#include <vector>
#include <unordered_map>
class Particle;
class ForceGenerator;
class ForceRegistry
{
public:
	struct PartForces {
		Particle* particle;
		ForceGenerator* forceGen;
	};
	ForceRegistry() {};
	~ForceRegistry() {};
	bool getForceState(ForceGenerator* f) { return activeForces[f]; };
	void setForceState(ForceGenerator* f, bool active) { activeForces[f] = active; };
	void registerPair(Particle* p, ForceGenerator* f);
	void applyForce(double t);
private:
	std::unordered_map<Particle*, std::vector<ForceGenerator*>> registry;
	std::unordered_map<ForceGenerator*, bool> activeForces;
};

