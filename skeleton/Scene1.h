#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "Particle.h"
#include "AnchoredSpring.h"
#include "GravityGenerator.h"
#include "ForceRegistry.h"

class Scene1 :
    public Scene
{
public:
    explicit Scene1(std::string name) : Scene(std::move(name)), p(nullptr), fReg(nullptr) {
    }

    void init() override {
        fReg = new ForceRegistry();
        double restLength = 10.;
        Vector3D anchor = Vector3D(0., 60., 0.);

        // CREACIÓN PARTÍCULA
        p = new Particle(Vector3D(0.f, anchor.y - restLength, 0.f), Vector3D(), Vector3D(1.f, 0.f, 1.f), 10.f, -1, 2.f);

        // CREACIÓN FUERZAS
        GravityGenerator* grav = new GravityGenerator(9.81f);
        fReg->registerPair(p, grav);
        forces.push_back(grav);
        spring = new AnchoredSpring(5., 5., anchor);
        fReg->registerPair(p, spring);
        forces.push_back(spring);
    }

    void update(double dt) override {
        fReg->applyForce(dt);
        p->integrateSemiEuler(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == '+') {
            spring->setK(spring->getK() + kMod);
            std::cout << "Nuevo valor k: " << spring->getK() << '\n';
        }
        else if (key == '-') {
            spring->setK(spring->getK() - kMod);
            std::cout << "Nuevo valor k: " << spring->getK() << '\n';
        }
    }

    void cleanup() override {
        delete p;
        delete fReg;
        for (ForceGenerator* p : forces) {
            delete p;
        }
    }

private:
    // Indica cuánto cambia k por pulsación
    double kMod = 1.;
    std::vector<ForceGenerator*> forces;
    AnchoredSpring* spring;
    ForceRegistry* fReg;
    Particle* p;
};

