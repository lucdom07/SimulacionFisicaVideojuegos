#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Bullet.h"

class Level_2 :
    public Scene
{
public:

    struct BulletConfig {
        float rVel;
        float mass;
        float gravity;
    };

    explicit Level_2(std::string name) : Scene(std::move(name)), currP(nullptr) {
        configs.insert({ shootChar, BulletConfig{330.f, 3.56f, 9.81f} });
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
        if (key == shootChar) {
            instantiateBullet(key);
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
    const char shootChar = 'p';
    // Distancia de la creación del proyectil a la cámara para que el proyectil no tape la cámara
    const float shootDistance = 20.f;

    std::unordered_map<unsigned char, BulletConfig> configs;
    std::vector<Bullet*> proyectiles;
    Bullet* currP;
};

