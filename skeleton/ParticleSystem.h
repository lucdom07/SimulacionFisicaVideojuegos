#pragma once
#include <vector>
class ParticleGenerator;
class Particle;
struct ParticleConfig;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void update(double dt);
	void activateParticle(ParticleConfig config);
private:
	const int N_PARTS = 100;
	const float PARTS_GRAVITY = 10.f;
	std::vector<Particle*> particles;
	using particle_it = std::vector<Particle*>::iterator;
	particle_it firstInactive;
	ParticleGenerator* generator;
};