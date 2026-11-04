#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>

#include "Particle.h"
#include "ForceRegistry.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"

class Level_1 :
    public Scene
{
public:
    explicit Level_1(std::string name) : Scene(std::move(name)) {}

    void init() override {
        fReg = new ForceRegistry();

        player = new Particle(Vector3D(0.f, 0.f, 0.f), Vector3D(), Vector3D(0.f, 1.f, 0.f), 1000.f, -1, 2.f);
        enemy = new Particle(Vector3D(-50.f, 50.f, -50.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.5f, -1, 2.f);

        GravityGenerator* grav = new GravityGenerator(9.81f);
        WindGenerator* wind = new WindGenerator(Vector3D(5.f, 5.f, 5.f), Vector3D(-50.f, -90.f, -50.f), Vector3D(0.f, 90.f, 0.f), 25.f);

        fReg->registerPair(enemy, grav);
        fReg->registerPair(enemy, wind);
    }

    void update(double dt) override {
        fReg->applyForce(dt);
        enemy->integrateSemiEuler(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

    }

    void cleanup() override {
        delete player;
        delete enemy;
        delete fReg;
    }

private:
    Particle* player;
    Particle* enemy;

    ForceRegistry* fReg;
};

