#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include "Vector3D.h"
class P1_Scene :
    public Scene
{
public:
    explicit P1_Scene(std::string name) : Scene(std::move(name)), 
        particle(Vector3D(0,0,0), Vector3D(10, 10, 0), Vector3D(0, 30, 0), 0.98f, 1.f) {}

    void init() override {
        
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        particle.integrateVerlet(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
    }

private:
    Particle particle;
};

