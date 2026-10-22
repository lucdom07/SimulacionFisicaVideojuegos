#pragma once
#include <vector>
class ParticleGenerator;
class Particle;
struct ParticleConfig;
struct GeneratorConfig;
class ParticleSystem
{
public:
	ParticleSystem(GeneratorConfig& config);
	~ParticleSystem();

	void update(double dt);
private:
	void activateParticle(ParticleConfig config);

	const int N_PARTS = 500;
	const float PARTS_GRAVITY = 10.f;
	std::vector<Particle*> particles;
	using particle_it = std::vector<Particle*>::iterator;
	particle_it firstInactive;
	ParticleGenerator* generator;
};