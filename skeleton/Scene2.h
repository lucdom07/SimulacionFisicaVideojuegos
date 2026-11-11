#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include "Particle.h"
#include "ElasticBand.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "ForceRegistry.h"

class Scene2 :
    public Scene
{
public:
    explicit Scene2(std::string name) : Scene(std::move(name)), fReg(nullptr) {
    }

    void init() override {
        fReg = new ForceRegistry();
        double restLength = 10.;
        double partDist = restLength/2.;

        // CREACIÓN PARTÍCULA
        Particle* p1 = new Particle(Vector3D(-1. , 0.f, 1.).normalize() * partDist, Vector3D(), Vector3D(1.f, 0.f, 1.f), 100.f, -1, 2.f);
        parts.push_back(p1);
        Particle* p2 = new Particle(Vector3D(1., 0.f, -1.).normalize() * partDist, Vector3D(), Vector3D(0.f, 1.f, 1.f), 100.f, -1, 2.f);
        parts.push_back(p2);

        // CREACIÓN FUERZAS
        ElasticBand* spring1 = new ElasticBand(10., restLength, p1);
        fReg->registerPair(p2, spring1);
        forces.push_back(spring1);

        ElasticBand* spring2 = new ElasticBand(10., restLength, p2);
        fReg->registerPair(p1, spring2);
        forces.push_back(spring2);

        WindGenerator* wind1 = new WindGenerator(Vector3D(100., 100., 100.), Vector3D(-1., 0.f, 1.).normalize() * partDist, Vector3D(-50.f, 0.f, 50.f), 30.f);
        fReg->registerPair(p1, wind1);
        forces.push_back(wind1);
        WindGenerator* wind2 = new WindGenerator(Vector3D(100., 100., 100.), Vector3D(1., 0.f, -1.).normalize() * partDist, Vector3D(50.f, 0.f, -50.f), 30.f);
        fReg->registerPair(p2, wind2);
        forces.push_back(wind2);
    }

    void update(double dt) override {
        fReg->applyForce(dt);
        for (Particle* p : parts) {
            p->integrateSemiEuler(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        delete fReg;
        for (Particle* p : parts) {
            delete p;
        }
        for (ForceGenerator* p : forces) {
            delete p;
        }
    }

private:
    std::vector<Particle*> parts;
    std::vector<ForceGenerator*> forces;
    ForceRegistry* fReg;
};

