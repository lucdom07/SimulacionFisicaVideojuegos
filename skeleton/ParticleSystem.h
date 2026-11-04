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
	void addForce(ForceGenerator* f);
	void addParticleGen(ParticleGenerator* g);
	void setParticleGenState(ParticleGenerator* g, bool active);
private:
	void generateParticles(double dt);
	void activateParticle(ParticleConfig config);

	const int N_PARTS = 1000;
	std::vector<Particle*> particles;
	using particle_it = std::vector<Particle*>::iterator;
	particle_it firstInactive;
	ForceRegistry* fReg;
	std::vector<ParticleGenerator*> partGens;
};