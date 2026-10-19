#pragma once
#include "PxPhysicsAPI.h"
#include "Vector3D.h"

class RenderItem;
class Particle
{
public:
	Particle();
	Particle(Vector3D pos, Vector3D pvel, Vector3D a, Vector3D color, float m, float g, float life, float size);
	virtual ~Particle();
	void configParticle(Vector3D pos, Vector3D pvel, Vector3D a, Vector3D color, float m, float g, float life, float size);
	void integrateEuler(double t);
	virtual void integrateSemiEuler(double t);
	void integrateVerlet(double t);
	void changeMass(bool increase);
	void changeGravity(bool increase);
	//suma el delta time al contador de tiempo de vida de la partícula. Devuelve true si ya ha superado su tiempo de vida y false en caso contrario
	void countLifeTime(double t);
	void decreaseOpacity(double t);
	void decreaseSize(double t);
protected:
	bool active;

	Vector3D vel;
	Vector3D acc;
	
	// indica cuánto cambia la masa por cada pulsación
	const float massMod = 0.1f; 
	// indica cuánto cambia la gravedad por cada pulsación
	const float gravMod = 0.1f; 
	// indica cuánto cambia la opacidad según el tiempo
	const float opacMod = 0.1f;
	// indica cuánto cambia el tamaño según el tiempo
	const float sizeMod = 0.1f;
	const float damping = 0.99f;
	float mass;
	//inverso de la masa
	float invMass;
	float lifeTime;
	float lTimer;

	physx::PxTransform pose;
	Vector3D lastPose;	
	Vector3D gravity;

	RenderItem* renderItem;
};

