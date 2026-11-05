#pragma once
#include <vector>
class ParticleGenerator;
class Particle;
class ForceRegistry;
class ForceGenerator;
struct ParticleConfig;
struct GeneratorConfig;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void update(double dt);
	void addParticleGen(ParticleGenerator* g);
	void addForce(ForceGenerator* f);
	void setParticleGenState(ParticleGenerator* g, bool active);
	bool getForceGenState(ForceGenerator* f);
	void setForceGenState(ForceGenerator* f, bool active);
private:
	void generateParticles(double dt);
	void activateParticle(ParticleConfig config);

	const int N_PARTS = 1000;
	std::vector<Particle*> particles;
	using particle_it = std::vector<Particle*>::iterator;
	particle_it firstInactive;
	std::vector<ParticleGenerator*> partGens;
	ForceRegistry* fReg;
};