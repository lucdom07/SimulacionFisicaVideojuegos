#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>

#include "Particle.h"
#include "ForceRegistry.h"

class Level_1 :
    public Scene
{
public:
    explicit Level_1(std::string name) : Scene(std::move(name)) {}

    void init() override {
        player = new Particle(Vector3D(-50.f, 0.f, 0.f), Vector3D(), Vector3D(0.f, 1.f, 0.f), 1000.f, -1, 2.f, true);
        enemy = new Particle(Vector3D(50.f, 0.f, 0.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.5f, -1, 2.f, true);
        fReg = new ForceRegistry();
    }

    void update(double dt) override {

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

