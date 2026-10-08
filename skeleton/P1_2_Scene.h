#pragma once
#include <vector>
#include <unordered_map>
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Bullet.h"

class P1_2_Scene :
    public Scene
{
public:

    struct BulletConfig {
        Vector3D vel;
        float mass;
        float gravity;
    };

    explicit P1_2_Scene(std::string name) : Scene(std::move(name)), currP(nullptr) {
        configs.insert({ bulletChar, BulletConfig{Vector3D(100, 0, 0), 10.f, 9.81f} });
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
        if (key == bulletChar) {
            instantiateBullet(key, camera);
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

    void instantiateBullet(unsigned char key, const physx::PxTransform& camera) {
        BulletConfig chosen = configs[key];
        currP = new Bullet(Vector3D(camera.p.x, camera.p.y, camera.p.z), chosen.vel, Vector3D(), 0.99f, chosen.mass, chosen.gravity);
        proyectiles.push_back(currP);
    }

private:
    const char bulletChar = 'p';
    std::unordered_map<unsigned char, BulletConfig> configs;
    std::vector<Bullet*> proyectiles;
    Bullet* currP;
};

