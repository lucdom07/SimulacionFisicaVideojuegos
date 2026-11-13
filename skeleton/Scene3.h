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
        p = new Particle(Vector3D(0.f, -1.f, 0.f), Vector3D(), Vector3D(1.f, 0.f, 1.f), 500.f, -1, 10.f, 30.f, 10.f);

        // CREACIÓN FUERZAS
        buoyancy = new BuoyancyGenerator(0.f, 1.f, 1000.f);
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
        if (key == ')') {
            p->changeMass(massMod);
            std::cout << "Nueva masa: " << p->getMass() << '\n';
        }
        else if (key == '(') {
            p->changeMass(-massMod);
            std::cout << "Nueva masa: " << p->getMass() << '\n';
        }
        else if (key == '[') {
            buoyancy->changeVolume(-volMod);
            std::cout << "Nuevo volumen: " << buoyancy->getVolume() << '\n';
        }
        else if (key == ']') {
            buoyancy->changeVolume(volMod);
            std::cout << "Nuevo volumen: " << buoyancy->getVolume() << '\n';
        }
    }

    void cleanup() override {
        delete p;
        delete fReg;
        for (ForceGenerator* f : forces) {
            delete f;
        }
    }

private:
    // indica cuánto cambia la masa por cada pulsación
    const float massMod = 1.f;
    // indica cuánto cambia el volumen por cada pulsación
    const float volMod = 0.25f;

    BuoyancyGenerator* buoyancy;
    std::vector<ForceGenerator*> forces;
    ForceRegistry* fReg;
    Particle* p;
};

