#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Bullet.h"

class P1_2_Scene :
    public Scene
{
public:

    struct BulletConfig {
        float rVel;
        float simVel;
        float mass;
        float gravity;
    };

    explicit P1_2_Scene(std::string name) : Scene(std::move(name)), currP(nullptr) {
        configs.insert({ canonChar, BulletConfig{250.f, 2.f, 5000.f, 9.81f} });
        configs.insert({ tankChar, BulletConfig{1800.f, 20.f, 18000.f, 9.81f} });
        configs.insert({ gunChar, BulletConfig{330.f, 4.f, 3.56f, 9.81f} });
        configs.insert({ laserChar, BulletConfig{3.f * powf(10.f, 8.f), 300.f, 0.f, 9.81f}});
    }

    void init() override {

    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        for (Bullet* p : proyectiles) {
            p->integrateSemiEuler(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == canonChar || key == tankChar || key == gunChar || key == laserChar) {
            instantiateBullet(key);
        }
        else if (currP) {
            if (key == '\'') { 
                //disminuir masa
                currP->changeMass(false);
            }
            else if (key == '¡') {
                //aumentar masa
                currP->changeMass(true);
            }
            else if (key == '?') {
                //disminuir gravedad
                currP->changeGravity(false);
            }
            else if (key == '¿') {
                //aumentar gravedad
                currP->changeGravity(true);
            }
        }
    }

    void cleanup() override {
        for (Bullet* p : proyectiles) {
            delete p;
        }
    }

    void instantiateBullet(unsigned char key) {
        Camera* camera = GetCamera();
        BulletConfig chosen = configs[key];
        currP = new Bullet(Vector3D(camera->getEye().x, camera->getEye().y, camera->getEye().z),
            Vector3D(camera->getDir().x * chosen.simVel, camera->getDir().y * chosen.simVel, camera->getDir().z * chosen.simVel), chosen.rVel,
            Vector3D(), 0.99f, chosen.mass, chosen.gravity);
        proyectiles.push_back(currP);
    }

private:
    const char canonChar = 'c';
    const char tankChar = 't';
    const char gunChar = 'p';
    const char laserChar = 'l';

    std::unordered_map<unsigned char, BulletConfig> configs;
    std::vector<Bullet*> proyectiles;
    Bullet* currP;
};

