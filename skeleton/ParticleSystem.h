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
	ParticleSystem(GeneratorConfig& config);
	~ParticleSystem();

	void update(double dt);
	void addParticleGen(ParticleGenerator* g);
	void addForce(ForceGenerator* f);
private:
	void generateParticles(double dt);
	void activateParticle(ParticleConfig config);

	const int N_PARTS = 500;
	std::vector<Particle*> particles;
	using particle_it = std::vector<Particle*>::iterator;
	particle_it firstInactive;
	std::vector<ParticleGenerator*> partGens;
	ForceRegistry* fReg;
};