#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "Particle.h"
#include "WhirlGenerator.h"
#include "ForceRegistry.h"

class Scene1 :
    public Scene
{
public:
    explicit Scene1(std::string name) : Scene(std::move(name)), p(nullptr), fReg(nullptr) {
    }

    void init() override {
        fReg = new ForceRegistry();

        // CREACIÓN SISTEMAS DE PARTÍCULAS
        p = new Particle(Vector3D(0.f, 0.f, 0.f), Vector3D(), Vector3D(1.f, 0.f, 1.f), 10.f, -1, 2.f);

        // CREACIÓN FUERZAS
        WhirlGenerator* whirl = new WhirlGenerator(Vector3D(50.f, 50.f, 50.f), Vector3D(-40.f, 0.f, 0.f), 1.f);
        fReg->registerPair(p, whirl);
        forces.push_back(whirl);
    }

    void update(double dt) override {
        fReg->applyForce(dt);
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
    std::vector<ForceGenerator*> forces;
    ForceRegistry* fReg;
    Particle* p;
};

