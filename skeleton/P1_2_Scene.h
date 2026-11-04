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
        float mass;
        float gravity;
    };

    explicit P1_2_Scene(std::string name) : Scene(std::move(name)), currP(nullptr) {
        configs.insert({ canonChar, BulletConfig{250.f, 5000.f, 9.81f} });
        configs.insert({ tankChar, BulletConfig{1800.f, 18000.f, 9.81f} });
        configs.insert({ gunChar, BulletConfig{330.f, 3.56f, 9.81f} });
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
        if (key == canonChar || key == tankChar || key == gunChar) {
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
        Vector3D cameraPos = Vector3D(camera->getTransform().p);
        currP = new Bullet(cameraPos + camera->getDir() * shootDistance, camera->getDir() * chosen.rVel, chosen.mass, chosen.gravity);
        proyectiles.push_back(currP);
    }

private:
    const char canonChar = 'c';
    const char tankChar = 't';
    const char gunChar = 'p';

    // Distancia de la creación del proyectil a la cámara para que el proyectil no tape la cámara
    const float shootDistance = 20.f;

    std::unordered_map<unsigned char, BulletConfig> configs;
    std::vector<Bullet*> proyectiles;
    Bullet* currP;
};

