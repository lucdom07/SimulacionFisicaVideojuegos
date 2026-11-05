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
    explicit Level_1(std::string name) : Scene(std::move(name)), rewind(1.0), 
        player(nullptr), playerWind(nullptr), playerForceReg(nullptr),enemyForceReg(nullptr) {}

    void init() override {
        rewind = 1;
        playerForceReg = new ForceRegistry();
        enemyForceReg = new ForceRegistry();

        // CREACIÓN PARTÍCULAS

        player = new Particle(Vector3D(0.f, 0.f, 0.f), Vector3D(), Vector3D(0.f, 1.f, 0.f), 4.f, -1, 2.f);
        enemies.push_back(new Particle(Vector3D(-50.f, 30.f, -50.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.7f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-50.f, -20.f, -50.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.6f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-65.f, 40.f, -65.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.5f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-65.f, -3.f, -65.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.7f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-80.f, 20.f, -80.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.6f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-80.f, -10.f, -80.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.5f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-95.f, 50.f, -95.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.8f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-95.f, -40.f, -95.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.6f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-110.f, 10.f, -110.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.5f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-110.f, -15.f, -110.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.6f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-125.f, 30.f, -125.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.6f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-125.f, -36.f, -125.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.7f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-140.f, 10.f, -140.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.5f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-140.f, -20.f, -140.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.6f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-155.f, 20.f, -155.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.7f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-155.f, -25.f, -155.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.5f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-170.f, 0.f, -170.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.6f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-170.f, -5.f, -170.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.7f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-185.f, 50.f, -185.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.7f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-185.f, -20.f, -185.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.8f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-200.f, 40.f, -200.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.5f, -1, 2.f));
        enemies.push_back(new Particle(Vector3D(-200.f, -10.f, -200.f), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.7f, -1, 2.f));

        // CREACIÓN FUERZAS

        GravityGenerator* grav = new GravityGenerator(10.f);
        WindGenerator* wind = new WindGenerator(Vector3D(1000.f, 5.f, 1000.f), Vector3D(-200.f, -45.f, -200.f), Vector3D(0.f, 90.f, 0.f), 20.f);
        forces.push_back(grav);
        forces.push_back(wind);

        for (Particle* e : enemies) {
            enemyForceReg->registerPair(e, grav);
            enemyForceReg->registerPair(e, wind);
        }

        playerWind = new WindGenerator(Vector3D(30.f, 5.f, 30.f), Vector3D(0.f, 0.f, 0.f), Vector3D(-50.f, 0.f, -50.f), 25.f);
        forces.push_back(playerWind);

        playerForceReg->registerPair(player, playerWind);
        playerForceReg->setForceState(playerWind, false);
    }

    void update(double dt) override {
        double time = dt * rewind;
        playerForceReg->applyForce(dt);
        enemyForceReg->applyForce(time);
        for (Particle* e : enemies) {
            e->integrateSemiEuler(time);
        }
        player->integrateSemiEuler(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 't' || key == 'T') {
            rewind = (rewind > 0.0) ? -0.6 : 1.0;
        }
        else if (key == 'p' || key == 'P') {
            playerForceReg->setForceState(playerWind, true);
        }
    }

    void cleanup() override {
        delete player;
        for (Particle* e : enemies) {
            delete e;
        }
        delete enemyForceReg;
        delete playerForceReg;
        for (ForceGenerator* f : forces) {
            delete f;
        }
    }

private:
    double rewind;

    Particle* player;
    std::vector<Particle*> enemies;

    WindGenerator* playerWind;
    std::vector<ForceGenerator*> forces;

    ForceRegistry* playerForceReg;
    ForceRegistry* enemyForceReg;
};

