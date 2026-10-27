#pragma once
#include "PxPhysicsAPI.h"
#include "Vector3D.h"

class RenderItem;
class Particle
{
public:
	Particle();
	Particle(Vector3D pos, Vector3D pvel, Vector3D color, float m, float g, float life, float size);
	virtual ~Particle();

	bool isActive() { return active; };

	void configParticle(Vector3D pos, Vector3D pvel, Vector3D color, float m, float g, float life, float size);

	void update(double dt);
	void cleanAcumulator();
	void acumulateForce(Vector3D F, float dt);
	virtual void integrateSemiEuler(double t);

	void changeMass(bool increase);
	void changeGravity(bool increase);
protected:
	//suma el delta time al contador de tiempo de vida de la partícula
	void countLifeTime(double t);
	void decreaseOpacity(double t);
	void decreaseSize(double t);

	//indica si la partícula está activa
	bool active;

	Vector3D vel;
	Vector3D acc;
	//acumulador de fuerzas
	Vector3D f;

	// modificador para la velocidad simulada
	const float simVelMod = 0.01f;
	// indica cuánto cambia la masa por cada pulsación
	const float massMod = 0.1f; 
	// indica cuánto cambia la gravedad por cada pulsación
	const float gravMod = 0.1f; 
	const float damping = 0.99f;
	float initSize;
	float mass;
	// inverso de la masa
	float invMass;
	float lifeTime;
	float lTimer;

	physx::PxTransform pose;
	Vector3D lastPose;	
	Vector3D gravity;

	RenderItem* renderItem;
};

