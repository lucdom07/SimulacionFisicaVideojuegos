#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "Particle.h"
#include "BuoyancyGenerator.h"
#include "GravityGenerator.h"
#include "ForceRegistry.h"

class Scene3 :
    public Scene
{
public:
    explicit Scene3(std::string name) : Scene(std::move(name)), p(nullptr), fReg(nullptr) {
    }

    void init() override {
        fReg = new ForceRegistry();

        // CREACIÓN PARTÍCULA
        p = new Particle(Vector3D(0.f, -10.f, 0.f), Vector3D(), Vector3D(1.f, 0.f, 1.f), 1000.f, -1, 10.f, 30.f, 10.f);

        // CREACIÓN FUERZAS
        BuoyancyGenerator* buoyancy = new BuoyancyGenerator(0.f, 3.f, 1000);
        fReg->registerPair(p, buoyancy);
        forces.push_back(buoyancy);
        GravityGenerator* grav = new GravityGenerator(9.81f);
        fReg->registerPair(p, grav);
        forces.push_back(grav);
    }

    void update(double dt) override {
        fReg->applyForce(dt);
        p->integrateSemiEuler(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        delete p;
        delete fReg;
        for (ForceGenerator* p : forces) {
            delete p;
        }
    }

private:
    double timer = 0.;
    double windTime = 5.;
    // Indica cuánto cambia k por pulsación
    double kMod = 1.;

    std::vector<ForceGenerator*> forces;
    ForceRegistry* fReg;
    Particle* p;
};

